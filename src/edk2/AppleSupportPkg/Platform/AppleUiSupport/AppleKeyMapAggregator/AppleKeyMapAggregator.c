/** @file

AppleKeyMapAggregator

Copyright (c) 2018, vit9696

All rights reserved.

This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/
#include <AppleMacEfi.h>
#include <IndustryStandard/AppleHid.h>
#include <Protocol/AppleKeyMapAggregator.h>
#include <Protocol/AppleKeyMapDatabase.h>
#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/DebugLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>


// KEY_MAP_AGGREGATOR_DATA_SIGNATURE
#define KEY_MAP_AGGREGATOR_DATA_SIGNATURE  \
  SIGNATURE_32 ('K', 'e', 'y', 'A')

// KEY_MAP_AGGREGATOR_DATA_FROM_AGGREGATOR_THIS
#define KEY_MAP_AGGREGATOR_DATA_FROM_AGGREGATOR_THIS(This)  \
  CR (                                                      \
    (This),                                                 \
    KEY_MAP_AGGREGATOR_DATA,                                \
    Aggregator,                                             \
    KEY_MAP_AGGREGATOR_DATA_SIGNATURE                       \
    )

// KEY_MAP_AGGREGATOR_DATA_FROM_DATABASE_THIS
#define KEY_MAP_AGGREGATOR_DATA_FROM_DATABASE_THIS(This)  \
  CR (                                                    \
    (This),                                               \
    KEY_MAP_AGGREGATOR_DATA,                              \
    Database,                                             \
    KEY_MAP_AGGREGATOR_DATA_SIGNATURE                     \
    )

// KEY_MAP_AGGREGATOR_DATA
typedef struct {
  UINTN                             Signature;
  UINTN                             NextKeyStrokeIndex;
  APPLE_KEY_CODE                    *KeyCodeBuffer;
  UINTN                             KeyCodeBufferLength;
  LIST_ENTRY                        KeyStrokesInfoList;
  APPLE_KEY_MAP_DATABASE_PROTOCOL   Database;
  APPLE_KEY_MAP_AGGREGATOR_PROTOCOL Aggregator;
} KEY_MAP_AGGREGATOR_DATA;

// APPLE_KEY_STROKES_INFO_SIGNATURE
#define APPLE_KEY_STROKES_INFO_SIGNATURE  SIGNATURE_32 ('K', 'e', 'y', 'S')

// APPLE_KEY_STROKES_INFO_FROM_LIST_ENTRY
#define APPLE_KEY_STROKES_INFO_FROM_LIST_ENTRY(Entry)  \
  CR (                                                 \
    (Entry),                                           \
    APPLE_KEY_STROKES_INFO,                            \
    Link,                                              \
    APPLE_KEY_STROKES_INFO_SIGNATURE                   \
    )

#define SIZE_OF_APPLE_KEY_STROKES_INFO  \
  OFFSET_OF (APPLE_KEY_STROKES_INFO, KeyCodes)

// APPLE_KEY_STROKES_INFO
typedef struct {
  UINTN              Signature;
  LIST_ENTRY         Link;
  UINTN              Index;
  UINTN              KeyCodeBufferLength;
  UINTN              NumberOfKeyCodes;
  APPLE_MODIFIER_MAP Modifiers;
  APPLE_KEY_CODE     KeyCodes[];
} APPLE_KEY_STROKES_INFO;

// InternalGetKeyStrokesByIndex
STATIC
APPLE_KEY_STROKES_INFO *
InternalGetKeyStrokesByIndex (
  IN KEY_MAP_AGGREGATOR_DATA  *KeyMapAggregatorData,
  IN UINTN                    Index
  )
{
  APPLE_KEY_STROKES_INFO *KeyStrokesInfo;

  LIST_ENTRY             *Entry;
  APPLE_KEY_STROKES_INFO *KeyStrokesInfoWalker;

  KeyStrokesInfo = NULL;

  for (
    Entry = GetFirstNode (&KeyMapAggregatorData->KeyStrokesInfoList);
    !IsNull (&KeyMapAggregatorData->KeyStrokesInfoList, Entry);
    Entry = GetNextNode (&KeyMapAggregatorData->KeyStrokesInfoList, Entry)
    ) {
    KeyStrokesInfoWalker = APPLE_KEY_STROKES_INFO_FROM_LIST_ENTRY (Entry);

    if (KeyStrokesInfoWalker->Index == Index) {
      KeyStrokesInfo = KeyStrokesInfoWalker;

      break;
    }
  }

  return KeyStrokesInfo;
}

// InternalMinSort
STATIC
VOID
InternalMinSort (
  IN OUT UINT16  *Operand,
  IN     UINTN   NumberOfChilds
  )
{

  UINTN  Index;
  UINTN  Index2;
  UINT16 FirstChild;

  for (Index = 0; Index < NumberOfChilds; ++Index) {
    for (Index2 = (Index + 1); Index2 < NumberOfChilds; ++Index2) {
      FirstChild = Operand[Index];

      if (FirstChild > Operand[Index2]) {
        Operand[Index]  = Operand[Index2];
        Operand[Index2] = FirstChild;
      }
    }
  }
}

// InternalGetKeyStrokes
/** Returns all pressed keys and key modifiers into the appropiate buffers.

  @param[in]  This              A pointer to the protocol instance.
  @param[out] Modifiers         The modifiers manipulating the given keys.
  @param[out] NumberOfKeyCodes  On input the number of keys allocated.
                                On output the number of keys returned into
                                KeyCodes.
  @param[out] KeyCodes          A Pointer to a caller-allocated the pressed
                                keys get returned in.

  @retval EFI_SUCCESS           The pressed keys have been returned into
                                KeyCodes.
  @retval EFI_BUFFER_TOO_SMALL  The memory required to return the value exceeds
                                the size of the allocated Buffer.
                                The required number of keys to allocate to
                                complete the operation has been returned into
                                NumberOfKeyCodes.
  @retval other                 An error returned by a sub-operation.
**/
STATIC
EFI_STATUS
EFIAPI
InternalGetKeyStrokes (
  IN     APPLE_KEY_MAP_AGGREGATOR_PROTOCOL  *This,
  OUT    APPLE_MODIFIER_MAP                 *Modifiers,
  OUT    UINTN                              *NumberOfKeyCodes,
  IN OUT APPLE_KEY_CODE                     *KeyCodes OPTIONAL
  )
{
  EFI_STATUS              Status;

  KEY_MAP_AGGREGATOR_DATA *KeyMapAggregatorData;
  LIST_ENTRY              *Entry;
  APPLE_KEY_STROKES_INFO  *KeyStrokesInfo;
  BOOLEAN                 Result;
  APPLE_MODIFIER_MAP      DbModifiers;
  UINTN                   DbNumberOfKeyCodestrokes;
  UINTN                   Index;
  UINTN                   Index2;
  APPLE_KEY_CODE          Key;

  KeyMapAggregatorData = KEY_MAP_AGGREGATOR_DATA_FROM_AGGREGATOR_THIS (This);

  DbModifiers              = 0;
  DbNumberOfKeyCodestrokes = 0;

  for (
    Entry = GetFirstNode (&KeyMapAggregatorData->KeyStrokesInfoList);
    !IsNull (&KeyMapAggregatorData->KeyStrokesInfoList, Entry);
    Entry = GetNextNode (&KeyMapAggregatorData->KeyStrokesInfoList, Entry)
    ) {
    KeyStrokesInfo = APPLE_KEY_STROKES_INFO_FROM_LIST_ENTRY (Entry);

    DbModifiers |= KeyStrokesInfo->Modifiers;

    for (Index = 0; Index < KeyStrokesInfo->NumberOfKeyCodes; ++Index) {
      Key = KeyStrokesInfo->KeyCodes[Index];

      for (Index2 = 0; Index2 < DbNumberOfKeyCodestrokes; ++Index2) {
        if (KeyMapAggregatorData->KeyCodeBuffer[Index2] == Key) {
          break;
        }
      }

      if (Index2 == DbNumberOfKeyCodestrokes) {
        KeyMapAggregatorData->KeyCodeBuffer[DbNumberOfKeyCodestrokes] = Key;
        ++DbNumberOfKeyCodestrokes;
      }
    }
  }

  Result = (BOOLEAN)(DbNumberOfKeyCodestrokes > *NumberOfKeyCodes);

  *NumberOfKeyCodes = DbNumberOfKeyCodestrokes;

  Status = EFI_BUFFER_TOO_SMALL;

  if (!Result) {
    *Modifiers = DbModifiers;

    Status = EFI_SUCCESS;

    if (KeyCodes != NULL) {
      CopyMem (
        (VOID *)KeyCodes,
        (VOID *)KeyMapAggregatorData->KeyCodeBuffer,
        (DbNumberOfKeyCodestrokes * sizeof (*KeyCodes))
        );
    }
  }

  return Status;
}

