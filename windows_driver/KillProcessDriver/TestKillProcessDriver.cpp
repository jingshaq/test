#include "stdafx.h"
#include <Windows.h>

#define DRIVER_NAME L"HbgProcessKillerDriver"
#define DRIVER_PATH L"HbgProcessKillerDriver.sys"
#define DRIVER_LINK L"\\\\.\\HbgProcessKillerDriverLnk"

#define OPERKILLPID CTL_CODE(FILE_DEVICE_UNKNOWN,0x800,METHOD_BUFFERED,FILE_ANY_ACCESS)

void KillPID()
{
	HANDLE hDevice = CreateFileW(DRIVER_LINK, GENERIC_READ|GENERIC_WRITE,0,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	if (hDevice == INVALID_HANDLE_VALUE)
	{
		printf("创建设备失败. %d\n", GetLastError());
		return;
	}
	DWORD InBuffer;
	DWORD OutBuffer;	
	DWORD dwOut;
	printf("请输入你要干掉的进程PID：");
	scanf("%d", &InBuffer);
	DeviceIoControl(hDevice,OPERKILLPID,&InBuffer,4,&OutBuffer,4,&dwOut,NULL);	
	// 关闭设备
	CloseHandle(hDevice);
}

int _tmain(int argc, _TCHAR* argv[])
{
	KillPID();
	getchar();
	return 0;
}