# 1 "/Users/weisiyuan/src/edk2/MdePkg/Library/BaseLib/X64/LongJump.nasm"
# 1 "<built-in>" 1
# 362 "<built-in>"
# 1 "/Users/weisiyuan/src/edk2/Build/Clover/RELEASE_XCODE8/X64/MdePkg/Library/BaseLib/BaseLib/DEBUG/AutoGen.h" 1
# 16 "/Users/weisiyuan/src/edk2/Build/Clover/RELEASE_XCODE8/X64/MdePkg/Library/BaseLib/BaseLib/DEBUG/AutoGen.h"
# 1 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h" 1
# 28 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
# 1 "/Users/weisiyuan/src/edk2/MdePkg/Include/X64/ProcessorBind.h" 1
# 41 "/Users/weisiyuan/src/edk2/MdePkg/Include/X64/ProcessorBind.h"
#pragma GCC visibility push (hidden)
# 188 "/Users/weisiyuan/src/edk2/MdePkg/Include/X64/ProcessorBind.h"
 typedef unsigned long long UINT64;



  typedef long long INT64;



  typedef unsigned int UINT32;



  typedef int INT32;



  typedef unsigned short UINT16;




  typedef unsigned short CHAR16;



  typedef short INT16;




  typedef unsigned char BOOLEAN;



  typedef unsigned char UINT8;



  typedef char CHAR8;



  typedef signed char INT8;






typedef UINT64 UINTN;




typedef INT64 INTN;
# 29 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h" 2
# 54 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
extern UINT8 _VerifySizeofBOOLEAN[(sizeof(BOOLEAN) == (1)) / (sizeof(BOOLEAN) == (1))];
extern UINT8 _VerifySizeofINT8[(sizeof(INT8) == (1)) / (sizeof(INT8) == (1))];
extern UINT8 _VerifySizeofUINT8[(sizeof(UINT8) == (1)) / (sizeof(UINT8) == (1))];
extern UINT8 _VerifySizeofINT16[(sizeof(INT16) == (2)) / (sizeof(INT16) == (2))];
extern UINT8 _VerifySizeofUINT16[(sizeof(UINT16) == (2)) / (sizeof(UINT16) == (2))];
extern UINT8 _VerifySizeofINT32[(sizeof(INT32) == (4)) / (sizeof(INT32) == (4))];
extern UINT8 _VerifySizeofUINT32[(sizeof(UINT32) == (4)) / (sizeof(UINT32) == (4))];
extern UINT8 _VerifySizeofINT64[(sizeof(INT64) == (8)) / (sizeof(INT64) == (8))];
extern UINT8 _VerifySizeofUINT64[(sizeof(UINT64) == (8)) / (sizeof(UINT64) == (8))];
extern UINT8 _VerifySizeofCHAR8[(sizeof(CHAR8) == (1)) / (sizeof(CHAR8) == (1))];
extern UINT8 _VerifySizeofCHAR16[(sizeof(CHAR16) == (2)) / (sizeof(CHAR16) == (2))];
# 73 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
typedef enum {
  __VerifyUint8EnumValue = 0xff
} __VERIFY_UINT8_ENUM_SIZE;

typedef enum {
  __VerifyUint16EnumValue = 0xffff
} __VERIFY_UINT16_ENUM_SIZE;

typedef enum {
  __VerifyUint32EnumValue = 0xffffffff
} __VERIFY_UINT32_ENUM_SIZE;

extern UINT8 _VerifySizeof__VERIFY_UINT8_ENUM_SIZE[(sizeof(__VERIFY_UINT8_ENUM_SIZE) == (4)) / (sizeof(__VERIFY_UINT8_ENUM_SIZE) == (4))];
extern UINT8 _VerifySizeof__VERIFY_UINT16_ENUM_SIZE[(sizeof(__VERIFY_UINT16_ENUM_SIZE) == (4)) / (sizeof(__VERIFY_UINT16_ENUM_SIZE) == (4))];
extern UINT8 _VerifySizeof__VERIFY_UINT32_ENUM_SIZE[(sizeof(__VERIFY_UINT32_ENUM_SIZE) == (4)) / (sizeof(__VERIFY_UINT32_ENUM_SIZE) == (4))];
# 280 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
typedef struct {
  UINT32 Data1;
  UINT16 Data2;
  UINT16 Data3;
  UINT8 Data4[8];
} GUID;




typedef struct {
  UINT8 Addr[4];
} IPv4_ADDRESS;




typedef struct {
  UINT8 Addr[16];
} IPv6_ADDRESS;




typedef UINT64 PHYSICAL_ADDRESS;




typedef struct _LIST_ENTRY LIST_ENTRY;




struct _LIST_ENTRY {
  LIST_ENTRY *ForwardLink;
  LIST_ENTRY *BackLink;
};
# 696 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
typedef __builtin_ms_va_list VA_LIST;
# 800 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
typedef UINTN *BASE_LIST;
# 964 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
typedef UINTN RETURN_STATUS;
# 1280 "/Users/weisiyuan/src/edk2/MdePkg/Include/Base.h"
  void * __builtin_return_address (unsigned int level);
