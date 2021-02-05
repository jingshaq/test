// Setup.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <setupapi.h>
#include "c:\ntddk\inc\newdev.h"

#pragma comment(lib , "C:\\NTDDK\\libchk\\i386\\newdev.lib")
#pragma comment(lib , "Setupapi.lib")

using namespace std;

///////////////////////////////////////////////////////////////////////////

//GUID_CLASS_KEYBOARD
GUID KeyboardClass = {0x4D36E96B,0xE325,0x11CE,0xBF,0xC1,0x08,0x00,0x2B,0xE1,0x03,0x18};

// Hardware ID
#define HardwareIDs  "VKeyboard\0\0"
#define DeviceName   "Virtual Keyboard"

int DisplayMsg(LPCTSTR msg)
{
	return MessageBox(0,msg,"Message",MB_OK);
}

BOOL FindExistingDevice()
{
	HDEVINFO DeviceInfoSet = SetupDiGetClassDevs(0,0,0,DIGCF_ALLCLASSES|DIGCF_PRESENT|DIGCF_PROFILE);
	if (DeviceInfoSet == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	bool Found = false;

	SP_DEVINFO_DATA DeviceInfoData;
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	for (DWORD i=0;SetupDiEnumDeviceInfo(DeviceInfoSet,i,&DeviceInfoData);i++)
	{
		char buf[10240] = {0};
		DWORD buffersize = sizeof(buf);
		DWORD DataT = 0;

		if(!SetupDiGetDeviceRegistryProperty(DeviceInfoSet,&DeviceInfoData,
			SPDRP_HARDWAREID,
			&DataT,
			(PBYTE)buf,
			buffersize,
			&buffersize))
		{
			continue;
		}

		for (char* p=buf;*p;p++)
		{
			if (strcmp(HardwareIDs,p) == 0)
			{
				Found = true;
				break;
			}
			for(;*p;p++);
		}

		if (Found)
		{
			break;
		}
	}

	SetupDiDestroyDeviceInfoList(DeviceInfoSet);

	return Found;
}

int IsFileExist(LPCTSTR filename)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = FindFirstFile(filename, &FindFileData);
	if(hFind == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	FindClose(hFind);

	return true;
}

int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	if(FindExistingDevice())
	{
		DisplayMsg("Virtual Keyboard already installed");
		return 0;
	}

	char FileName[MAX_PATH];
	GetModuleFileName(hInstance,FileName,sizeof(FileName));

	char Drive[MAX_PATH],Path[MAX_PATH];
	_splitpath(FileName,Drive,Path,0,0);

	char infile[MAX_PATH];
	char sysfile[MAX_PATH];
	_makepath(infile,Drive,Path,"keyfdo",".inf");
	_makepath(sysfile,Drive,Path,"VKeyFdo",".sys");

	if(!IsFileExist(infile))
	{
		DisplayMsg("Can't find .INF file");
		return 0;
	}

	if(!IsFileExist(sysfile))
	{
		DisplayMsg("Can't find .SYS file");
		return 0;
	}

	HDEVINFO top;
	top=SetupDiCreateDeviceInfoList(&KeyboardClass,NULL);
	if (top == INVALID_HANDLE_VALUE)
	{
		DisplayMsg("Can't get device infolist");
		return 0;
	}

	SP_DEVINFO_DATA dev;
	dev.cbSize=sizeof(SP_DEVINFO_DATA);
	int status=SetupDiCreateDeviceInfo(top, DeviceName, &KeyboardClass, 
		DeviceName,
		NULL, DICD_GENERATE_ID, &dev);

	if(!status)
	{
		DisplayMsg("Can't create device");
		return 0;
	}

	status=SetupDiRegisterDeviceInfo(top,&dev,0,NULL,NULL,NULL);

	if(!status)
	{
		DisplayMsg("Can't register device");
		return 0;
	}

	unsigned char idstr[256] = {0};
	memcpy(idstr,HardwareIDs,sizeof(idstr));
	status=SetupDiSetDeviceRegistryProperty(top, &dev, SPDRP_HARDWAREID,idstr, sizeof(idstr));

	if(!status)
	{
		DisplayMsg("Can't set device HardwareID");
		return 0;
	}

	SetupDiDestroyDeviceInfoList(top);

	int RebootRequired;
	status=UpdateDriverForPlugAndPlayDevices(GetDesktopWindow(),(LPCTSTR)idstr,infile,0,&RebootRequired);

	return 0;
}
