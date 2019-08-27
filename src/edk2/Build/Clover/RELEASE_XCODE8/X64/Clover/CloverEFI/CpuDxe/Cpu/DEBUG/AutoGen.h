/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_10527025_78B2_4d3e_A9DF_41E75C220F5A
#define _AUTOGENH_10527025_78B2_4d3e_A9DF_41E75C220F5A

#ifdef __cplusplus
extern "C" {
#endif

#include <PiDxe.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x10527025, 0x78B2, 0x4d3e, {0xA9, 0xDF, 0x41, 0xE7, 0x5C, 0x22, 0x0F, 0x5A}}

// Guids
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;

// Protocols
extern EFI_GUID gEfiCpuArchProtocolGuid;
extern EFI_GUID gEfiLegacy8259ProtocolGuid;
extern EFI_GUID gMsgLogProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
InitializeCpu (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
