//	DeviceIoControl IOCTL codes supported by virtual keyboard

#ifndef VK_CODE_STRUCT
#define VK_CODE_STRUCT

#define IOCTL_TEST CTL_CODE(FILE_DEVICE_UNKNOWN,0x801,METHOD_BUFFERED,FILE_ANY_ACCESS)
#define IOCTL_SENDKEY CTL_CODE(FILE_DEVICE_UNKNOWN,0x802,METHOD_BUFFERED,FILE_ANY_ACCESS)

#define NT_DEVICE_NAME L"\\Device\\VKeyboard"
#define DOS_DEVICE_NAME L"\\DosDevices\\VKeyboard"
#define DEVICE_NAME _T("\\\\.\\VKeyboard")
#define KEYBOARDCLASS0 L"\\Device\\KeyboardClass0"

typedef struct
{
	int Count;
	struct
	{
		int Press;
		int Code;
	}Keys[6];
}VK_SENDKEY,*PVK_SENDKEY;

#endif