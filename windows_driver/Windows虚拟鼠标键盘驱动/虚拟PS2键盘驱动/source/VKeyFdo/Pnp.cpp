/////////////////////////////////////////////////////////////////////////////
//	pnp.cpp:		Plug and Play and Power IRP handlers
/////////////////////////////////////////////////////////////////////////////
//	AddDevice	Add device routine
//	Pnp			PNP IRP dispatcher
//	Power		POWER IRP dispatcher
/////////////////////////////////////////////////////////////////////////////

#define INITGUID

#include "VKeyFdo.h"
#include "guids.h"
#include "..\inc\vkIoctl.h"

#pragma code_seg("PAGE")	// start PAGE section

/////////////////////////////////////////////////////////////////////////////
//	AddDevice:
//
//	Description:
//		Cope with a new Pnp device being added here.
//		Usually just attach to the top of the driver stack.
//		Do not talk to device here!
//
//	Arguments:
//		Pointer to the Driver object
//		Pointer to Physical Device Object
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject,IN PDEVICE_OBJECT pdo)
{
	DbgPrint("add device\n");

	NTSTATUS status;
	PDEVICE_OBJECT fdo;

	// Create our Functional Device Object in fdo
	status = IoCreateDevice (DriverObject,
		sizeof(DEVICE_EXTENSION),
		0,
		FILE_DEVICE_KEYBOARD,
		0,
		true,	// Not exclusive
		&fdo);
	if(!NT_SUCCESS(status))
	{
		return status;
	}

	// Remember fdo in our device extension
	PDEVICE_EXTENSION dx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	dx->fdo = fdo;

	// Attach to the driver stack below us
	dx->NextStackDevice = IoAttachDeviceToDeviceStack(fdo,pdo);

	// Set fdo flags appropriately
	fdo->Flags |= DO_BUFFERED_IO|DO_POWER_PAGABLE;
	fdo->Flags &= ~DO_DEVICE_INITIALIZING;

	DbgPrint("add device ok\n");

	return STATUS_SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////
//	Pnp:
//
//	Description:
//		Handle IRP_MJ_PNP requests
//
//	Arguments:
//		Pointer to our FDO
//		Pointer to the IRP
//			Various minor codes
//				IrpStack->Parameters.QueryDeviceRelations
//				IrpStack->Parameters.QueryInterface
//				IrpStack->Parameters.DeviceCapabilities
//				IrpStack->Parameters.FilterResourceRequirements
//				IrpStack->Parameters.ReadWriteConfig
//				IrpStack->Parameters.SetLock
//				IrpStack->Parameters.QueryId
//				IrpStack->Parameters.QueryDeviceText
//				IrpStack->Parameters.UsageNotification
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS Pnp(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	if(FunctionDevice == fdo)
	{
		return CompleteIrp(Irp,STATUS_UNSUCCESSFUL,0);
	}

	PDEVICE_EXTENSION dx=(PDEVICE_EXTENSION)fdo->DeviceExtension;

	// Remember minor function
	PIO_STACK_LOCATION IrpStack = IoGetCurrentIrpStackLocation(Irp);
	ULONG MinorFunction = IrpStack->MinorFunction;

	// Just pass to lower driver
	IoSkipCurrentIrpStackLocation(Irp);
	NTSTATUS status = IoCallDriver( dx->NextStackDevice, Irp);

	// Device removed
	if( MinorFunction==IRP_MN_REMOVE_DEVICE)
	{
		// unattach from stack
		if (dx->NextStackDevice)
		{
			IoDetachDevice(dx->NextStackDevice);
		}

		// delete our fdo
		IoDeleteDevice(fdo);
	}

	return status;
}

/////////////////////////////////////////////////////////////////////////////
//	Power:
//
//	Description:
//		Handle IRP_MJ_POWER requests
//
//	Arguments:
//		Pointer to the FDO
//		Pointer to the IRP
//			IRP_MN_WAIT_WAKE:		IrpStack->Parameters.WaitWake.Xxx
//			IRP_MN_POWER_SEQUENCE:	IrpStack->Parameters.PowerSequence.Xxx
//			IRP_MN_SET_POWER:
//			IRP_MN_QUERY_POWER:		IrpStack->Parameters.Power.Xxx
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS Power(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	if(FunctionDevice == fdo)
	{
		return CompleteIrp(Irp,STATUS_UNSUCCESSFUL,0);
	}

	PDEVICE_EXTENSION dx = (PDEVICE_EXTENSION)fdo->DeviceExtension;

	// Just pass to lower driver
	PoStartNextPowerIrp( Irp);
	IoSkipCurrentIrpStackLocation(Irp);
	return PoCallDriver( dx->NextStackDevice, Irp);
}

#pragma code_seg()	// end PAGE section
