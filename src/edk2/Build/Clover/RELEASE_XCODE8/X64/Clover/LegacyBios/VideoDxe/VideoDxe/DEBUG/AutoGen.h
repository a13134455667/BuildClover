/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_0B04B2ED_861C_42cd_A22F_C3AAFACCB896
#define _AUTOGENH_0B04B2ED_861C_42cd_A22F_C3AAFACCB896

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x0B04B2ED, 0x861C, 0x42cd, {0xA2, 0x2F, 0xC3, 0xAA, 0xFA, 0xCC, 0xB8, 0x96}}

// Guids
extern EFI_GUID gEfiLegacyBiosGuid;
extern EFI_GUID gEfiEventExitBootServicesGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiVirtualDiskGuid;
extern EFI_GUID gEfiVirtualCdGuid;
extern EFI_GUID gEfiPersistentVirtualDiskGuid;
extern EFI_GUID gEfiPersistentVirtualCdGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAcpi10TableGuid;

// Protocols
extern EFI_GUID gEfiVgaMiniPortProtocolGuid;
extern EFI_GUID gEfiEdidDiscoveredProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiEdidActiveProtocolGuid;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiEdidOverrideProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdBiosVideoSetTextVgaModeEnable  95U
#define _PCD_SIZE_PcdBiosVideoSetTextVgaModeEnable 1
#define _PCD_GET_MODE_SIZE_PcdBiosVideoSetTextVgaModeEnable  _PCD_SIZE_PcdBiosVideoSetTextVgaModeEnable 
#define _PCD_VALUE_PcdBiosVideoSetTextVgaModeEnable  0U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdBiosVideoSetTextVgaModeEnable;
#define _PCD_GET_MODE_BOOL_PcdBiosVideoSetTextVgaModeEnable  _gPcd_FixedAtBuild_PcdBiosVideoSetTextVgaModeEnable
//#define _PCD_SET_MODE_BOOL_PcdBiosVideoSetTextVgaModeEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdBiosVideoCheckVbeEnable  96U
#define _PCD_SIZE_PcdBiosVideoCheckVbeEnable 1
#define _PCD_GET_MODE_SIZE_PcdBiosVideoCheckVbeEnable  _PCD_SIZE_PcdBiosVideoCheckVbeEnable 
#define _PCD_VALUE_PcdBiosVideoCheckVbeEnable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdBiosVideoCheckVbeEnable;
#define _PCD_GET_MODE_BOOL_PcdBiosVideoCheckVbeEnable  _gPcd_FixedAtBuild_PcdBiosVideoCheckVbeEnable
//#define _PCD_SET_MODE_BOOL_PcdBiosVideoCheckVbeEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdBiosVideoCheckVgaEnable  97U
#define _PCD_SIZE_PcdBiosVideoCheckVgaEnable 1
#define _PCD_GET_MODE_SIZE_PcdBiosVideoCheckVgaEnable  _PCD_SIZE_PcdBiosVideoCheckVgaEnable 
#define _PCD_VALUE_PcdBiosVideoCheckVgaEnable  1U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdBiosVideoCheckVgaEnable;
#define _PCD_GET_MODE_BOOL_PcdBiosVideoCheckVgaEnable  _gPcd_FixedAtBuild_PcdBiosVideoCheckVgaEnable
//#define _PCD_SET_MODE_BOOL_PcdBiosVideoCheckVgaEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdVideoHorizontalResolution  69U
#define _PCD_PATCHABLE_VALUE_PcdVideoHorizontalResolution  ((UINT32)0U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdVideoHorizontalResolution;
#define _PCD_GET_MODE_32_PcdVideoHorizontalResolution  _gPcd_BinaryPatch_PcdVideoHorizontalResolution
#define _PCD_PATCHABLE_PcdVideoHorizontalResolution_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdVideoHorizontalResolution  _gPcd_BinaryPatch_Size_PcdVideoHorizontalResolution 
extern UINTN _gPcd_BinaryPatch_Size_PcdVideoHorizontalResolution; 
#define _PCD_SET_MODE_32_PcdVideoHorizontalResolution(Value)  (_gPcd_BinaryPatch_PcdVideoHorizontalResolution = (Value))
#define _PCD_SET_MODE_32_S_PcdVideoHorizontalResolution(Value)  ((_gPcd_BinaryPatch_PcdVideoHorizontalResolution = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdVideoVerticalResolution  70U
#define _PCD_PATCHABLE_VALUE_PcdVideoVerticalResolution  ((UINT32)0U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdVideoVerticalResolution;
#define _PCD_GET_MODE_32_PcdVideoVerticalResolution  _gPcd_BinaryPatch_PcdVideoVerticalResolution
#define _PCD_PATCHABLE_PcdVideoVerticalResolution_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdVideoVerticalResolution  _gPcd_BinaryPatch_Size_PcdVideoVerticalResolution 
extern UINTN _gPcd_BinaryPatch_Size_PcdVideoVerticalResolution; 
#define _PCD_SET_MODE_32_PcdVideoVerticalResolution(Value)  (_gPcd_BinaryPatch_PcdVideoVerticalResolution = (Value))
#define _PCD_SET_MODE_32_S_PcdVideoVerticalResolution(Value)  ((_gPcd_BinaryPatch_PcdVideoVerticalResolution = (Value)), RETURN_SUCCESS) 

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
BiosVideoEntryPoint (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
