/** @file
  Clean several important nvram variables to recover from issues.

Copyright (c) 2018, vit9696. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>

#include <Guid/GlobalVariable.h>
#include <Guid/OcVariables.h>

#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Protocol/OcFirmwareRuntime.h>
#include <AppleSupportPkgVersion.h>

STATIC
EFI_GUID
mOzmosisProprietary1Guid    = { 0x4D1FDA02, 0x38C7, 0x4A6A, { 0x9C, 0xC6, 0x4B, 0xCC, 0xA8, 0xB3, 0x01, 0x02 } };

STATIC
EFI_GUID
mOzmosisProprietary2Guid    = { 0x1F8E0C02, 0x58A9, 0x4E34, { 0xAE, 0x22, 0x2B, 0x63, 0x74, 0x5F, 0xA1, 0x01 } };

STATIC
EFI_GUID
mOzmosisProprietary3Guid    = { 0x9480E8A1, 0x1793, 0x46C9, { 0x91, 0xD8, 0x11, 0x08, 0xDB, 0xA4, 0x73, 0x1C } };

STATIC
BOOLEAN
IsDeletableVariable (
  IN CHAR16    *Name,
  IN EFI_GUID  *Guid
  )
{
  //
  // Apple GUIDs
  //
  if (CompareGuid (Guid, &gAppleVendorVariableGuid)
    || CompareGuid (Guid, &gAppleBootVariableGuid)
    || CompareGuid (Guid, &gAppleCoreStorageVariableGuid)
    || CompareGuid (Guid, &gAppleTamperResistantBootVariableGuid)
    || CompareGuid (Guid, &gAppleWirelessNetworkVariableGuid)
    || CompareGuid (Guid, &gApplePersonalizationVariableGuid)
    || CompareGuid (Guid, &gAppleNetbootVariableGuid)
    || CompareGuid (Guid, &gAppleSecureBootVariableGuid)
    || CompareGuid (Guid, &gAppleTamperResistantBootSecureVariableGuid)
    || CompareGuid (Guid, &gAppleTamperResistantBootEfiUserVariableGuid)) {
    return TRUE;
  //
  // Global variable boot options
  //
  } else if (CompareGuid (Guid, &gEfiGlobalVariableGuid)) {
    //
    // Only erase boot and driver entries for BDS
    // I.e. BootOrder, Boot####, DriverOrder, Driver####
    //
    if (StrnCmp (Name, L"Boot", StrLen(L"Boot")) == 0
      || StrnCmp (Name, L"Driver", StrLen(L"Driver")) == 0) {
      return TRUE;
    }
  //
  // Lilu & OpenCore extensions if present
  //
  } else if (CompareGuid (Guid, &gOcVendorVariableGuid)) {
    //
    // Do not remove OpenCore critical variables.
    //
    if (StrCmp (Name, OC_BOOT_REDIRECT_VARIABLE_NAME) != 0
      && StrCmp (Name, OC_LOAD_POLICY_VARIABLE_NAME) != 0
      && StrCmp (Name, OC_SCAN_POLICY_VARIABLE_NAME) != 0) {
      return TRUE;
    }
  } else if (CompareGuid (Guid, &gOcReadOnlyVariableGuid)
    || CompareGuid (Guid, &gOcWriteOnlyVariableGuid)) {
    return TRUE;
  //
  // Ozmozis extensions if present
  //
  } else if (CompareGuid (Guid, &mOzmosisProprietary1Guid)
    || CompareGuid (Guid, &mOzmosisProprietary2Guid)
    || CompareGuid (Guid, &mOzmosisProprietary3Guid)) {
    return TRUE;
  }

  return FALSE;
}

STATIC
VOID
DeleteVariables (
  VOID
  )
{
  EFI_GUID     CurrentGuid;
  EFI_STATUS   Status;
  CHAR16       *Buffer;
  CHAR16       *TmpBuffer;
  UINTN        BufferSize;
  UINTN        RequestedSize;
  BOOLEAN      Restart;
  BOOLEAN      CriticalFailure;

  //
  // Request 1024 byte buffer.
  //
  Buffer = NULL;
  BufferSize = 0;
  RequestedSize = 1024;

  //
  // Force starting from 0th GUID.
  //
  Restart = TRUE;

  //
  // Assume we have not failed yet.
  //
  CriticalFailure = FALSE;

  do {
    //
    // Allocate new buffer if needed.
    //
    if (RequestedSize > BufferSize) {
      TmpBuffer = AllocateZeroPool (RequestedSize);
      if (TmpBuffer != NULL) {
        if (Buffer != NULL) {
          CopyMem (TmpBuffer, Buffer, BufferSize);
          FreePool (Buffer);
        }
        Buffer = TmpBuffer;
        BufferSize = RequestedSize;
      } else {
        Print (L"Failed to allocate variable name buffer of %u bytes\n", (UINT32)RequestedSize);
        break;
      }
    }

    //
    // To start the search variable name should be L"".
    //
    if (Restart) {
      ZeroMem (&CurrentGuid, sizeof (CurrentGuid));
      ZeroMem (Buffer, BufferSize);
      Restart = FALSE;
    }

    //
    // Always pass maximum variable name size to reduce reallocations.
    //
    RequestedSize = BufferSize;
    Status = gRT->GetNextVariableName (&RequestedSize, Buffer, &CurrentGuid);

    if (!EFI_ERROR (Status)) {
      if (IsDeletableVariable (Buffer, &CurrentGuid)) {
        Print (L"Deleting %g:%s... ", &CurrentGuid, Buffer);
        Status = gRT->SetVariable (Buffer, &CurrentGuid, 0, 0, NULL);
        if (!EFI_ERROR (Status)) {
          Print (L"OK\n");
          //
          // Calls to SetVariable() between calls to GetNextVariableName()
          // may produce unpredictable results, so we restart.
          //
          Restart = TRUE;
        } else if (Status == EFI_NOT_FOUND) {
          Print (L"SKIP (%r)\n", Status);
        } else {
          Print (L"FAIL (%r)\n", Status);
          break;
        }
      } else {
        // Print (L"Skipping %g:%s\n", &CurrentGuid, Buffer);
      }
    } else if (Status != EFI_BUFFER_TOO_SMALL && Status != EFI_NOT_FOUND) {
      if (!CriticalFailure) {
        Print (L"Unexpected error (%r), trying to rescan\n", Status);
        CriticalFailure = TRUE;
      } else {
        Print (L"Unexpected error (%r), aborting\n", Status);
        break;
      }
    }
  } while (Status != EFI_NOT_FOUND);

  if (Buffer != NULL) {
    FreePool (Buffer);
  }
}

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                   Status;
  OC_FIRMWARE_RUNTIME_PROTOCOL *FwRuntime;
  OC_FWRT_CONFIG               Config;

  Print (L"NVRAM cleanup %s\n", APPLE_SUPPORT_VERSION);

  Status = gBS->LocateProtocol (
    &gOcFirmwareRuntimeProtocolGuid,
    NULL,
    (VOID **) &FwRuntime
    );

  if (!EFI_ERROR (Status) && FwRuntime->Revision >= OC_FIRMWARE_RUNTIME_REVISION) {
    ZeroMem (&Config, sizeof (Config));
    FwRuntime->SetOverride (&Config);
    Print (L"Found AMF NVRAM, full access %d\n", Config.BootVariableRedirect);
  } else {
    FwRuntime = NULL;
    Print (L"Missing AMF NVRAM\n");
  }

  DeleteVariables ();

  if (FwRuntime != NULL) {
    Print (L"Restoring AMF NVRAM...\n");
    FwRuntime->SetOverride (NULL);
  }

  Print (L"NVRAM cleanup completed, please reboot!\n");

  return EFI_SUCCESS;
}
