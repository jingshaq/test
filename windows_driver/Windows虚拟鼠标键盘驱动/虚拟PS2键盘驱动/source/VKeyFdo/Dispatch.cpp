/////////////////////////////////////////////////////////////////////////////
//	dispatch.cpp:	Other IRP handlers
/////////////////////////////////////////////////////////////////////////////
//	Create			Handle Create/Open file IRP
//	Close			Handle Close file IRPs
//	Read			Handle Read IRPs
//	Write			Handle Write IRPs
//	DeviceControl	Handle DeviceIoControl IRPs
//	SystemControl	Handle WMI IRPs
/////////////////////////////////////////////////////////////////////////////

#include "VKeyFdo.h"
#include "..\inc\vkIoctl.h"

/////////////////////////////////////////////////////////////////////////////
//	Create:
//
//	Description:
//		Handle IRP_MJ_CREATE requests
//
//	Arguments:
//		Pointer to our FDO
//		Pointer to the IRP
//			IrpStack->Parameters.Create.xxx has create parameters
//			IrpStack->FileObject->FileName has file name of device
//
//	Return Value:
//		This function returns STATUS_XXX

PDEVICE_OBJECT FunctionDevice  = 0;
PDEVICE_OBJECT KeyboardClassDO = 0;
int UnitId = 0;
KeyboardClassServiceCallback SeviceCallback = 0;

NTSTATUS Create(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	if( (SeviceCallback == 0) || (0 == KeyboardClassDO) )
	{
		return CompleteIrp(Irp,STATUS_DEVICE_OFF_LINE,0);
	}	// Complete successfully

	return CompleteIrp(Irp,STATUS_SUCCESS,0);
}

/////////////////////////////////////////////////////////////////////////////
//	Close:
//
//	Description:
//		Handle IRP_MJ_CLOSE requests
//
//	Arguments:
//		Pointer to our FDO
//		Pointer to the IRP
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS Close(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	// Complete successfully
	return CompleteIrp(Irp,STATUS_SUCCESS,0);
}

/////////////////////////////////////////////////////////////////////////////
//	DeviceControl:
//
//	Description:
//		Handle IRP_MJ_DEVICE_CONTROL requests
//
//	Arguments:
//		Pointer to our FDO
//		Pointer to the IRP
//			Buffered:	AssociatedIrp.SystemBuffer (and IrpStack->Parameters.DeviceIoControl.Type3InputBuffer)
//			Direct:		MdlAddress
//
//			IrpStack->Parameters.DeviceIoControl.InputBufferLength
//			IrpStack->Parameters.DeviceIoControl.OutputBufferLength 
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS DeviceControl(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	if(FunctionDevice != fdo)
	{
		PIO_STACK_LOCATION IrpStack = IoGetCurrentIrpStackLocation(Irp);
		ULONG CtlCode = IrpStack->Parameters.DeviceIoControl.IoControlCode;
		DbgPrint("device io ctrl code = %x\n",CtlCode);

		PDEVICE_EXTENSION dx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
		IoSkipCurrentIrpStackLocation(Irp);
		return IoCallDriver( dx->NextStackDevice, Irp);
	}

	PIO_STACK_LOCATION IrpStack = IoGetCurrentIrpStackLocation(Irp);

	NTSTATUS status = STATUS_INVALID_DEVICE_REQUEST;
	ULONG BytesTxd = 0;

	ULONG ControlCode    = IrpStack->Parameters.DeviceIoControl.IoControlCode;
	PVK_SENDKEY ioBuffer = (PVK_SENDKEY)Irp->AssociatedIrp.SystemBuffer;
	ULONG InputLength    = IrpStack->Parameters.DeviceIoControl.InputBufferLength;
	//ULONG OutputLength   = IrpStack->Parameters.DeviceIoControl.OutputBufferLength;

	switch( ControlCode)
	{
	case IOCTL_SENDKEY:
		if( (ioBuffer==0) || (InputLength < sizeof(VK_SENDKEY)) || (ioBuffer->Count > 5) )
		{
			status = STATUS_INVALID_PARAMETER;
			break;
		}

		// Send data to KeyboardClass
		{
		ULONG NumSend = 0;
		MYKEYBOARD_INPUT_DATA Data[6];
		for(int i =0 ; i< ioBuffer->Count ; i++)
		{
			if( ioBuffer->Keys[i].Press == 0 )
			{
				Data[i].Flags = KEY_BREAK;
			}
			Data[i].UnitId   = UnitId ;
			Data[i].MakeCode = ioBuffer->Keys[i].Code;
		}

		SeviceCallback(KeyboardClassDO,Data,&Data[ioBuffer->Count],&NumSend);
		}

		status = STATUS_SUCCESS;
		break;

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
	}

	// Complete IRP
	return CompleteIrp(Irp,status,BytesTxd);
}

