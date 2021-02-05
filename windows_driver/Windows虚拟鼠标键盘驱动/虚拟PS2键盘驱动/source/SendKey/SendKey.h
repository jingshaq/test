// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SENDKEY_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SENDKEY_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SENDKEY_EXPORTS
#define SENDKEY_API __declspec(dllexport)
#else
#define SENDKEY_API __declspec(dllimport)
#endif

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <winioctl.h>
#include "..\inc\vkIoctl.h"



extern "C" SENDKEY_API int VKSendKey(PVK_SENDKEY key);
extern "C" SENDKEY_API HANDLE VKOpenVirtualKey();
extern "C" SENDKEY_API int VKCloseVirtualKey(HANDLE VKHandle);
extern "C" SENDKEY_API int VKSendKeyEx(HANDLE VKHandle,PVK_SENDKEY key);
