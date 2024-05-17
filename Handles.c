#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

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
	
	Status = gBS->LocateHandleBuffer (
		AllHandles,
                NULL,
                NULL,
                &HandleCount,
                &HandleBuffer
                );
	if (EFI_ERROR (Status)) 
	{
  		return Status;
	}
	
	for (UINTN Index = 0; Index < HandleCount; Index++)
	{
		Print(L"Child handle %u: %p\n", Index, HandleBuffer[Index]);
	}
	
	SystemTable->BootServices->Stall(10000000);

	if (HandleBuffer != NULL)
	{
	FreePool (HandleBuffer);
	}
	
	return EFI_SUCCESS;
}