// InternalContainsKeyStrokes
/** Returns whether or not a list of keys and their modifiers are part of the
    database of pressed keys.

  @param[in]      This          A pointer to the protocol instance.
  @param[in]      Modifiers     The modifiers manipulating the given keys.
  @param[in]      NumberOfKeyCodes  The number of keys present in KeyCodes.
  @param[in, out] KeyCodes          The list of keys to check for.  The children
                                may be sorted in the process.
  @param[in]      ExactMatch    Specifies whether Modifiers and KeyCodes should be
                                exact matches or just contained.

  @return                Returns whether or not a list of keys and their
                         modifiers are part of the database of pressed keys.
  @retval EFI_SUCCESS    The queried keys are part of the database.
  @retval EFI_NOT_FOUND  The queried keys could not be found.
**/
STATIC
EFI_STATUS
EFIAPI
InternalContainsKeyStrokes (
  IN     APPLE_KEY_MAP_AGGREGATOR_PROTOCOL  *This,
  IN     APPLE_MODIFIER_MAP                 Modifiers,
  IN     UINTN                              NumberOfKeyCodes,
  IN OUT APPLE_KEY_CODE                     *KeyCodes,
  IN     BOOLEAN                            ExactMatch
  )
{
  EFI_STATUS         Status;

  UINTN              DbNumberOfKeyCodes;
  APPLE_MODIFIER_MAP DbModifiers;
  APPLE_KEY_CODE     DbKeyCodes[8];
  INTN               Result;
  UINTN              Index;
  UINTN              DbIndex;

  DbNumberOfKeyCodes = ARRAY_SIZE (DbKeyCodes);
  Status             = This->GetKeyStrokes (
                               This,
                               &DbModifiers,
                               &DbNumberOfKeyCodes,
                               DbKeyCodes
                               );

  if (EFI_ERROR (Status)) {
    return Status;
  }

  if (ExactMatch) {
    if ((DbModifiers != Modifiers)
     || (DbNumberOfKeyCodes != NumberOfKeyCodes)) {
      return EFI_NOT_FOUND;
    }

    InternalMinSort ((UINT16 *)KeyCodes, NumberOfKeyCodes);
    InternalMinSort ((UINT16 *)DbKeyCodes, DbNumberOfKeyCodes);

    Result = CompareMem (
                (VOID *)KeyCodes,
                (VOID *)DbKeyCodes,
                (NumberOfKeyCodes * sizeof (*KeyCodes))
                );

    if (Result != 0) {
      return EFI_NOT_FOUND;
    }
  } else {
    if ((DbModifiers & Modifiers) == Modifiers) {
      return EFI_NOT_FOUND;
    }

    for (Index = 0; Index < NumberOfKeyCodes; ++Index) {
      for (DbIndex = 0; DbIndex < DbNumberOfKeyCodes; ++DbIndex) {
        if (KeyCodes[Index] == DbKeyCodes[DbIndex]) {
          break;
        }
      }

      if (DbNumberOfKeyCodes == DbIndex) {
        return EFI_NOT_FOUND;
      }
    }
  }

  return EFI_SUCCESS;
}