# 17 "/Users/weisiyuan/src/edk2/Build/Clover/RELEASE_XCODE8/X64/MdePkg/Library/BaseLib/BaseLib/DEBUG/AutoGen.h" 2
# 1 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h" 1
# 1082 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINTN

LibPcdSetSku (
     UINTN SkuId
  );
# 1099 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT8

LibPcdGet8 (
     UINTN TokenNumber
  );
# 1116 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT16

LibPcdGet16 (
     UINTN TokenNumber
  );
# 1133 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT32

LibPcdGet32 (
     UINTN TokenNumber
  );
# 1150 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT64

LibPcdGet64 (
     UINTN TokenNumber
  );
# 1167 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPcdGetPtr (
     UINTN TokenNumber
  );
# 1184 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
BOOLEAN

LibPcdGetBool (
     UINTN TokenNumber
  );
# 1199 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINTN

LibPcdGetSize (
     UINTN TokenNumber
  );
# 1220 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT8

LibPcdGetEx8 (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1242 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT16

LibPcdGetEx16 (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1261 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT32

LibPcdGetEx32 (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1283 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT64

LibPcdGetEx64 (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1305 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPcdGetExPtr (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1327 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
BOOLEAN

LibPcdGetExBool (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1349 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINTN

LibPcdGetExSize (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 1370 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT8

LibPcdSet8 (
     UINTN TokenNumber,
     UINT8 Value
  );
# 1390 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT16

LibPcdSet16 (
     UINTN TokenNumber,
     UINT16 Value
  );
# 1410 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT32

LibPcdSet32 (
     UINTN TokenNumber,
     UINT32 Value
  );
# 1430 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT64

LibPcdSet64 (
     UINTN TokenNumber,
     UINT64 Value
  );
# 1460 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPcdSetPtr (
            UINTN TokenNumber,
            UINTN *SizeOfBuffer,
     const void *Buffer
  );
# 1481 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
BOOLEAN

LibPcdSetBool (
     UINTN TokenNumber,
     BOOLEAN Value
  );
# 1505 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT8

LibPcdSetEx8 (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT8 Value
  );
# 1530 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT16

LibPcdSetEx16 (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT16 Value
  );
# 1555 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT32

LibPcdSetEx32 (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT32 Value
  );
# 1580 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINT64

LibPcdSetEx64 (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT64 Value
  );
# 1611 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPcdSetExPtr (
          const GUID *Guid,
          UINTN TokenNumber,
          UINTN *SizeOfBuffer,
          void *Buffer
  );
# 1637 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
BOOLEAN

LibPcdSetExBool (
     const GUID *Guid,
     UINTN TokenNumber,
     BOOLEAN Value
  );
# 1658 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSet8S (
     UINTN TokenNumber,
     UINT8 Value
  );
# 1677 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSet16S (
     UINTN TokenNumber,
     UINT16 Value
  );
# 1696 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSet32S (
     UINTN TokenNumber,
     UINT32 Value
  );
# 1715 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSet64S (
     UINTN TokenNumber,
     UINT64 Value
  );
# 1744 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetPtrS (
           UINTN TokenNumber,
           UINTN *SizeOfBuffer,
     const void *Buffer
  );
# 1764 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetBoolS (
     UINTN TokenNumber,
     BOOLEAN Value
  );
# 1787 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetEx8S (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT8 Value
  );
# 1811 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetEx16S (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT16 Value
  );
# 1835 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetEx32S (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT32 Value
  );
# 1859 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetEx64S (
     const GUID *Guid,
     UINTN TokenNumber,
     UINT64 Value
  );
# 1889 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetExPtrS (
     const GUID *Guid,
           UINTN TokenNumber,
           UINTN *SizeOfBuffer,
           void *Buffer
  );
# 1914 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPcdSetExBoolS (
     const GUID *Guid,
     UINTN TokenNumber,
     BOOLEAN Value
  );
# 1938 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
typedef
void
( *PCD_CALLBACK)(
            const GUID *CallBackGuid,
            UINTN CallBackToken,
            void *TokenData,
            UINTN TokenDataSize
  );
# 1964 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void

LibPcdCallbackOnSet (
     const GUID *Guid,
     UINTN TokenNumber,
     PCD_CALLBACK NotificationFunction
  );
# 1986 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void

LibPcdCancelCallback (
     const GUID *Guid,
     UINTN TokenNumber,
     PCD_CALLBACK NotificationFunction
  );
# 2014 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINTN

LibPcdGetNextToken (
     const GUID *Guid,
     UINTN TokenNumber
  );
# 2036 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
GUID *

LibPcdGetNextTokenSpace (
     const GUID *TokenSpaceGuid
  );
# 2066 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPatchPcdSetPtr (
             void *PatchVariable,
            UINTN MaximumDatumSize,
            UINTN *SizeOfBuffer,
     const void *Buffer
  );
# 2098 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPatchPcdSetPtrS (
           void *PatchVariable,
           UINTN MaximumDatumSize,
           UINTN *SizeOfBuffer,
     const void *Buffer
  );
