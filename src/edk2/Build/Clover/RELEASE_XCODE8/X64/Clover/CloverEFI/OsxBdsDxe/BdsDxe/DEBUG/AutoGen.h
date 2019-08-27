/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_FC5C7020_1A48_4198_9BE2_EAD5ABC8CF2F
#define _AUTOGENH_FC5C7020_1A48_4198_9BE2_EAD5ABC8CF2F

#ifdef __cplusplus
extern "C" {
#endif

#include <PiDxe.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0xFC5C7020, 0x1A48, 0x4198, {0x9B, 0xE2, 0xEA, 0xD5, 0xAB, 0xC8, 0xCF, 0x2F}}

// Guids
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiFileSystemVolumeLabelInfoIdGuid;
extern EFI_GUID gEfiFileInfoGuid;
extern EFI_GUID gEfiFileSystemInfoGuid;
extern EFI_GUID gEfiHiiPlatformSetupFormsetGuid;
extern EFI_GUID gEfiIfrTianoGuid;
extern EFI_GUID gEfiHiiDriverHealthFormsetGuid;
extern EFI_GUID gEfiLegacyDevOrderVariableGuid;
extern EFI_GUID gFrontPageFormSetGuid;
extern EFI_GUID gBootMaintFormSetGuid;
extern EFI_GUID gFileExploreFormSetGuid;
extern EFI_GUID gBootManagerFormSetGuid;
extern EFI_GUID gDeviceManagerFormSetGuid;
extern EFI_GUID gDriverHealthFormSetGuid;
extern EFI_GUID gConnectConInEventGuid;
extern EFI_GUID gEfiFmpCapsuleGuid;
extern EFI_GUID gEdkiiStatusCodeDataTypeVariableGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiIntelFrameworkModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiMdeModulePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiVirtualDiskGuid;
extern EFI_GUID gEfiVirtualCdGuid;
extern EFI_GUID gEfiPersistentVirtualDiskGuid;
extern EFI_GUID gEfiPersistentVirtualCdGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAcpi10TableGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiAcpiDescriptionGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEdkiiIfrBitVarstoreGuid;
extern EFI_GUID gEfiMemoryTypeInformationGuid;
extern EFI_GUID gPerformanceProtocolGuid;
extern EFI_GUID gLastEnumLangGuid;
extern EFI_GUID gHdBootDevicePathVariablGuid;
extern EFI_GUID gBdsLibStringPackageGuid;
extern EFI_GUID gEfiPciExpressBaseAddressGuid;
extern EFI_GUID gEfiMpsTableGuid;
extern EFI_GUID gEfiSmbiosTableGuid;
extern EFI_GUID gEfiSmbios3TableGuid;
extern EFI_GUID gEfiAcpiTableGuid;
extern EFI_GUID gLdrMemoryDescriptorGuid;

// Protocols
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiBdsArchProtocolGuid;
extern EFI_GUID gEfiSmbiosProtocolGuid;
extern EFI_GUID gEfiGenericMemTestProtocolGuid;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiBlockIo2ProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiSimpleTextInputExProtocolGuid;
extern EFI_GUID gEfiHiiConfigAccessProtocolGuid;
extern EFI_GUID gEfiFormBrowser2ProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDriverHealthProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiBootLogoProtocolGuid;
extern EFI_GUID gEfiLegacy8259ProtocolGuid;
extern EFI_GUID gEfiCpuArchProtocolGuid;
extern EFI_GUID gEdkiiVariableLockProtocolGuid;
extern EFI_GUID gPcdProtocolGuid;
extern EFI_GUID gEfiPcdProtocolGuid;
extern EFI_GUID gGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiGetPcdInfoProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiHiiStringProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiConfigRoutingProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiLoadFile2ProtocolGuid;
extern EFI_GUID gEfiSimpleNetworkProtocolGuid;
extern EFI_GUID gEfiSimpleTextInProtocolGuid;
extern EFI_GUID gEfiAcpiS3SaveProtocolGuid;
extern EFI_GUID gEfiOEMBadgingProtocolGuid;
extern EFI_GUID gEfiUserManagerProtocolGuid;
extern EFI_GUID gEfiUsbIoProtocolGuid;
extern EFI_GUID gEfiAcpiTableProtocolGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdUefiVariableDefaultLangDeprecate  25U
#define _PCD_SIZE_PcdUefiVariableDefaultLangDeprecate 1
#define _PCD_GET_MODE_SIZE_PcdUefiVariableDefaultLangDeprecate  _PCD_SIZE_PcdUefiVariableDefaultLangDeprecate 
#define _PCD_VALUE_PcdUefiVariableDefaultLangDeprecate  ((BOOLEAN)0U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLangDeprecate;
#define _PCD_GET_MODE_BOOL_PcdUefiVariableDefaultLangDeprecate  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLangDeprecate
//#define _PCD_SET_MODE_BOOL_PcdUefiVariableDefaultLangDeprecate  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUgaConsumeSupport  20U
#define _PCD_SIZE_PcdUgaConsumeSupport 1
#define _PCD_GET_MODE_SIZE_PcdUgaConsumeSupport  _PCD_SIZE_PcdUgaConsumeSupport 
#define _PCD_VALUE_PcdUgaConsumeSupport  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUgaConsumeSupport;
#define _PCD_GET_MODE_BOOL_PcdUgaConsumeSupport  _gPcd_FixedAtBuild_PcdUgaConsumeSupport
//#define _PCD_SET_MODE_BOOL_PcdUgaConsumeSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdBootlogoOnlyEnable  76U
#define _PCD_SIZE_PcdBootlogoOnlyEnable 1
#define _PCD_GET_MODE_SIZE_PcdBootlogoOnlyEnable  _PCD_SIZE_PcdBootlogoOnlyEnable 
#define _PCD_VALUE_PcdBootlogoOnlyEnable  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdBootlogoOnlyEnable;
#define _PCD_GET_MODE_BOOL_PcdBootlogoOnlyEnable  _gPcd_FixedAtBuild_PcdBootlogoOnlyEnable
//#define _PCD_SET_MODE_BOOL_PcdBootlogoOnlyEnable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUefiVariableDefaultLangCodes  77U
#define _PCD_VALUE_PcdUefiVariableDefaultLangCodes  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLangCodes
extern const UINT8 _gPcd_FixedAtBuild_PcdUefiVariableDefaultLangCodes[13];
#define _PCD_GET_MODE_PTR_PcdUefiVariableDefaultLangCodes  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLangCodes
#define _PCD_SIZE_PcdUefiVariableDefaultLangCodes 13
#define _PCD_GET_MODE_SIZE_PcdUefiVariableDefaultLangCodes  _PCD_SIZE_PcdUefiVariableDefaultLangCodes 
//#define _PCD_SET_MODE_PTR_PcdUefiVariableDefaultLangCodes  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUefiVariableDefaultLang  78U
#define _PCD_VALUE_PcdUefiVariableDefaultLang  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLang
extern const UINT8 _gPcd_FixedAtBuild_PcdUefiVariableDefaultLang[4];
#define _PCD_GET_MODE_PTR_PcdUefiVariableDefaultLang  _gPcd_FixedAtBuild_PcdUefiVariableDefaultLang
#define _PCD_SIZE_PcdUefiVariableDefaultLang 4
#define _PCD_GET_MODE_SIZE_PcdUefiVariableDefaultLang  _PCD_SIZE_PcdUefiVariableDefaultLang 
//#define _PCD_SET_MODE_PTR_PcdUefiVariableDefaultLang  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUefiVariableDefaultPlatformLangCodes  79U
#define _PCD_VALUE_PcdUefiVariableDefaultPlatformLangCodes  _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLangCodes
extern const UINT8 _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLangCodes[18];
#define _PCD_GET_MODE_PTR_PcdUefiVariableDefaultPlatformLangCodes  _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLangCodes
#define _PCD_SIZE_PcdUefiVariableDefaultPlatformLangCodes 18
#define _PCD_GET_MODE_SIZE_PcdUefiVariableDefaultPlatformLangCodes  _PCD_SIZE_PcdUefiVariableDefaultPlatformLangCodes 
//#define _PCD_SET_MODE_PTR_PcdUefiVariableDefaultPlatformLangCodes  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdUefiVariableDefaultPlatformLang  61U
#define _PCD_VALUE_PcdUefiVariableDefaultPlatformLang  _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLang
extern const UINT8 _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLang[6];
#define _PCD_GET_MODE_PTR_PcdUefiVariableDefaultPlatformLang  _gPcd_FixedAtBuild_PcdUefiVariableDefaultPlatformLang
#define _PCD_SIZE_PcdUefiVariableDefaultPlatformLang 6
#define _PCD_GET_MODE_SIZE_PcdUefiVariableDefaultPlatformLang  _PCD_SIZE_PcdUefiVariableDefaultPlatformLang 
//#define _PCD_SET_MODE_PTR_PcdUefiVariableDefaultPlatformLang  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdConOutRow  56U
#define _PCD_PATCHABLE_VALUE_PcdConOutRow  ((UINT32)0U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdConOutRow;
#define _PCD_GET_MODE_32_PcdConOutRow  _gPcd_BinaryPatch_PcdConOutRow
#define _PCD_PATCHABLE_PcdConOutRow_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdConOutRow  _gPcd_BinaryPatch_Size_PcdConOutRow 
extern UINTN _gPcd_BinaryPatch_Size_PcdConOutRow; 
#define _PCD_SET_MODE_32_PcdConOutRow(Value)  (_gPcd_BinaryPatch_PcdConOutRow = (Value))
#define _PCD_SET_MODE_32_S_PcdConOutRow(Value)  ((_gPcd_BinaryPatch_PcdConOutRow = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdConOutColumn  57U
#define _PCD_PATCHABLE_VALUE_PcdConOutColumn  ((UINT32)0U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdConOutColumn;
#define _PCD_GET_MODE_32_PcdConOutColumn  _gPcd_BinaryPatch_PcdConOutColumn
#define _PCD_PATCHABLE_PcdConOutColumn_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdConOutColumn  _gPcd_BinaryPatch_Size_PcdConOutColumn 
extern UINTN _gPcd_BinaryPatch_Size_PcdConOutColumn; 
#define _PCD_SET_MODE_32_PcdConOutColumn(Value)  (_gPcd_BinaryPatch_PcdConOutColumn = (Value))
#define _PCD_SET_MODE_32_S_PcdConOutColumn(Value)  ((_gPcd_BinaryPatch_PcdConOutColumn = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdHardwareErrorRecordLevel  80U
#define _PCD_SIZE_PcdHardwareErrorRecordLevel 2
#define _PCD_GET_MODE_SIZE_PcdHardwareErrorRecordLevel  _PCD_SIZE_PcdHardwareErrorRecordLevel 
#define _PCD_VALUE_PcdHardwareErrorRecordLevel  0U
extern const  UINT16  _gPcd_FixedAtBuild_PcdHardwareErrorRecordLevel;
#define _PCD_GET_MODE_16_PcdHardwareErrorRecordLevel  _gPcd_FixedAtBuild_PcdHardwareErrorRecordLevel
//#define _PCD_SET_MODE_16_PcdHardwareErrorRecordLevel  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdPlatformBootTimeOut  81U
#define _PCD_SIZE_PcdPlatformBootTimeOut 2
#define _PCD_GET_MODE_SIZE_PcdPlatformBootTimeOut  _PCD_SIZE_PcdPlatformBootTimeOut 
#define _PCD_VALUE_PcdPlatformBootTimeOut  0xffffU
extern const  UINT16  _gPcd_FixedAtBuild_PcdPlatformBootTimeOut;
#define _PCD_GET_MODE_16_PcdPlatformBootTimeOut  _gPcd_FixedAtBuild_PcdPlatformBootTimeOut
//#define _PCD_SET_MODE_16_PcdPlatformBootTimeOut  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdBootState  1U
#define _PCD_GET_MODE_BOOL_PcdBootState  LibPcdGetBool(_PCD_TOKEN_PcdBootState)
#define _PCD_GET_MODE_SIZE_PcdBootState  LibPcdGetSize(_PCD_TOKEN_PcdBootState)
#define _PCD_SET_MODE_BOOL_PcdBootState(Value)  LibPcdSetBool(_PCD_TOKEN_PcdBootState, (Value))
#define _PCD_SET_MODE_BOOL_S_PcdBootState(Value)  LibPcdSetBoolS(_PCD_TOKEN_PcdBootState, (Value))

#define _PCD_TOKEN_PcdFirmwareVendor  82U
#define _PCD_VALUE_PcdFirmwareVendor  _gPcd_FixedAtBuild_PcdFirmwareVendor
extern const UINT16 _gPcd_FixedAtBuild_PcdFirmwareVendor[7];
#define _PCD_GET_MODE_PTR_PcdFirmwareVendor  _gPcd_FixedAtBuild_PcdFirmwareVendor
#define _PCD_SIZE_PcdFirmwareVendor 14
#define _PCD_GET_MODE_SIZE_PcdFirmwareVendor  _PCD_SIZE_PcdFirmwareVendor 
//#define _PCD_SET_MODE_PTR_PcdFirmwareVendor  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdFirmwareRevision  83U
#define _PCD_SIZE_PcdFirmwareRevision 4
#define _PCD_GET_MODE_SIZE_PcdFirmwareRevision  _PCD_SIZE_PcdFirmwareRevision 
#define _PCD_VALUE_PcdFirmwareRevision  0x00010010U
extern const  UINT32  _gPcd_FixedAtBuild_PcdFirmwareRevision;
#define _PCD_GET_MODE_32_PcdFirmwareRevision  _gPcd_FixedAtBuild_PcdFirmwareRevision
//#define _PCD_SET_MODE_32_PcdFirmwareRevision  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

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

#define _PCD_TOKEN_PcdConInConnectOnDemand  58U
#define _PCD_SIZE_PcdConInConnectOnDemand 1
#define _PCD_GET_MODE_SIZE_PcdConInConnectOnDemand  _PCD_SIZE_PcdConInConnectOnDemand 
#define _PCD_VALUE_PcdConInConnectOnDemand  0U
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdConInConnectOnDemand;
#define _PCD_GET_MODE_BOOL_PcdConInConnectOnDemand  _gPcd_FixedAtBuild_PcdConInConnectOnDemand
//#define _PCD_SET_MODE_BOOL_PcdConInConnectOnDemand  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdSetupConOutColumn  84U
#define _PCD_PATCHABLE_VALUE_PcdSetupConOutColumn  ((UINT32)80U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdSetupConOutColumn;
#define _PCD_GET_MODE_32_PcdSetupConOutColumn  _gPcd_BinaryPatch_PcdSetupConOutColumn
#define _PCD_PATCHABLE_PcdSetupConOutColumn_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdSetupConOutColumn  _gPcd_BinaryPatch_Size_PcdSetupConOutColumn 
extern UINTN _gPcd_BinaryPatch_Size_PcdSetupConOutColumn; 
#define _PCD_SET_MODE_32_PcdSetupConOutColumn(Value)  (_gPcd_BinaryPatch_PcdSetupConOutColumn = (Value))
#define _PCD_SET_MODE_32_S_PcdSetupConOutColumn(Value)  ((_gPcd_BinaryPatch_PcdSetupConOutColumn = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdSetupConOutRow  85U
#define _PCD_PATCHABLE_VALUE_PcdSetupConOutRow  ((UINT32)25U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdSetupConOutRow;
#define _PCD_GET_MODE_32_PcdSetupConOutRow  _gPcd_BinaryPatch_PcdSetupConOutRow
#define _PCD_PATCHABLE_PcdSetupConOutRow_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdSetupConOutRow  _gPcd_BinaryPatch_Size_PcdSetupConOutRow 
extern UINTN _gPcd_BinaryPatch_Size_PcdSetupConOutRow; 
#define _PCD_SET_MODE_32_PcdSetupConOutRow(Value)  (_gPcd_BinaryPatch_PcdSetupConOutRow = (Value))
#define _PCD_SET_MODE_32_S_PcdSetupConOutRow(Value)  ((_gPcd_BinaryPatch_PcdSetupConOutRow = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdSetupVideoHorizontalResolution  86U
#define _PCD_PATCHABLE_VALUE_PcdSetupVideoHorizontalResolution  ((UINT32)800U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdSetupVideoHorizontalResolution;
#define _PCD_GET_MODE_32_PcdSetupVideoHorizontalResolution  _gPcd_BinaryPatch_PcdSetupVideoHorizontalResolution
#define _PCD_PATCHABLE_PcdSetupVideoHorizontalResolution_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdSetupVideoHorizontalResolution  _gPcd_BinaryPatch_Size_PcdSetupVideoHorizontalResolution 
extern UINTN _gPcd_BinaryPatch_Size_PcdSetupVideoHorizontalResolution; 
#define _PCD_SET_MODE_32_PcdSetupVideoHorizontalResolution(Value)  (_gPcd_BinaryPatch_PcdSetupVideoHorizontalResolution = (Value))
#define _PCD_SET_MODE_32_S_PcdSetupVideoHorizontalResolution(Value)  ((_gPcd_BinaryPatch_PcdSetupVideoHorizontalResolution = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdSetupVideoVerticalResolution  87U
#define _PCD_PATCHABLE_VALUE_PcdSetupVideoVerticalResolution  ((UINT32)600U)
extern volatile   UINT32  _gPcd_BinaryPatch_PcdSetupVideoVerticalResolution;
#define _PCD_GET_MODE_32_PcdSetupVideoVerticalResolution  _gPcd_BinaryPatch_PcdSetupVideoVerticalResolution
#define _PCD_PATCHABLE_PcdSetupVideoVerticalResolution_SIZE 4
#define _PCD_GET_MODE_SIZE_PcdSetupVideoVerticalResolution  _gPcd_BinaryPatch_Size_PcdSetupVideoVerticalResolution 
extern UINTN _gPcd_BinaryPatch_Size_PcdSetupVideoVerticalResolution; 
#define _PCD_SET_MODE_32_PcdSetupVideoVerticalResolution(Value)  (_gPcd_BinaryPatch_PcdSetupVideoVerticalResolution = (Value))
#define _PCD_SET_MODE_32_S_PcdSetupVideoVerticalResolution(Value)  ((_gPcd_BinaryPatch_PcdSetupVideoVerticalResolution = (Value)), RETURN_SUCCESS) 

#define _PCD_TOKEN_PcdErrorCodeSetVariable  50U
#define _PCD_SIZE_PcdErrorCodeSetVariable 4
#define _PCD_GET_MODE_SIZE_PcdErrorCodeSetVariable  _PCD_SIZE_PcdErrorCodeSetVariable 
#define _PCD_VALUE_PcdErrorCodeSetVariable  0x03058002U
extern const  UINT32  _gPcd_FixedAtBuild_PcdErrorCodeSetVariable;
#define _PCD_GET_MODE_32_PcdErrorCodeSetVariable  _gPcd_FixedAtBuild_PcdErrorCodeSetVariable
//#define _PCD_SET_MODE_32_PcdErrorCodeSetVariable  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

#define _PCD_TOKEN_PcdShellFile  88U
#define _PCD_VALUE_PcdShellFile  (VOID *)_gPcd_FixedAtBuild_PcdShellFile
extern const UINT8 _gPcd_FixedAtBuild_PcdShellFile[16];
#define _PCD_GET_MODE_PTR_PcdShellFile  (VOID *)_gPcd_FixedAtBuild_PcdShellFile
#define _PCD_SIZE_PcdShellFile 16
#define _PCD_GET_MODE_SIZE_PcdShellFile  _PCD_SIZE_PcdShellFile 
//#define _PCD_SET_MODE_PTR_PcdShellFile  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
BdsInitialize (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );



#include "BdsDxeStrDefs.h"


#ifdef __cplusplus
}
#endif

#endif
