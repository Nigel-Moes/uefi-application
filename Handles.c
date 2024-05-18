#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Uefi.h>

// Function to print a GUID to the console
VOID PrintGuid(EFI_GUID Guid)
{
	CHAR16 GuidStr[36];
	UnicodeSPrint(GuidStr, sizeof(GuidStr), L"%g", &Guid);
	Print(GuidStr);
}

// Function to print the GUIDs that are installed on a handle
EFI_STATUS PrintGuidsPerHandle(IN EFI_HANDLE Handle)
{
	EFI_STATUS	Status;
	EFI_GUID	**GuidBuffer;
	UINTN		GuidCount;
	
	// Retrieve the list of all protocol GUIDs and place them in a GUID buffer
	Status = gBS->ProtocolsPerHandle(Handle, &GuidBuffer, &GuidCount);
	if (EFI_ERROR(Status)) 
	{
		Print(L"Failed to get protocol GUIDs: %r\n", Status);
  		return Status;
	}
	
	// Print the GUIDs to the console
	for (UINTN Index = 0; Index < GuidCount; Index++)
	{
		EFI_GUID *Guid = GuidBuffer[Index];
		Print(L"\t");
		PrintGuid(*Guid);
		Print(L"\n");
	}
	
	// Free memory allocated to the GUID buffer	
	if (GuidBuffer != NULL)
	{
	FreePool(GuidBuffer);
	}
	
	return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
UefiMain (
	IN EFI_HANDLE		ImageHandle,
	IN EFI_SYSTEM_TABLE	*SystemTable
	) 
{
	EFI_STATUS	Status;
	UINTN           HandleCount;
	EFI_HANDLE      *HandleBuffer;
	
	// Retrieve the list of all handles in the handle database and place them in a handle buffer
	Status = gBS->LocateHandleBuffer(AllHandles, NULL, NULL, &HandleCount, &HandleBuffer);
	if (EFI_ERROR(Status)) 
	{
		Print(L"Failed to locate handles: %r\n", Status);
  		return Status;
	}
	
	// Loop through the handles in the handle buffer
	for (UINTN Index = 0; Index < HandleCount; Index++)
	{
		EFI_HANDLE Handle = HandleBuffer[Index];
		Print(L"Handle %u: %p\n", Index, Handle);
		
		// Print the protocol interface GUIDs that are installed on the handle
		Print(L"\tProtocols:\n");
		Status = PrintGuidsPerHandle(Handle);
		if (EFI_ERROR(Status))
		{
		Print(L"Failed to print protocol GUIDs for handle %u, %p: %r\n", Index, Handle, Status);
  		return Status;
		}
	}
	
	// Stall the processor for 10 seconds to be able to read the printed console output
	SystemTable->BootServices->Stall(10000000);

	// Free memory allocated to the handle buffer
	if (HandleBuffer != NULL)
	{
	FreePool(HandleBuffer);
	}
	
	return EFI_SUCCESS;
}