// KeyMapCreateKeyStrokesBuffer
/** Creates a new key set with a given number of keys allocated.  The index
    within the database is returned.

  @param[in]  This          A pointer to the protocol instance.
  @param[in]  BufferLength  The amount of keys to allocate for the key set.
  @param[out] Index         The assigned index of the created key set.

  @return                       Returned is the status of the operation.
  @retval EFI_SUCCESS           A key set with the given number of keys
                                allocated has been created.
  @retval EFI_OUT_OF_RESOURCES  The memory necessary to complete the operation
                                could not be allocated.
  @retval other                 An error returned by a sub-operation.
**/
STATIC
EFI_STATUS
EFIAPI
InternalCreateKeyStrokesBuffer (
  IN  APPLE_KEY_MAP_DATABASE_PROTOCOL  *This,
  IN  UINTN                            BufferLength,
  OUT UINTN                            *Index
  )
{
  EFI_STATUS              Status;

  KEY_MAP_AGGREGATOR_DATA *KeyMapAggregatorData;
  UINTN                   TotalBufferLength;
  APPLE_KEY_CODE          *Buffer;
  APPLE_KEY_STROKES_INFO  *KeyStrokesInfo;

  KeyMapAggregatorData = KEY_MAP_AGGREGATOR_DATA_FROM_DATABASE_THIS (This);

  if (KeyMapAggregatorData->KeyCodeBuffer != NULL) {
    gBS->FreePool ((VOID *)KeyMapAggregatorData->KeyCodeBuffer);
  }

  TotalBufferLength = (KeyMapAggregatorData->KeyCodeBufferLength + BufferLength);

  KeyMapAggregatorData->KeyCodeBufferLength = TotalBufferLength;

  Buffer = AllocateZeroPool (TotalBufferLength * sizeof (*Buffer));

  KeyMapAggregatorData->KeyCodeBuffer = Buffer;

  Status = EFI_OUT_OF_RESOURCES;

  if (Buffer != NULL) {
    KeyStrokesInfo = AllocateZeroPool (
                       SIZE_OF_APPLE_KEY_STROKES_INFO
                         + (BufferLength * sizeof (*Buffer))
                       );

    Status = EFI_OUT_OF_RESOURCES;

    if (KeyStrokesInfo != NULL) {
      KeyStrokesInfo->Signature           = APPLE_KEY_STROKES_INFO_SIGNATURE;
      KeyStrokesInfo->KeyCodeBufferLength = BufferLength;
      KeyStrokesInfo->Index               = KeyMapAggregatorData->NextKeyStrokeIndex++;

      InsertTailList (
        &KeyMapAggregatorData->KeyStrokesInfoList,
        &KeyStrokesInfo->Link
        );

      Status = EFI_SUCCESS;

      *Index = KeyStrokesInfo->Index;
    }
  }

  return Status;
}