/////////////////////////////////////////////////////////////////////////////
//	InternalControl:
//
//	Description:
//		Handle IRP_MJ_INTERNAL_DEVICE_CONTROL requests
//	Return Value:
//		This function returns STATUS_XXX
NTSTATUS InternalControl(IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	PDEVICE_EXTENSION dx = (PDEVICE_EXTENSION)fdo->DeviceExtension;

	PIO_STACK_LOCATION              irpStack;
	irpStack = IoGetCurrentIrpStackLocation(Irp);

	ULONG CtlCode = irpStack->Parameters.DeviceIoControl.IoControlCode;
	DbgPrint("internal = %x\n",CtlCode);

	switch(CtlCode)
	{
	case IOCTL_INTERNAL_KEYBOARD_CONNECT:
		if (irpStack->Parameters.DeviceIoControl.InputBufferLength >= sizeof(CONNECT_DATA))
		{
			PCONNECT_DATA connectData = ((PCONNECT_DATA)(irpStack->Parameters.DeviceIoControl.Type3InputBuffer));
			KeyboardClassDO = connectData->ClassDeviceObject;
			SeviceCallback  = (KeyboardClassServiceCallback)connectData->ClassService;

			DbgPrint("KeyClass = %x,Service Callback = %x\n",KeyboardClassDO,SeviceCallback);
			return CompleteIrp(Irp,STATUS_SUCCESS,0);
		}
		break;
	case IOCTL_KEYBOARD_QUERY_ATTRIBUTES:
		if(irpStack->Parameters.DeviceIoControl.InputBufferLength>=sizeof(KEYBOARD_UNIT_ID_PARAMETER))
		{
			PKEYBOARD_UNIT_ID_PARAMETER puip = (PKEYBOARD_UNIT_ID_PARAMETER) Irp->AssociatedIrp.SystemBuffer ;
			UnitId = puip-> UnitId;
			DbgPrint("id = %x\n",UnitId);
		}
		else
		{
			DbgPrint("id = 0\n");
		}

		if (irpStack->Parameters.DeviceIoControl.OutputBufferLength <sizeof(KEYBOARD_ATTRIBUTES))
		{
			return CompleteIrp(Irp,STATUS_BUFFER_TOO_SMALL,0);
		}
		else
		{
			PKEYBOARD_ATTRIBUTES pka = (PKEYBOARD_ATTRIBUTES) Irp->AssociatedIrp.SystemBuffer ;
			pka->KeyboardIdentifier.Type    = 2;
			pka->KeyboardIdentifier.Subtype = 0;
			pka->KeyboardMode               = 2;
			pka->NumberOfFunctionKeys       = 0;
			pka->NumberOfIndicators         = 0;
			pka->NumberOfKeysTotal          = 101;
			pka->InputDataQueueLength       = 256;
			pka->KeyRepeatMinimum.UnitId    = UnitId;
			pka->KeyRepeatMinimum.Rate      = 15;
			pka->KeyRepeatMinimum.Delay     = 100;
			pka->KeyRepeatMaximum.UnitId    = UnitId;
			pka->KeyRepeatMaximum.Rate      = 150;
			pka->KeyRepeatMaximum.Delay     = 10;
			return CompleteIrp(Irp,STATUS_SUCCESS,sizeof(KEYBOARD_ATTRIBUTES));
		}
	case IOCTL_KEYBOARD_SET_TYPEMATIC:
		DbgPrint("IOCTL_KEYBOARD_SET_TYPEMATIC\n");
		break;
	case IOCTL_KEYBOARD_SET_INDICATORS:
		DbgPrint("IOCTL_KEYBOARD_SET_INDICATORS\n");
		break;
	case IOCTL_KEYBOARD_QUERY_TYPEMATIC:
		DbgPrint("IOCTL_KEYBOARD_QUERY_TYPEMATIC\n");
		break;
	case IOCTL_KEYBOARD_QUERY_INDICATORS:
		DbgPrint("IOCTL_KEYBOARD_QUERY_INDICATORS\n");
		break;
	case IOCTL_KEYBOARD_QUERY_INDICATOR_TRANSLATION:
		DbgPrint("IOCTL_KEYBOARD_QUERY_INDICATOR_TRANSLATION\n");
		break;
	case IOCTL_KEYBOARD_INSERT_DATA:
		DbgPrint("IOCTL_KEYBOARD_INSERT_DATA\n");
		break;
	}

	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver( dx->NextStackDevice, Irp);
}

/////////////////////////////////////////////////////////////////////////////
//	SystemControl:
//
//	Description:
//		Handle IRP_MJ_SYSTEM_CONTROL requests
//
//	Arguments:
//		Pointer to our FDO
//		Pointer to the IRP
//			Various minor parameters
//			IrpStack->Parameters.WMI.xxx has WMI parameters
//
//	Return Value:
//		This function returns STATUS_XXX

NTSTATUS SystemControl(	IN PDEVICE_OBJECT fdo,IN PIRP Irp)
{
	if(FunctionDevice == fdo)
	{
		return CompleteIrp(Irp,STATUS_UNSUCCESSFUL,0);
	}

	// Just pass to lower driver
	IoSkipCurrentIrpStackLocation(Irp);
	PDEVICE_EXTENSION dx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	return IoCallDriver( dx->NextStackDevice, Irp);
}

/////////////////////////////////////////////////////////////////////////////
//	CompleteIrp:	Sets IoStatus and completes the IRP

NTSTATUS CompleteIrp( PIRP Irp, NTSTATUS status, ULONG info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp,IO_NO_INCREMENT);
	return status;
}

/////////////////////////////////////////////////////////////////////////////

