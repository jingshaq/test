/////////////////////////////////////////////////////////////////////////////
//	init.cpp:		Driver initialization code
/////////////////////////////////////////////////////////////////////////////
//	DriverEntry		Initialisation entry point
//	Unload		Unload driver routine
/////////////////////////////////////////////////////////////////////////////

#include "VKeyFdo.h"
#include "..\inc\vkIoctl.h"

extern "C"
{
#include "hidport.h"
}

#pragma code_seg("INIT") // start INIT section

/////////////////////////////////////////////////////////////////////////////
//	DriverEntry:
//
//	Description:
//		This function initializes the driver, and creates
//		any objects needed to process I/O requests.
//
//	Arguments:
//		Pointer to the Driver object
//		Registry path string for driver service key
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject,IN PUNICODE_STRING RegistryPath)
{
	// Export other driver entry points...
	DriverObject->DriverExtension->AddDevice = AddDevice;

	DriverObject->MajorFunction[IRP_MJ_CREATE                 ] = Create;
	DriverObject->MajorFunction[IRP_MJ_CLOSE                  ] = Close;
	DriverObject->MajorFunction[IRP_MJ_PNP                    ] = Pnp;
	DriverObject->MajorFunction[IRP_MJ_POWER                  ] = Power;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL         ] = DeviceControl;
	DriverObject->MajorFunction[IRP_MJ_INTERNAL_DEVICE_CONTROL] = InternalControl;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL         ] = SystemControl;

	extern PDEVICE_OBJECT  FunctionDevice;
	UNICODE_STRING         deviceNameUnicodeString;
	RtlInitUnicodeString(&deviceNameUnicodeString, NT_DEVICE_NAME);

	NTSTATUS status = STATUS_SUCCESS;
	status = IoCreateDevice(DriverObject, 0,
		&deviceNameUnicodeString,FILE_DEVICE_UNKNOWN,
		0, false, &FunctionDevice);

	if (!NT_SUCCESS(status))
	{
		return status;
	}

	UNICODE_STRING deviceLinkUnicodeString;
	RtlInitUnicodeString(&deviceLinkUnicodeString, DOS_DEVICE_NAME);
	status = IoCreateSymbolicLink(&deviceLinkUnicodeString, &deviceNameUnicodeString);
	if (!NT_SUCCESS(status))
	{
		if (FunctionDevice)
		{
			IoDeleteDevice(FunctionDevice);
			return status;
		}
	}

	// Set fdo flags appropriately
	FunctionDevice->Flags |= DO_BUFFERED_IO|DO_POWER_PAGABLE;
	FunctionDevice->Flags &= ~DO_DEVICE_INITIALIZING;

	return STATUS_SUCCESS;
}
#pragma code_seg() // end INIT section

//////////////////////////////////////////////////////////////////////////////
//	Unload
//
//	Description:
//		Unload the driver by removing any remaining objects, etc.
//
//	Arguments:
//		Pointer to the Driver object
//
//	Return Value:
//		None

#pragma code_seg("PAGE") // start PAGE section

VOID Unload(IN PDRIVER_OBJECT DriverObject)
{
}

//////////////////////////////////////////////////////////////////////////////
#pragma code_seg() // end PAGE section