// KeyMapRemoveKeyStrokesBuffer
/** Removes a key set specified by its index from the database.

  @param[in] This   A pointer to the protocol instance.
  @param[in] Index  The index of the key set to remove.

  @return                Returned is the status of the operation.
  @retval EFI_SUCCESS    The specified key set has been removed.
  @retval EFI_NOT_FOUND  No key set could be found for the given index.
  @retval other          An error returned by a sub-operation.
**/
STATIC
EFI_STATUS
EFIAPI
InternalRemoveKeyStrokesBuffer (
  IN APPLE_KEY_MAP_DATABASE_PROTOCOL  *This,
  IN UINTN                            Index
  )
{
  EFI_STATUS              Status;

  KEY_MAP_AGGREGATOR_DATA *KeyMapAggregatorData;
  APPLE_KEY_STROKES_INFO  *KeyStrokesInfo;

  KeyMapAggregatorData = KEY_MAP_AGGREGATOR_DATA_FROM_DATABASE_THIS (This);

  KeyStrokesInfo = InternalGetKeyStrokesByIndex (
                     KeyMapAggregatorData,
                     Index
                     );

  Status = EFI_NOT_FOUND;

  if (KeyStrokesInfo != NULL) {
    KeyMapAggregatorData->KeyCodeBufferLength -= KeyStrokesInfo->KeyCodeBufferLength;

    RemoveEntryList (&KeyStrokesInfo->Link);
    gBS->FreePool ((VOID *)KeyStrokesInfo);

    Status = EFI_SUCCESS;
  }

  return Status;
}

