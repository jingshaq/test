//#include <ntddk.h>
#include <ntifs.h>

#define DEVICE_NAME L"\\Device\\MyFirstDevice"
#define SYM_NAME	L"\\??\\MyFirstDevice"

VOID nothing(HANDLE ppid, HANDLE mypid, BOOLEAN bcreate)
{
	DbgPrint("ProcessNotify\n");
}

VOID DrvUnload(PDRIVER_OBJECT pdriver) 
{
	KdPrint(("Driver Unload.......\n"));
	PsSetCreateProcessNotifyRoutine(nothing, TRUE);
	if (pdriver->DeviceObject)
	{
		IoDeleteDevice(pdriver->DeviceObject);
		UNICODE_STRING symname = { 0 };
		RtlInitUnicodeString(&symname, SYM_NAME);
		IoDeleteSymbolicLink(&symname);
		KdPrint(("Driver Unload.......Finished\n"));
	}
}

NTSTATUS MyCreate(PDEVICE_OBJECT pdevice, PIRP pirp)
{
	NTSTATUS status = STATUS_SUCCESS;
	KdPrint(("My Device has been opened.\n"));

	pirp->IoStatus.Status = status;
	pirp->IoStatus.Information = 0;

	IoCompleteRequest(pirp, IO_NO_INCREMENT);
	
	return STATUS_SUCCESS;
}

NTSTATUS MyClose(PDEVICE_OBJECT pdevice, PIRP pirp)
{
	NTSTATUS status = STATUS_SUCCESS;
	KdPrint(("My Device has been closed.\n"));

	pirp->IoStatus.Status = status;
	pirp->IoStatus.Information = 0;

	IoCompleteRequest(pirp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS MyCleanUp(PDEVICE_OBJECT pdevice, PIRP pirp)
{
	NTSTATUS status = STATUS_SUCCESS;
	KdPrint(("My Device has been clean.\n"));

	pirp->IoStatus.Status = status;
	pirp->IoStatus.Information = 0;

	IoCompleteRequest(pirp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS DriverEntry(IN PDRIVER_OBJECT driver, IN PUNICODE_STRING regPath) 
{
	NTSTATUS status = STATUS_SUCCESS;
	UNICODE_STRING devicename = { 0 };
	PDEVICE_OBJECT pdevice = NULL;

	KdPrint(("KdPrint DriverEntry---%wZ.......\n", regPath));
	DbgPrint("DbgPrint DriverEntry---%wZ.......\n", regPath);

	driver->DriverUnload = DrvUnload;

	RtlInitUnicodeString(&devicename, DEVICE_NAME);

	// Create Device
	status = IoCreateDevice(driver, 0, &devicename, FILE_DEVICE_UNKNOWN, 0, TRUE, &pdevice);
	if (!NT_SUCCESS(status))
	{
		KdPrint(("Create Device Fail: %x \n", status));
		return status;
	}

	// Create Symbolic Link
	UNICODE_STRING myname = { 0 };
	RtlInitUnicodeString(&myname, SYM_NAME);
	status = IoCreateSymbolicLink(&myname, &devicename);
	if(!NT_SUCCESS(status))
	{
		KdPrint(("Create Symbolic Link Fail: %x \n", status));
		IoDeleteDevice(pdevice);
		return status;
	}

	// Register Operations: Create / Close / Read / Write ......
	driver->MajorFunction[IRP_MJ_CREATE] = MyCreate;
	driver->MajorFunction[IRP_MJ_CLOSE] = MyClose;
	driver->MajorFunction[IRP_MJ_CLEANUP] = MyCleanUp;

	return STATUS_SUCCESS;
}
