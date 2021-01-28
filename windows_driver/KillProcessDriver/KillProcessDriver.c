#include <ntddk.h>

#define DEVICE_NAME L"\\Device\\HbgProcessKillerDriverDev"
#define DRIVER_LINK L"\\??\\HbgProcessKillerDriverLnk"

#define OPERKILLPID CTL_CODE(FILE_DEVICE_UNKNOWN,0x800,METHOD_BUFFERED,FILE_ANY_ACCESS)

// 结构声明
typedef struct _LDR_DATA_TABLE_ENTRY
{
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InMemoryOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID DllBase;
	PVOID EntryPoint;
	UINT32 SizeOfImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	UINT32 Flags;
	UINT16 LoadCount;
	UINT16 TlsIndex;
	LIST_ENTRY HashLinks;
	PVOID SectionPointer;
	UINT32 CheckSum;
	UINT32 TimeDateStamp;
	PVOID LoadedImports;
	PVOID EntryPointActivationContext;
	PVOID PatchInformation;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

// 全局变量
PDRIVER_OBJECT g_pDriver;

// 函数声明
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING RegPath);
VOID DriverUnload(PDRIVER_OBJECT pDriver);
NTSTATUS IrpCreateProc(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS IrpCloseProc(PDEVICE_OBJECT pDevObj, PIRP pIrp);
NTSTATUS IrpDeviceControlProc(PDEVICE_OBJECT pDevObj, PIRP pIrp);
VOID GetKernelBase(PDRIVER_OBJECT driver, PVOID *pKrnlBase, PUINT32 uKrnlImageSize);
PVOID MemorySearch(PVOID bytecode, UINT32 bytecodeLen, PVOID pBeginAddress, PVOID pEndAddress);
void KillPid(ULONG uPid, PDRIVER_OBJECT driver);

// 入口函数
NTSTATUS DriverEntry(PDRIVER_OBJECT pDriver, PUNICODE_STRING RegPath)
{
	NTSTATUS status;
	ULONG uIndex = 0;
	PDEVICE_OBJECT pDeviceObj = NULL; // 设备对象指针
	UNICODE_STRING DeviceName; // 设备名，0环用
	UNICODE_STRING SymbolicLinkName; // 符号链接名，3环用

	g_pDriver = pDriver;

	// 创建设备名称
	RtlInitUnicodeString(&DeviceName,DEVICE_NAME);
	// 创建设备
	status = IoCreateDevice(pDriver,0,&DeviceName,FILE_DEVICE_UNKNOWN,FILE_DEVICE_SECURE_OPEN,FALSE,&pDeviceObj);
	if (status != STATUS_SUCCESS)
	{
		IoDeleteDevice(pDeviceObj);
		DbgPrint("创建设备失败.\n");
		return status;
	}
	DbgPrint("创建设备成功.\n");
	// 设置交互数据的方式
	pDeviceObj->Flags |= DO_BUFFERED_IO;
	// 创建符号链接
	RtlInitUnicodeString(&SymbolicLinkName, DRIVER_LINK);
	IoCreateSymbolicLink(&SymbolicLinkName, &DeviceName);
	// 设置分发函数
	pDriver->MajorFunction[IRP_MJ_CREATE] = IrpCreateProc;
	pDriver->MajorFunction[IRP_MJ_CLOSE] = IrpCloseProc;
	pDriver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = IrpDeviceControlProc;
	// 设置卸载函数
	pDriver->DriverUnload = DriverUnload;
	return STATUS_SUCCESS;
}

// 卸载驱动
VOID DriverUnload(PDRIVER_OBJECT pDriver)
{
	UNICODE_STRING SymbolicLinkName;
	// 删除符号链接，删除设备
	RtlInitUnicodeString(&SymbolicLinkName, DRIVER_LINK);
	IoDeleteSymbolicLink(&SymbolicLinkName);
	IoDeleteDevice(pDriver->DeviceObject);
	DbgPrint("驱动卸载成功\n");
}

// 不设置这个函数，则Ring3调用CreateFile会返回1
// IRP_MJ_CREATE 处理函数
NTSTATUS IrpCreateProc(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	DbgPrint("应用层连接设备.\n");
	// 返回状态如果不设置，Ring3返回值是失败
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

// IRP_MJ_CLOSE 处理函数
NTSTATUS IrpCloseProc(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	DbgPrint("应用层断开连接设备.\n");
	// 返回状态如果不设置，Ring3返回值是失败
	pIrp->IoStatus.Status = STATUS_SUCCESS;
	pIrp->IoStatus.Information = 0;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

// IRP_MJ_DEVICE_CONTROL 处理函数
NTSTATUS IrpDeviceControlProc(PDEVICE_OBJECT pDevObj, PIRP pIrp)
{
	// DbgPrint("IrpDeviceControlProc.\n");
	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	PIO_STACK_LOCATION pIrpStack;
	ULONG uIoControlCode;
	PVOID pIoBuffer;
	ULONG uInLength;
	ULONG uOutLength;
	ULONG uPid; // 要关闭的进程号
	ULONG uRet; // PspTerminateProcess 返回值返回给3环

	// 设置临时变量的值
	uPid = uRet = 0;
	// 获取IRP数据
	pIrpStack = IoGetCurrentIrpStackLocation(pIrp);
	// 获取控制码
	uIoControlCode = pIrpStack->Parameters.DeviceIoControl.IoControlCode;
	// 获取缓冲区地址（输入输出是同一个）
	pIoBuffer = pIrp->AssociatedIrp.SystemBuffer;
	// Ring3 发送数据的长度
	uInLength = pIrpStack->Parameters.DeviceIoControl.InputBufferLength;
	// Ring0 发送数据的长度
	uOutLength = pIrpStack->Parameters.DeviceIoControl.OutputBufferLength;

	switch (uIoControlCode)
	{
	case OPERKILLPID:
		{
			// 读取缓冲区
			memcpy(&uPid,pIoBuffer,4);
			// 调用 PspTerminateProcess
			KillPid(uPid,g_pDriver);
			// 写入缓冲区
			memcpy(pIoBuffer, &uRet, 4);
			// 设置状态
			pIrp->IoStatus.Information = 4;
			status = STATUS_SUCCESS;
			break;
		}
	}

	// 返回状态如果不设置，Ring3返回值是失败
	pIrp->IoStatus.Status = status;
	IoCompleteRequest(pIrp, IO_NO_INCREMENT);
	return STATUS_SUCCESS;
}

// 获取内核基址，大小
VOID GetKernelBase(PDRIVER_OBJECT driver, PVOID *pKrnlBase, PUINT32 uKrnlImageSize)
{
	PLDR_DATA_TABLE_ENTRY pLdteHead; // 内核模块链表头
	PLDR_DATA_TABLE_ENTRY pLdteCur; // 遍历指针
	UNICODE_STRING usKrnlBaseDllName; // 内核模块名

	RtlInitUnicodeString(&usKrnlBaseDllName,L"ntoskrnl.exe");
	pLdteHead = (PLDR_DATA_TABLE_ENTRY)driver->DriverSection;
	pLdteCur = pLdteHead;
	do 
	{
		PLDR_DATA_TABLE_ENTRY pLdte = CONTAINING_RECORD(pLdteCur, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
		//DbgPrint("DllBase: %p, SizeOfImage: %08X %wZ\n", pLdteCur->DllBase, pLdteCur->SizeOfImage, &(pLdteCur->FullDllName));
		if (RtlCompareUnicodeString(&pLdteCur->BaseDllName, &usKrnlBaseDllName, TRUE) == 0)
		{
			*pKrnlBase = pLdteCur->DllBase;
			*uKrnlImageSize = pLdteCur->SizeOfImage;
			return;
		}
		pLdteCur = (PLDR_DATA_TABLE_ENTRY)pLdteCur->InLoadOrderLinks.Flink;
	} while (pLdteHead != pLdteCur);
	return;
}

// 特征码搜索
PVOID MemorySearch(PVOID bytecode, UINT32 bytecodeLen, PVOID pBeginAddress, PVOID pEndAddress)
{
	PVOID pCur = pBeginAddress;
	while (pCur != pEndAddress)
	{
		if (RtlCompareMemory(bytecode,pCur,bytecodeLen) == bytecodeLen)
		{
			return pCur;
		}
		((UINT32)pCur)++;
	}
	return 0;
}

// 杀进程
void KillPid(ULONG uPid, PDRIVER_OBJECT driver)
{
	typedef NTSTATUS (*_PspTerminateProcess)(PEPROCESS pEprocess, NTSTATUS ExitCode);
	_PspTerminateProcess PspTerminateProcess;
	UINT32 bytecode[] = {
		0x0124a164, 0x758b0000, 0x44703b08, 0x0db80775,
		0xebc00000, 0xbe8d575a, 0x00000248, 0x200147f6,
		0x868d1274, 0x00000174
	};
	PVOID pKrnlBase; // 内核基址
	UINT32 uKrnlImageSize; // 内核大小
	PEPROCESS pEprocess; // 要关闭的进程的EPROCESS

	// 获取内核模块基址和大小
	GetKernelBase(driver, &pKrnlBase, &uKrnlImageSize);
	//DbgPrint("内核基址: %p，大小: %X\n", pKrnlBase, uKrnlImageSize);
	// 获取 PspTerminateProcess 函数地址
	PspTerminateProcess = (_PspTerminateProcess)((UINT32)MemorySearch( \
		bytecode,sizeof(bytecode),pKrnlBase,(PVOID)((UINT32)pKrnlBase+uKrnlImageSize)) - 6);
	//DbgPrint("PspTerminateProcess: %p\n", PspTerminateProcess);
	// 根据PID获取EPROCESS
	PsLookupProcessByProcessId((HANDLE)uPid,&pEprocess);
	// 调用 PspTerminateProcess 关闭进程
	PspTerminateProcess(pEprocess, 0);
}