// KeyMapSetKeyStrokeBufferKeys
/** Sets the keys of a key set specified by its index to the given KeyCodes
    Buffer.

  @param[in] This              A pointer to the protocol instance.
  @param[in] Index             The index of the key set to edit.
  @param[in] Modifiers         The key modifiers manipulating the given keys.
  @param[in] NumberOfKeyCodes  The number of keys contained in KeyCodes.
  @param[in] KeyCodes          An array of keys to add to the specified key
                               set.

  @return                       Returned is the status of the operation.
  @retval EFI_SUCCESS           The given keys were set for the specified key
                                set.
  @retval EFI_OUT_OF_RESOURCES  The memory necessary to complete the operation
                                could not be allocated.
  @retval EFI_NOT_FOUND         No key set could be found for the given index.
  @retval other                 An error returned by a sub-operation.
**/
STATIC
EFI_STATUS
EFIAPI
InternalSetKeyStrokeBufferKeys (
  IN APPLE_KEY_MAP_DATABASE_PROTOCOL  *This,
  IN UINTN                            Index,
  IN APPLE_MODIFIER_MAP               Modifiers,
  IN UINTN                            NumberOfKeyCodes,
  IN APPLE_KEY_CODE                   *KeyCodes
  )
{
  EFI_STATUS               Status;

  KEY_MAP_AGGREGATOR_DATA *KeyMapAggregatorData;
  APPLE_KEY_STROKES_INFO  *KeyStrokesInfo;

  KeyMapAggregatorData = KEY_MAP_AGGREGATOR_DATA_FROM_DATABASE_THIS (This);

  KeyStrokesInfo = InternalGetKeyStrokesByIndex (
                     KeyMapAggregatorData,
                     Index
                     );

  Status = EFI_NOT_FOUND;

  if (KeyStrokesInfo != NULL) {
    Status = EFI_OUT_OF_RESOURCES;

    if (KeyStrokesInfo->KeyCodeBufferLength >= NumberOfKeyCodes) {
      KeyStrokesInfo->NumberOfKeyCodes = NumberOfKeyCodes;
      KeyStrokesInfo->Modifiers        = Modifiers;

      CopyMem (
        (VOID *)&KeyStrokesInfo->KeyCodes[0],
        (VOID *)KeyCodes,
        (NumberOfKeyCodes * sizeof (*KeyCodes))
        );

      Status = EFI_SUCCESS;
    }
  }

  return Status;
}


/**
  InitializeAppleKeyMapAggregator

  @param[in] ImageHandle  The firmware allocated handle for the EFI image.
  @param[in] SystemTable  A pointer to the EFI System Table.

  @retval EFI_SUCCESS          The entry point is executed successfully.
  @retval EFI_ALREADY_STARTED  The protocol has already been installed.
**/
EFI_STATUS
EFIAPI
InitializeAppleKeyMapAggregator (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS               Status;
  EFI_HANDLE               NewHandle             = NULL;
  EFI_HANDLE               *Buffer               = NULL;
  UINTN                    NumberOfHandles       = 0;
  KEY_MAP_AGGREGATOR_DATA  *KeyMapAggregatorData = NULL;

  Status = gBS->LocateHandleBuffer (
                  ByProtocol,
                  &gAppleKeyMapDatabaseProtocolGuid,
                  NULL,
                  &NumberOfHandles,
                  &Buffer
                  );

  if (!EFI_ERROR (Status)) {
    Status = EFI_ALREADY_STARTED;

    if (Buffer != NULL) {
      gBS->FreePool ((VOID *)Buffer);
    }
  } else {
    KeyMapAggregatorData = AllocateZeroPool (sizeof (*KeyMapAggregatorData));

    if (KeyMapAggregatorData == NULL) {
      return EFI_OUT_OF_RESOURCES;
    }

    KeyMapAggregatorData->Signature          = KEY_MAP_AGGREGATOR_DATA_SIGNATURE;
    KeyMapAggregatorData->NextKeyStrokeIndex = 3000;

    KeyMapAggregatorData->Database.Revision               = APPLE_KEY_MAP_DATABASE_PROTOCOL_REVISION;
    KeyMapAggregatorData->Database.CreateKeyStrokesBuffer = InternalCreateKeyStrokesBuffer;
    KeyMapAggregatorData->Database.RemoveKeyStrokesBuffer = InternalRemoveKeyStrokesBuffer;
    KeyMapAggregatorData->Database.SetKeyStrokeBufferKeys = InternalSetKeyStrokeBufferKeys;

    KeyMapAggregatorData->Aggregator.Revision           = APPLE_KEY_MAP_AGGREGATOR_PROTOCOL_REVISION;
    KeyMapAggregatorData->Aggregator.GetKeyStrokes      = InternalGetKeyStrokes;
    KeyMapAggregatorData->Aggregator.ContainsKeyStrokes = InternalContainsKeyStrokes;

    InitializeListHead (&KeyMapAggregatorData->KeyStrokesInfoList);

    Status = gBS->InstallMultipleProtocolInterfaces (
      &NewHandle,
      &gAppleKeyMapDatabaseProtocolGuid,
      (VOID *)&KeyMapAggregatorData->Database,
      &gAppleKeyMapAggregatorProtocolGuid,
      (VOID *)&KeyMapAggregatorData->Aggregator,
      NULL
      );

  }

  return Status;
}
