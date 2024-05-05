#include <Uefi.h>
#include <Library/UefiLib.h>

EFI_STATUS
EFIAPI
EntryPoint (
	IN EFI_HANDLE        ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable
	) {
	Print(L"Hello World!\n");
	SystemTable->BootServices->Stall(5000000);
	return EFI_SUCCESS;
}