# 2132 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void *

LibPatchPcdSetPtrAndSize (
            void *PatchVariable,
            UINTN *SizeOfPatchVariable,
            UINTN MaximumDatumSize,
            UINTN *SizeOfBuffer,
     const void *Buffer
  );
# 2167 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
RETURN_STATUS

LibPatchPcdSetPtrAndSizeS (
           void *PatchVariable,
           UINTN *SizeOfPatchVariable,
           UINTN MaximumDatumSize,
           UINTN *SizeOfBuffer,
     const void *Buffer
  );

typedef enum {
  PCD_TYPE_8,
  PCD_TYPE_16,
  PCD_TYPE_32,
  PCD_TYPE_64,
  PCD_TYPE_BOOL,
  PCD_TYPE_PTR
} PCD_TYPE;

typedef struct {




  PCD_TYPE PcdType;




  UINTN PcdSize;






  CHAR8 *PcdName;
} PCD_INFO;
# 2219 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void

LibPcdGetInfo (
            UINTN TokenNumber,
            PCD_INFO *PcdInfo
  );
# 2239 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
void

LibPcdGetInfoEx (
     const GUID *Guid,
            UINTN TokenNumber,
            PCD_INFO *PcdInfo
  );
# 2254 "/Users/weisiyuan/src/edk2/MdePkg/Include/Library/PcdLib.h"
UINTN

LibPcdGetSku (
  void
  );
# 18 "/Users/weisiyuan/src/edk2/Build/Clover/RELEASE_XCODE8/X64/MdePkg/Library/BaseLib/BaseLib/DEBUG/AutoGen.h" 2

extern GUID gEfiCallerIdGuid;
extern CHAR8 *gEfiCallerBaseName;



extern GUID gEfiMdePkgTokenSpaceGuid;


extern UINT64 _gPcd_SkuId_Array[];



extern const BOOLEAN _gPcd_FixedAtBuild_PcdVerifyNodeInList;



extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumLinkedListLength;






extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumAsciiStringLength;






extern const UINT32 _gPcd_FixedAtBuild_PcdMaximumUnicodeStringLength;






extern const UINT32 _gPcd_FixedAtBuild_PcdControlFlowEnforcementPropertyMask;
# 363 "<built-in>" 2
# 1 "/Users/weisiyuan/src/edk2/MdePkg/Library/BaseLib/X64/LongJump.nasm" 2
;------------------------------------------------------------------------------
;
; Copyright (c) 2006 - 2019, Intel Corporation. All rights reserved.<BR>
; This program and the accompanying materials
; are licensed and made available under the terms and conditions of the BSD License
; which accompanies this distribution. The full text of the license may be found at
; http:
;
; THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
; WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.
;
; Module Name:
;
; LongJump.Asm
;
; Abstract:
;
; Implementation of _LongJump() on x64.
;
;------------------------------------------------------------------------------

%include "Nasm.inc"

    DEFAULT REL
    SECTION .text

extern __gPcd_FixedAtBuild_PcdControlFlowEnforcementPropertyMask

;------------------------------------------------------------------------------
; void
;
; InternalLongJump (
; BASE_LIBRARY_JUMP_BUFFER *JumpBuffer,
; UINTN Value
; );
;------------------------------------------------------------------------------
global _InternalLongJump
_InternalLongJump:

    mov eax, [__gPcd_FixedAtBuild_PcdControlFlowEnforcementPropertyMask]
    test eax, eax
    jz CetDone
    mov rax, cr4
    bt eax, 23 ; check if CET is enabled
    jnc CetDone

    push rdx ; save rdx

    mov rdx, [rcx + 0xF8] ; rdx = target SSP
    READSSP_RAX
    sub rdx, rax ; rdx = delta
    mov rax, rdx ; rax = delta

    shr rax, 3 ; rax = delta/sizeof(UINT64)
    INCSSP_RAX

    pop rdx ; restore rdx
CetDone:

    mov rbx, [rcx]
    mov rsp, [rcx + 8]
    mov rbp, [rcx + 0x10]
    mov rdi, [rcx + 0x18]
    mov rsi, [rcx + 0x20]
    mov r12, [rcx + 0x28]
    mov r13, [rcx + 0x30]
    mov r14, [rcx + 0x38]
    mov r15, [rcx + 0x40]
    ; load non-volatile fp registers
    ldmxcsr [rcx + 0x50]
    movdqu xmm6, [rcx + 0x58]
    movdqu xmm7, [rcx + 0x68]
    movdqu xmm8, [rcx + 0x78]
    movdqu xmm9, [rcx + 0x88]
    movdqu xmm10, [rcx + 0x98]
    movdqu xmm11, [rcx + 0xA8]
    movdqu xmm12, [rcx + 0xB8]
    movdqu xmm13, [rcx + 0xC8]
    movdqu xmm14, [rcx + 0xD8]
    movdqu xmm15, [rcx + 0xE8]
    mov rax, rdx ; set return value
    jmp qword [rcx + 0x48]
