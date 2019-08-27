/**
  DO NOT EDIT
  FILE auto-generated
  Module name:
    AutoGen.h
  Abstract:       Auto-generated AutoGen.h for building module or library.
**/

#ifndef _AUTOGENH_8F7D7B1E_0E1C_4C98_B12E_4EC99C4081AC
#define _AUTOGENH_8F7D7B1E_0E1C_4C98_B12E_4EC99C4081AC

#ifdef __cplusplus
extern "C" {
#endif

#include <Uefi.h>
#include <Library/PcdLib.h>

extern GUID  gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;

#define EFI_CALLER_ID_GUID \
  {0x8F7D7B1E, 0x0E1C, 0x4C98, {0xB1, 0x2E, 0x4E, 0xC9, 0x9C, 0x40, 0x81, 0xAC}}

// Guids
extern EFI_GUID gEfiAcpiTableGuid;
extern EFI_GUID gEfiAcpi10TableGuid;
extern EFI_GUID gEfiAcpi20TableGuid;
extern EFI_GUID gEfiAppleBootGuid;
extern EFI_GUID gEfiAppleNvramGuid;
extern EFI_GUID gEfiAppleVendorGuid;
extern EFI_GUID gEfiDxeServicesTableGuid;
extern EFI_GUID gEfiEventReadyToBootGuid;
extern EFI_GUID gEfiEventVirtualAddressChangeGuid;
extern EFI_GUID gEfiEventExitBootServicesGuid;
extern EFI_GUID gEfiFileInfoGuid;
extern EFI_GUID gEfiFileSystemInfoGuid;
extern EFI_GUID gEfiFileSystemVolumeLabelInfoIdGuid;
extern EFI_GUID gEfiGlobalVariableGuid;
extern EFI_GUID gEfiPartTypeLegacyMbrGuid;
extern EFI_GUID gEfiPartTypeSystemPartGuid;
extern EFI_GUID gEfiSmbiosTableGuid;
extern EFI_GUID gEfiSmbios3TableGuid;
extern EFI_GUID gEfiSasDevicePathGuid;
extern EFI_GUID gEfiImageSecurityDatabaseGuid;
extern EFI_GUID gEfiCertX509Guid;
extern EFI_GUID gEfiCertSha1Guid;
extern EFI_GUID gEfiCertSha256Guid;
extern EFI_GUID gEfiCertPkcs7Guid;
extern EFI_GUID gEfiCertRsa2048Guid;
extern EFI_GUID gEfiCertRsa2048Sha256Guid;
extern EFI_GUID gEfiCertTypeRsa2048Sha256Guid;
extern EFI_GUID gAppleOsLoadedNamedEventGuid;
extern EFI_GUID gBootChimeVendorVariableGuid;
extern EFI_GUID gEfiMdePkgTokenSpaceGuid;
extern EFI_GUID gEfiVTUTF8Guid;
extern EFI_GUID gEfiVT100Guid;
extern EFI_GUID gEfiVT100PlusGuid;
extern EFI_GUID gEfiPcAnsiGuid;
extern EFI_GUID gEfiUartDevicePathGuid;
extern EFI_GUID gEfiVirtualDiskGuid;
extern EFI_GUID gEfiVirtualCdGuid;
extern EFI_GUID gEfiPersistentVirtualDiskGuid;
extern EFI_GUID gEfiPersistentVirtualCdGuid;
extern EFI_GUID gEfiEventLegacyBootGuid;
extern EFI_GUID gEfiHobListGuid;
extern EFI_GUID gEfiAdapterInfoMediaStateGuid;

// Protocols
extern EFI_GUID gEfiComponentName2ProtocolGuid;
extern EFI_GUID gEfiDevicePathToTextProtocolGuid;
extern EFI_GUID gEfiSimpleFileSystemProtocolGuid;
extern EFI_GUID gEfiSimpleTextInProtocolGuid;
extern EFI_GUID gEfiSimpleTextInputExProtocolGuid;
extern EFI_GUID gEfiSimpleTextOutProtocolGuid;
extern EFI_GUID gEfiUnicodeCollationProtocolGuid;
extern EFI_GUID gEfiUnicodeCollation2ProtocolGuid;
extern EFI_GUID gEfiAcpiS3SaveProtocolGuid;
extern EFI_GUID gEfiBlockIoProtocolGuid;
extern EFI_GUID gEfiCpuArchProtocolGuid;
extern EFI_GUID gEfiDebugPortProtocolGuid;
extern EFI_GUID gEfiDevicePathProtocolGuid;
extern EFI_GUID gEfiDiskIoProtocolGuid;
extern EFI_GUID gEfiExtScsiPassThruProtocolGuid;
extern EFI_GUID gEfiFirmwareVolume2ProtocolGuid;
extern EFI_GUID gEfiGraphicsOutputProtocolGuid;
extern EFI_GUID gEfiHiiFontProtocolGuid;
extern EFI_GUID gEfiLegacy8259ProtocolGuid;
extern EFI_GUID gEfiLoadedImageProtocolGuid;
extern EFI_GUID gEfiOEMBadgingProtocolGuid;
extern EFI_GUID gEfiPciIoProtocolGuid;
extern EFI_GUID gEfiScsiIoProtocolGuid;
extern EFI_GUID gEfiScsiPassThruProtocolGuid;
extern EFI_GUID gEfiSimpleNetworkProtocolGuid;
extern EFI_GUID gEfiStatusCodeRuntimeProtocolGuid;
extern EFI_GUID gEfiUgaDrawProtocolGuid;
extern EFI_GUID gEfiManagedNetworkServiceBindingProtocolGuid;
extern EFI_GUID gEfiAbsolutePointerProtocolGuid;
extern EFI_GUID gEfiAcpiTableProtocolGuid;
extern EFI_GUID gEfiEdidActiveProtocolGuid;
extern EFI_GUID gEfiEdidDiscoveredProtocolGuid;
extern EFI_GUID gEfiEdidOverrideProtocolGuid;
extern EFI_GUID gEfiHiiDatabaseProtocolGuid;
extern EFI_GUID gEfiHiiImageProtocolGuid;
extern EFI_GUID gEfiHiiProtocolGuid;
extern EFI_GUID gEfiSimplePointerProtocolGuid;
extern EFI_GUID gEfiSmbiosProtocolGuid;
extern EFI_GUID gEfiSecurityArchProtocolGuid;
extern EFI_GUID gEfiSecurity2ArchProtocolGuid;
extern EFI_GUID AppleDevicePropertyProtocolGuid;
extern EFI_GUID gAppleScreenInfoProtocolGuid;
extern EFI_GUID gEfiConsoleControlProtocolGuid;
extern EFI_GUID gAppleGraphConfigProtocolGuid;
extern EFI_GUID gEfiLegacyBiosProtocolGuid;
extern EFI_GUID gEfiTimerArchProtocolGuid;
extern EFI_GUID gAppleImageCodecProtocolGuid;
extern EFI_GUID gAppleEventProtocolGuid;
extern EFI_GUID gEfiOSInfoProtocolGuid;
extern EFI_GUID gEfiKeyboardInfoProtocolGuid;
extern EFI_GUID gFSInjectProtocolGuid;
extern EFI_GUID gMsgLogProtocolGuid;
extern EFI_GUID gEfiPlatformDriverOverrideProtocolGuid;
extern EFI_GUID gEmuVariableControlProtocolGuid;
extern EFI_GUID gEfiAudioIoProtocolGuid;
extern EFI_GUID gEfiDriverBindingProtocolGuid;
extern EFI_GUID gEfiComponentNameProtocolGuid;
extern EFI_GUID gEfiDriverConfigurationProtocolGuid;
extern EFI_GUID gEfiDriverConfiguration2ProtocolGuid;
extern EFI_GUID gEfiDriverDiagnosticsProtocolGuid;
extern EFI_GUID gEfiDriverDiagnostics2ProtocolGuid;
extern EFI_GUID gEfiLoadFileProtocolGuid;
extern EFI_GUID gEfiLoadFile2ProtocolGuid;
extern EFI_GUID gEfiLegacyRegionProtocolGuid;
extern EFI_GUID gEfiLegacyRegion2ProtocolGuid;
extern EFI_GUID gEfiManagedNetworkProtocolGuid;
extern EFI_GUID gEfiIp4Config2ProtocolGuid;
extern EFI_GUID gEfiAdapterInformationProtocolGuid;

// Definition of SkuId Array
extern UINT64 _gPcd_SkuId_Array[];

// Definition of PCDs used in this module

#define _PCD_TOKEN_PcdUgaConsumeSupport  20U
#define _PCD_SIZE_PcdUgaConsumeSupport 1
#define _PCD_GET_MODE_SIZE_PcdUgaConsumeSupport  _PCD_SIZE_PcdUgaConsumeSupport 
#define _PCD_VALUE_PcdUgaConsumeSupport  ((BOOLEAN)1U)
extern const  BOOLEAN  _gPcd_FixedAtBuild_PcdUgaConsumeSupport;
#define _PCD_GET_MODE_BOOL_PcdUgaConsumeSupport  _gPcd_FixedAtBuild_PcdUgaConsumeSupport
//#define _PCD_SET_MODE_BOOL_PcdUgaConsumeSupport  ASSERT(FALSE)  // It is not allowed to set value for a FIXED_AT_BUILD PCD

// Definition of PCDs used in libraries is in AutoGen.c


EFI_STATUS
EFIAPI
RefitMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  );





#ifdef __cplusplus
}
#endif

#endif
