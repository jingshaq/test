//////////////////////////////////////////////////////////////////////////////
//	Copyright 2004 by leiwhere
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//	Include WDM standard header with C linkage

extern "C"
{
#include "wdm.h"
#include "kbdmou.h"
#include <ntddkbd.h>
}

typedef VOID (*KeyboardClassServiceCallback)(
	IN PDEVICE_OBJECT DeviceObject,
	IN PKEYBOARD_INPUT_DATA InputDataStart,
	IN PKEYBOARD_INPUT_DATA InputDataEnd,
	IN OUT PULONG InputDataConsumed);

/////////////////////////////////////////////////////////////////////////////
//	Our device extension
typedef struct
{
	PDEVICE_OBJECT	fdo;
	PDEVICE_OBJECT	NextStackDevice;
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;

extern PDEVICE_OBJECT FunctionDevice;

class MYKEYBOARD_INPUT_DATA : public KEYBOARD_INPUT_DATA
{
public:
	MYKEYBOARD_INPUT_DATA()
	{
		RtlZeroMemory(this,sizeof(MYKEYBOARD_INPUT_DATA));
	}
};

/////////////////////////////////////////////////////////////////////////////
// Forward declarations of global functions

VOID Unload(IN PDRIVER_OBJECT DriverObject);

NTSTATUS Power(	IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS Pnp(IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject,IN PDEVICE_OBJECT pdo);

NTSTATUS Create(IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS Close(IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS DeviceControl(	IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS InternalControl(IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS SystemControl(	IN PDEVICE_OBJECT fdo,IN PIRP Irp);

NTSTATUS CompleteIrp( PIRP Irp, NTSTATUS status, ULONG info);

/////////////////////////////////////////////////////////////////////////////
