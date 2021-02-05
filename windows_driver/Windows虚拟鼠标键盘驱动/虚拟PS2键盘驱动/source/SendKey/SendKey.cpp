// SendKey.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "SendKey.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

extern "C" SENDKEY_API int VKSendKey(PVK_SENDKEY key)
{
	HANDLE file = CreateFile(DEVICE_NAME,GENERIC_WRITE|GENERIC_READ,0,0,OPEN_EXISTING,0,0);
	if(file == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	DWORD BytesRet = 0;
	int ret = DeviceIoControl(file,IOCTL_SENDKEY,key,sizeof(VK_SENDKEY),0,0,&BytesRet,0);
	if(ret == 0)
	{
		return false;
	}

	CloseHandle(file);
	return true;
}

extern "C" SENDKEY_API HANDLE VKOpenVirtualKey()
{
	return CreateFile(DEVICE_NAME,GENERIC_WRITE|GENERIC_READ,0,0,OPEN_EXISTING,0,0);
}

extern "C" SENDKEY_API int VKCloseVirtualKey(HANDLE VKHandle)
{
	return CloseHandle(VKHandle);
}

extern "C" SENDKEY_API int VKSendKeyEx(HANDLE VKHandle,PVK_SENDKEY key)
{
	DWORD BytesRet = 0;
	return DeviceIoControl(VKHandle,IOCTL_SENDKEY,key,sizeof(VK_SENDKEY),0,0,&BytesRet,0);
}
