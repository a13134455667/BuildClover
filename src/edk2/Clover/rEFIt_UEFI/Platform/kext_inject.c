#include "Platform.h"

#define KEXT_INJECT_DEBUG 0

#if KEXT_INJECT_DEBUG == 2
#define DBG(...) MsgLog(__VA_ARGS__)
#elif KEXT_INJECT_DEBUG == 1
#define DBG(...)  AsciiPrint(__VA_ARGS__);
#else
#define DBG(...)
#endif

// runtime debug
#define DBG_RT(entry, ...)    if ((entry != NULL) && (entry->KernelAndKextPatches != NULL) && entry->KernelAndKextPatches->KPDebug) { AsciiPrint(__VA_ARGS__); }


////////////////////
// globals
////////////////////
LIST_ENTRY gKextList = INITIALIZE_LIST_HEAD_VARIABLE (gKextList);


////////////////////
// before booting
////////////////////
EFI_STATUS EFIAPI ThinFatFile(IN OUT UINT8 **binary, IN OUT UINTN *length, IN cpu_type_t archCpuType)
{
  UINT32 nfat, swapped, size = 0;
  FAT_HEADER *fhp = (FAT_HEADER *)*binary;
  FAT_ARCH   *fap = (FAT_ARCH *)(*binary + sizeof(FAT_HEADER));
  cpu_type_t fapcputype;
  UINT32 fapoffset;
  UINT32 fapsize;

  swapped = 0;
  if (fhp->magic == FAT_MAGIC) {
    nfat = fhp->nfat_arch;
  } else if (fhp->magic == FAT_CIGAM) {
    nfat = SwapBytes32(fhp->nfat_arch);
    swapped = 1;
    //already thin
  } else if (fhp->magic == THIN_X64){
    if (archCpuType == CPU_TYPE_X86_64) {
      return EFI_SUCCESS;
    }
    return EFI_NOT_FOUND;
  } else if (fhp->magic == THIN_IA32){
    if (archCpuType == CPU_TYPE_I386) {
      return EFI_SUCCESS;
    }
    return EFI_NOT_FOUND;
  } else {
    MsgLog("Thinning fails\n");
    return EFI_NOT_FOUND;
  }

  for (; nfat > 0; nfat--, fap++) {
    if (swapped) {
      fapcputype = SwapBytes32(fap->cputype);
      fapoffset = SwapBytes32(fap->offset);
      fapsize = SwapBytes32(fap->size);
    } else {
      fapcputype = fap->cputype;
      fapoffset = fap->offset;
      fapsize = fap->size;
    }
    if (fapcputype == archCpuType) {
      *binary = (*binary + fapoffset);
      size = fapsize;
      break;
    }
  }
  if (length != 0) *length = size;

  return EFI_SUCCESS;
}

extern VOID KernelAndKextPatcherInit(IN LOADER_ENTRY *Entry);
extern VOID AnyKextPatch(UINT8 *Driver, UINT32 DriverSize, CHAR8 *InfoPlist, UINT32 InfoPlistSize, INT32 N, LOADER_ENTRY *Entry);

EFI_STATUS EFIAPI LoadKext(IN LOADER_ENTRY *Entry, IN EFI_FILE *RootDir, IN CHAR16 *FileName, IN cpu_type_t archCpuType, IN OUT _DeviceTreeBuffer *kext)
{
  EFI_STATUS  Status;
  UINT8*      infoDictBuffer = NULL;
  UINTN       infoDictBufferLength = 0;
  UINT8*      executableFatBuffer = NULL;
  UINT8*      executableBuffer = NULL;
  UINTN       executableBufferLength = 0;
  CHAR8*      bundlePathBuffer = NULL;
  UINTN       bundlePathBufferLength = 0;
  CHAR16      TempName[256];
  CHAR16      Executable[256];
  TagPtr      dict = NULL;
  TagPtr      prop = NULL;
  BOOLEAN     NoContents = FALSE;
  _BooterKextFileInfo *infoAddr = NULL;

  UnicodeSPrint(TempName, 512, L"%s\\%s", FileName, L"Contents\\Info.plist");
  Status = egLoadFile(RootDir, TempName, &infoDictBuffer, &infoDictBufferLength);
  if (EFI_ERROR(Status)) {
    //try to find a planar kext, without Contents
    UnicodeSPrint(TempName, 512, L"%s\\%s", FileName, L"Info.plist");
    Status = egLoadFile(RootDir, TempName, &infoDictBuffer, &infoDictBufferLength);
    if (EFI_ERROR(Status)) {
      MsgLog("Failed to load extra kext (Info.plist not found): %s\n", FileName);
      return EFI_NOT_FOUND;
    }
    NoContents = TRUE;
  }
  if(ParseXML((CHAR8*)infoDictBuffer,&dict,(UINT32)infoDictBufferLength)!=0) {
    FreePool(infoDictBuffer);
    MsgLog("Failed to load extra kext (failed to parse Info.plist): %s\n", FileName);
    return EFI_NOT_FOUND;
  }
  prop = GetProperty(dict,"CFBundleExecutable");
  if(prop!=0) {
    AsciiStrToUnicodeStrS(prop->string, Executable, 256);
    if (NoContents) {
      UnicodeSPrint(TempName, 512, L"%s\\%s", FileName, Executable);
    } else {
      UnicodeSPrint(TempName, 512, L"%s\\%s\\%s", FileName, L"Contents\\MacOS",Executable);
    }
    Status = egLoadFile(RootDir, TempName, &executableFatBuffer, &executableBufferLength);
    if (EFI_ERROR(Status)) {
      FreePool(infoDictBuffer);
      MsgLog("Failed to load extra kext (executable not found): %s\n", FileName);
      return EFI_NOT_FOUND;
    }
    executableBuffer = executableFatBuffer;
    if (ThinFatFile(&executableBuffer, &executableBufferLength, archCpuType)) {
      FreePool(infoDictBuffer);
      FreePool(executableBuffer);
      MsgLog("Thinning failed: %s\n", FileName);
      return EFI_NOT_FOUND;
    }
  }
  bundlePathBufferLength = StrLen(FileName) + 1;
  bundlePathBuffer = AllocateZeroPool(bundlePathBufferLength);
  UnicodeStrToAsciiStrS(FileName, bundlePathBuffer, bundlePathBufferLength);

  kext->length = (UINT32)(sizeof(_BooterKextFileInfo) + infoDictBufferLength + executableBufferLength + bundlePathBufferLength);
  infoAddr = (_BooterKextFileInfo *)AllocatePool(kext->length);
  infoAddr->infoDictPhysAddr = sizeof(_BooterKextFileInfo);
  infoAddr->infoDictLength = (UINT32)infoDictBufferLength;
  infoAddr->executablePhysAddr = (UINT32)(sizeof(_BooterKextFileInfo) + infoDictBufferLength);
  infoAddr->executableLength = (UINT32)executableBufferLength;
  infoAddr->bundlePathPhysAddr = (UINT32)(sizeof(_BooterKextFileInfo) + infoDictBufferLength + executableBufferLength);
  infoAddr->bundlePathLength = (UINT32)bundlePathBufferLength;
  kext->paddr = (UINT32)(UINTN)infoAddr; // Note that we cannot free infoAddr because of this
  CopyMem((CHAR8 *)infoAddr + sizeof(_BooterKextFileInfo), infoDictBuffer, infoDictBufferLength);
  CopyMem((CHAR8 *)infoAddr + sizeof(_BooterKextFileInfo) + infoDictBufferLength, executableBuffer, executableBufferLength);
  CopyMem((CHAR8 *)infoAddr + sizeof(_BooterKextFileInfo) + infoDictBufferLength + executableBufferLength, bundlePathBuffer, bundlePathBufferLength);
  FreePool(infoDictBuffer);
  FreePool(executableFatBuffer);
  FreePool(bundlePathBuffer);

  return EFI_SUCCESS;
}

EFI_STATUS EFIAPI AddKext(IN LOADER_ENTRY *Entry, IN EFI_FILE *RootDir, IN CHAR16 *FileName, IN cpu_type_t archCpuType)
{
  EFI_STATUS  Status;
  KEXT_ENTRY  *KextEntry;

  KextEntry = AllocatePool (sizeof(KEXT_ENTRY));
  KextEntry->Signature = KEXT_SIGNATURE;
  Status = LoadKext(Entry, RootDir, FileName, archCpuType, &KextEntry->kext);
  if(EFI_ERROR(Status)) {
    FreePool(KextEntry);
  } else {
    InsertTailList (&gKextList, &KextEntry->Link);
  }

  return Status;
}

UINT32 GetListCount(LIST_ENTRY const* List)
{
  LIST_ENTRY    *Link;
  UINT32      Count=0;

  if(!IsListEmpty(List)) {
    for (Link = List->ForwardLink; Link != List; Link = Link->ForwardLink)
      Count++;
  }

  return Count;
}

UINT32 GetKextCount()
{
  return (UINT32)GetListCount(&gKextList);
}

UINT32 GetKextsSize()
{
  LIST_ENTRY    *Link;
  KEXT_ENTRY    *KextEntry;
  UINT32        kextsSize=0;

  if(!IsListEmpty(&gKextList)) {
    for (Link = gKextList.ForwardLink; Link != &gKextList; Link = Link->ForwardLink) {
      KextEntry = CR(Link, KEXT_ENTRY, Link, KEXT_SIGNATURE);
      kextsSize += RoundPage(KextEntry->kext.length);
    }
  }
  return kextsSize;
}

VOID LoadPlugInKexts(IN LOADER_ENTRY *Entry, IN EFI_FILE *RootDir, IN CHAR16 *DirName, IN cpu_type_t archCpuType, IN BOOLEAN Force)
{
   REFIT_DIR_ITER          PlugInIter;
   EFI_FILE_INFO           *PlugInFile;
   CHAR16                  FileName[256];
   if ((Entry == NULL) || (RootDir == NULL) || (DirName == NULL)) {
      return;
   }
   DirIterOpen(RootDir, DirName, &PlugInIter);
   while (DirIterNext(&PlugInIter, 1, L"*.kext", &PlugInFile)) {
      if (PlugInFile->FileName[0] == '.' || StrStr(PlugInFile->FileName, L".kext") == NULL)
         continue;   // skip this

      UnicodeSPrint(FileName, 512, L"%s\\%s", DirName, PlugInFile->FileName);
      MsgLog("    %s PlugIn kext: %s\n", Force ? L"Force" : L"Extra", FileName);
      AddKext(Entry, RootDir, FileName, archCpuType);
   }
   DirIterClose(&PlugInIter);
}

VOID AddKexts(IN LOADER_ENTRY *Entry, CHAR16 *SrcDir, CHAR16 *Path, CHAR16 *UniSysVers, cpu_type_t archCpuType)
{
  CHAR16                  FileName[256];
  CHAR16                  PlugInName[256];
  SIDELOAD_KEXT           *CurrentKext;
  SIDELOAD_KEXT           *CurrentPlugInKext;

  MsgLog("Preparing kexts injection for arch=%s from %s\n", (archCpuType==CPU_TYPE_X86_64)?L"x86_64":(archCpuType==CPU_TYPE_I386)?L"i386":L"", SrcDir);
  CurrentKext = InjectKextList;
  while (CurrentKext) {
    DBG("current kext name %s Match %s, while sysver: %s\n", CurrentKext->FileName, CurrentKext->MatchOS, UniSysVers);
    if (StrStr(CurrentKext->MatchOS, Path) != NULL) {
      UnicodeSPrint(FileName, 512, L"%s\\%s", SrcDir, CurrentKext->FileName);
      if (!(CurrentKext->MenuItem.BValue)) {
        // inject require
        MsgLog("Extra kext: %s (v.%s)\n", FileName, CurrentKext->Version);
        AddKext(Entry, SelfVolume->RootDir, FileName, archCpuType);

        // decide which plugins to inject
        CurrentPlugInKext = CurrentKext->PlugInList;
        while (CurrentPlugInKext) {
          UnicodeSPrint(PlugInName, 512, L"%s\\%s\\%s", FileName, L"Contents\\PlugIns", CurrentPlugInKext->FileName);
          if (!(CurrentPlugInKext->MenuItem.BValue)) {
            // inject PlugIn require
            MsgLog("  |-- PlugIn kext: %s (v.%s)\n", PlugInName, CurrentPlugInKext->Version);
            AddKext(Entry, SelfVolume->RootDir, PlugInName, archCpuType);
          } else {
            MsgLog("  |-- Disabled plug-in kext: %s (v.%s)\n", PlugInName, CurrentPlugInKext->Version);
          }
          CurrentPlugInKext = CurrentPlugInKext->Next;
        } // end of plug-in kext injection
      } else {
        // disable current kext injection
        MsgLog("Disabled kext: %s (v.%s)\n", FileName, CurrentKext->Version);
      }
    }
    CurrentKext = CurrentKext->Next;
  } // end of kext injection

}

EFI_STATUS LoadKexts(IN LOADER_ENTRY *Entry)
{
  CHAR16                  *SrcDir = NULL;
  REFIT_DIR_ITER          PlugInIter;
  EFI_FILE_INFO           *PlugInFile;
  CHAR16                  FileName[256];
  CHAR16                  PlugIns[256];
  CHAR16                  *Arch = NULL;
  CHAR16                  *Ptr = NULL;
#if defined(MDE_CPU_X64)
  cpu_type_t              archCpuType=CPU_TYPE_X86_64;
#else
  cpu_type_t              archCpuType=CPU_TYPE_I386;
#endif
  UINTN                    mm_extra_size;
  VOID                    *mm_extra;
  UINTN                    extra_size;
  VOID                    *extra;

  SIDELOAD_KEXT           *CurrentKext = NULL;
  SIDELOAD_KEXT           *CurrentPlugInKext = NULL;
  SIDELOAD_KEXT           *Next = NULL;

  if (Entry == 0)/* || OSFLAG_ISUNSET(Entry->Flags, OSFLAG_WITHKEXTS) */ {
    return EFI_NOT_STARTED;
  }

  // Make Arch point to the last appearance of "arch=" in LoadOptions (which is what boot.efi will use).
  if (Entry->LoadOptions != NULL) {
    for (Ptr = StrStr(Entry->LoadOptions, L"arch="); Ptr != NULL; Arch = Ptr + StrLen(L"arch="), Ptr = StrStr(Arch, L"arch="));
  }

  if (Arch != NULL && StrnCmp(Arch,L"x86_64",StrLen(L"x86_64")) == 0) {
    archCpuType = CPU_TYPE_X86_64;
  } else if (Arch != NULL && StrnCmp(Arch,L"i386",StrLen(L"i386")) == 0) {
    archCpuType = CPU_TYPE_I386;
  } else if (Entry->OSVersion != NULL) {
    UINT64 os_version = AsciiOSVersionToUint64(Entry->OSVersion);
    if (os_version >= AsciiOSVersionToUint64("10.8")) {
      archCpuType = CPU_TYPE_X86_64; // For OSVersion >= 10.8, only x86_64 exists
    } else if (os_version < AsciiOSVersionToUint64("10.7")) {
      archCpuType = CPU_TYPE_I386; // For OSVersion < 10.7, use default of i386
    }
  }

  // Force kexts to load
  if ((Entry->KernelAndKextPatches != NULL) &&
      (Entry->KernelAndKextPatches->NrForceKexts > 0) &&
      (Entry->KernelAndKextPatches->ForceKexts != NULL)) {
    INT32 i = 0;
    for (; i < Entry->KernelAndKextPatches->NrForceKexts; ++i) {
      MsgLog("  Force kext: %s\n", Entry->KernelAndKextPatches->ForceKexts[i]);
      if (Entry->Volume && Entry->Volume->RootDir) {
        // Check if the entry is a directory
        if (StrStr(Entry->KernelAndKextPatches->ForceKexts[i], L".kext") == NULL) {
          DirIterOpen(Entry->Volume->RootDir, Entry->KernelAndKextPatches->ForceKexts[i], &PlugInIter);
          while (DirIterNext(&PlugInIter, 1, L"*.kext", &PlugInFile)) {
            if (PlugInFile->FileName[0] == '.' || StrStr(PlugInFile->FileName, L".kext") == NULL)
              continue;   // skip this

            UnicodeSPrint(FileName, 512, L"%s\\%s", Entry->KernelAndKextPatches->ForceKexts[i], PlugInFile->FileName);
            MsgLog("  Force kext: %s\n", FileName);
            AddKext(Entry, Entry->Volume->RootDir, FileName, archCpuType);
            UnicodeSPrint(PlugIns, 512, L"%s\\Contents\\PlugIns", FileName);
            LoadPlugInKexts(Entry, Entry->Volume->RootDir, PlugIns, archCpuType, TRUE);
          }
          DirIterClose(&PlugInIter);
        } else {
          AddKext(Entry, Entry->Volume->RootDir, Entry->KernelAndKextPatches->ForceKexts[i], archCpuType);

          UnicodeSPrint(PlugIns, 512, L"%s\\Contents\\PlugIns", Entry->KernelAndKextPatches->ForceKexts[i]);
          LoadPlugInKexts(Entry, Entry->Volume->RootDir, PlugIns, archCpuType, TRUE);
        }
      }
    }
  }

  CHAR16 UniSysVers[6];
  CHAR8  ShortOSVersion[6];
  if (AsciiOSVersionToUint64(Entry->OSVersion) < AsciiOSVersionToUint64("10.10")) {
    // OSVersion that are earlier than 10.10(form: 10.x.y)
    AsciiStrnCpyS(ShortOSVersion, 6, Entry->OSVersion, 4);
    AsciiStrToUnicodeStrS(Entry->OSVersion, UniSysVers, 5);
  } else {
    AsciiStrnCpyS(ShortOSVersion, 6, Entry->OSVersion, 5);
    AsciiStrToUnicodeStrS(Entry->OSVersion, UniSysVers, 6);
  }

  // syscl - allow specific load inject kext
  // Clover/Kexts/Other is for general injection thus we need to scan both Other and OSVersion folder
  if ((SrcDir = GetOtherKextsDir(TRUE)) != NULL) {
    AddKexts(Entry, SrcDir, L"Other", UniSysVers, archCpuType);
    FreePool(SrcDir);
  }
    // slice: CLOVER/kexts/Off keep disabled kext which can be allowed
  if ((SrcDir = GetOtherKextsDir(FALSE)) != NULL) {
    AddKexts(Entry, SrcDir, L"Off", UniSysVers, archCpuType);
    FreePool(SrcDir);
  }

  if ((SrcDir = GetOSVersionKextsDir(ShortOSVersion)) != NULL) {
    AddKexts(Entry, SrcDir, UniSysVers, UniSysVers, archCpuType);
    FreePool(SrcDir);
  }

  // reserve space in the device tree
  if (GetKextCount() > 0) {
    mm_extra_size = GetKextCount() * (sizeof(DeviceTreeNodeProperty) + sizeof(_DeviceTreeBuffer));
    mm_extra = AllocateZeroPool(mm_extra_size - sizeof(DeviceTreeNodeProperty));
    /*Status =  */LogDataHub(&gEfiMiscSubClassGuid, L"mm_extra", mm_extra, (UINT32)(mm_extra_size - sizeof(DeviceTreeNodeProperty)));
    extra_size = GetKextsSize();
    extra = AllocateZeroPool(extra_size - sizeof(DeviceTreeNodeProperty) + EFI_PAGE_SIZE);
    /*Status =  */LogDataHub(&gEfiMiscSubClassGuid, L"extra", extra, (UINT32)(extra_size - sizeof(DeviceTreeNodeProperty) + EFI_PAGE_SIZE));
    // MsgLog("count: %d    \n", GetKextCount());
    // MsgLog("mm_extra_size: %d    \n", mm_extra_size);
    // MsgLog("extra_size: %d     \n", extra_size);
    // MsgLog("offset: %d       \n", extra_size - sizeof(DeviceTreeNodeProperty) + EFI_PAGE_SIZE);
    //no more needed
    FreePool(mm_extra);
    FreePool(extra);
  }

  //No more InjectKextList needed. Will free the list
  while (InjectKextList) {
    CurrentKext = InjectKextList->Next;
    CurrentPlugInKext = InjectKextList->PlugInList;
    while (CurrentPlugInKext) {
      Next = CurrentPlugInKext->Next;
      FreePool(CurrentPlugInKext->FileName);
      FreePool(CurrentPlugInKext->MatchOS);
      FreePool(CurrentPlugInKext->Version);
      FreePool(CurrentPlugInKext);
      CurrentPlugInKext = Next;
    }
    FreePool(InjectKextList->FileName);
    FreePool(InjectKextList->MatchOS);
    FreePool(InjectKextList->Version);
    FreePool(InjectKextList);
    InjectKextList = CurrentKext;
  }
  return EFI_SUCCESS;
}


////////////////////
// OnExitBootServices
////////////////////
EFI_STATUS InjectKexts(/*IN EFI_MEMORY_DESCRIPTOR *Desc*/ IN UINT32 deviceTreeP, IN UINT32* deviceTreeLength, LOADER_ENTRY *Entry)
{
  UINT8                              *dtEntry = (UINT8*)(UINTN) deviceTreeP;
  UINTN                              dtLength = (UINTN) *deviceTreeLength;

  DTEntry                            platformEntry;
  DTEntry                            memmapEntry;
  CHAR8                             *ptr;
  struct OpaqueDTPropertyIterator   OPropIter;
  DTPropertyIterator                iter = &OPropIter;
  DeviceTreeNodeProperty            *prop = NULL;

  UINT8                              *infoPtr = 0;
  UINT8                              *extraPtr = 0;
  UINT8                              *drvPtr = 0;
  UINTN                              offset = 0;

  LIST_ENTRY                        *Link;
  KEXT_ENTRY                        *KextEntry;
  UINTN                              KextBase = 0;
  _DeviceTreeBuffer                  *mm;
  _BooterKextFileInfo                *drvinfo;

  UINT32                            KextCount;
  UINTN                              Index;


  DBG_RT(Entry, "\nInjectKexts: ");
  KextCount = GetKextCount();
  if (KextCount == 0) {
    DBG_RT(Entry, "no kexts to inject.\nPausing 5 secs ...\n");
    if (Entry->KernelAndKextPatches->KPDebug) {
      gBS->Stall(5000000);
    }
    return EFI_NOT_FOUND;
  }
  DBG_RT(Entry, "%d kexts ...\n", KextCount);

  // kextsBase = Desc->PhysicalStart + (((UINTN) Desc->NumberOfPages) * EFI_PAGE_SIZE);
  // kextsPages = EFI_SIZE_TO_PAGES(kext.length);
  // Status = gBS->AllocatePages(AllocateAddress, EfiLoaderData, kextsPages, &kextsBase);
  // if (EFI_ERROR(Status)) { MsgLog("Kext inject: could not allocate memory\n"); return Status; }
  // Desc->NumberOfPages += kextsPages;
  // CopyMem((VOID*)kextsBase, (VOID*)(UINTN)kext.paddr, kext.length);
  // drvinfo = (_BooterKextFileInfo*) kextsBase;
  // drvinfo->infoDictPhysAddr += (UINT32)kextsBase;
  // drvinfo->executablePhysAddr += (UINT32)kextsBase;
  // drvinfo->bundlePathPhysAddr += (UINT32)kextsBase;

  DTInit(dtEntry);
  if(DTLookupEntry(NULL,"/chosen/memory-map",&memmapEntry)==kSuccess) {
    if(DTCreatePropertyIteratorNoAlloc(memmapEntry,iter)==kSuccess) {
      while(DTIterateProperties(iter,&ptr)==kSuccess) {
        prop = iter->currentProperty;
        drvPtr = (UINT8*) prop;
        if(AsciiStrnCmp(prop->name, "Driver-", 7)==0 || AsciiStrnCmp(prop->name, "DriversPackage-", 15)==0) {
          break;
        }
      }
    }
  }

  if(DTLookupEntry(NULL,"/efi/platform",&platformEntry)==kSuccess) {
    if(DTCreatePropertyIteratorNoAlloc(platformEntry,iter)==kSuccess) {
      while(DTIterateProperties(iter,&ptr)==kSuccess) {
        prop = iter->currentProperty;
        if(AsciiStrCmp(prop->name,"mm_extra")==0) {
          infoPtr = (UINT8*) prop;
        }
        if(AsciiStrCmp(prop->name,"extra")==0) {
          extraPtr = (UINT8*) prop;
        }
      }
    }
  }

  if (drvPtr == 0 || infoPtr == 0 || extraPtr == 0 || drvPtr > infoPtr || drvPtr > extraPtr || infoPtr > extraPtr) {
    Print(L"\nInvalid device tree for kext injection\n");
    gBS->Stall(5000000);
    return EFI_INVALID_PARAMETER;
  }

  // make space for memory map entries
  platformEntry->nProperties -= 2;
  offset = sizeof(DeviceTreeNodeProperty) + ((DeviceTreeNodeProperty*) infoPtr)->length;
  CopyMem(drvPtr+offset, drvPtr, infoPtr-drvPtr);

  // make space behind device tree
  // platformEntry->nProperties--;
  offset = sizeof(DeviceTreeNodeProperty)+((DeviceTreeNodeProperty*) extraPtr)->length;
  CopyMem(extraPtr, extraPtr+offset, dtLength-(UINTN)(extraPtr-dtEntry)-offset);
  *deviceTreeLength -= (UINT32)offset;

  KextBase = RoundPage(dtEntry + *deviceTreeLength);
  if(!IsListEmpty(&gKextList)) {
    Index = 1;
    for (Link = gKextList.ForwardLink; Link != &gKextList; Link = Link->ForwardLink) {
      KextEntry = CR(Link, KEXT_ENTRY, Link, KEXT_SIGNATURE);

      CopyMem((VOID*) KextBase, (VOID*)(UINTN) KextEntry->kext.paddr, KextEntry->kext.length);
      drvinfo = (_BooterKextFileInfo*) KextBase;
      drvinfo->infoDictPhysAddr += (UINT32) KextBase;
      drvinfo->executablePhysAddr += (UINT32) KextBase;
      drvinfo->bundlePathPhysAddr += (UINT32) KextBase;

      memmapEntry->nProperties++;
      prop = ((DeviceTreeNodeProperty*) drvPtr);
      prop->length = sizeof(_DeviceTreeBuffer);
      mm = (_DeviceTreeBuffer*) (((UINT8*)prop) + sizeof(DeviceTreeNodeProperty));
      mm->paddr = (UINT32)KextBase;
      mm->length = KextEntry->kext.length;
      AsciiSPrint(prop->name, 31, "Driver-%x", KextBase);

      drvPtr += sizeof(DeviceTreeNodeProperty) + sizeof(_DeviceTreeBuffer);
      KextBase = RoundPage(KextBase + KextEntry->kext.length);
      DBG_RT(Entry, " %d - %a\n", Index, (CHAR8 *)(UINTN)drvinfo->bundlePathPhysAddr);
      if (gSettings.KextPatchesAllowed) {
        INT32  i;
        CHAR8  SavedValue;
        CHAR8 *InfoPlist = (CHAR8*)(UINTN)drvinfo->infoDictPhysAddr;
        SavedValue = InfoPlist[drvinfo->infoDictLength];
        InfoPlist[drvinfo->infoDictLength] = '\0';
        KernelAndKextPatcherInit(Entry);
        for (i = 0; i < Entry->KernelAndKextPatches->NrKexts; i++) {
          if ((Entry->KernelAndKextPatches->KextPatches[i].DataLen > 0) &&
              (AsciiStrStr(InfoPlist, Entry->KernelAndKextPatches->KextPatches[i].Name) != NULL)) {
            AnyKextPatch(
                         (UINT8*)(UINTN)drvinfo->executablePhysAddr,
                         drvinfo->executableLength,
                         InfoPlist,
                         drvinfo->infoDictLength,
                         i,
                         Entry
                         );
          }
        }
        InfoPlist[drvinfo->infoDictLength] = SavedValue;
      }
      Index++;
    }
  }

   if (Entry->KernelAndKextPatches->KPDebug) {
    DBG_RT(Entry, "Done.\n");
    gBS->Stall(5000000);
  }
  return EFI_SUCCESS;
}


////////////////////////////////////
//
// KernelBooterExtensionsPatch to load extra kexts besides kernelcache
//
//

// Snow Leopard i386
UINT8   KBESnowSearchEXT_i386[]  = { 0xE8, 0xED, 0xF9, 0xFF, 0xFF, 0xEB, 0x08, 0x89, 0x1C, 0x24 };
UINT8   KBESnowReplaceEXT_i386[] = { 0xE8, 0xED, 0xF9, 0xFF, 0xFF, 0x90, 0x90, 0x89, 0x1C, 0x24 };

// Snow Leopard X64
UINT8   KBESnowSearchEXT_X64[]   = { 0xE8, 0x5A, 0xFB, 0xFF, 0xFF, 0xEB, 0x08, 0x48, 0x89, 0xDF };
UINT8   KBESnowReplaceEXT_X64[]  = { 0xE8, 0x5A, 0xFB, 0xFF, 0xFF, 0x90, 0x90, 0x48, 0x89, 0xDF };

// Lion i386
UINT8   KBELionSearchEXT_i386[]  = { 0xE8, 0xAA, 0xFB, 0xFF, 0xFF, 0xEB, 0x08, 0x89, 0x34, 0x24 };
UINT8   KBELionReplaceEXT_i386[] = { 0xE8, 0xAA, 0xFB, 0xFF, 0xFF, 0x90, 0x90, 0x89, 0x34, 0x24 };

// Lion X64
UINT8   KBELionSearchEXT_X64[]   = { 0xE8, 0x0C, 0xFD, 0xFF, 0xFF, 0xEB, 0x08, 0x48, 0x89, 0xDF };
UINT8   KBELionReplaceEXT_X64[]  = { 0xE8, 0x0C, 0xFD, 0xFF, 0xFF, 0x90, 0x90, 0x48, 0x89, 0xDF };


//
// We can not rely on OSVersion global variable for OS version detection,
// since in some cases it is not correct (install of ML from Lion, for example).
// So, we'll use "brute-force" method - just try to patch.
// Actually, we'll at least check that if we can find only one instance of code that
// we are planning to patch.
//
// Fully reworked by Sherlocks. 2019.06.23
//

VOID EFIAPI KernelBooterExtensionsPatch(IN UINT8 *Kernel, LOADER_ENTRY *Entry)
{
  UINTN   Num = 0;
  UINTN   NumSnow_i386_EXT   = 0;
  UINTN   NumSnow_X64_EXT    = 0;
  UINTN   NumLion_i386_EXT   = 0;
  UINTN   NumLion_X64_EXT    = 0;
  UINT32  patchLocation1 = 0, patchLocation2 = 0, patchLocation3 = 0;
  UINT32  i, y;

  DBG_RT(Entry, "\nPatching kernel for injected kexts...\n");

  if (is64BitKernel) {
    NumSnow_X64_EXT  = SearchAndCount(Kernel, KERNEL_MAX_SIZE, KBESnowSearchEXT_X64, sizeof(KBESnowSearchEXT_X64));
    NumLion_X64_EXT  = SearchAndCount(Kernel, KERNEL_MAX_SIZE, KBELionSearchEXT_X64, sizeof(KBELionSearchEXT_X64));
  } else {
    NumSnow_i386_EXT = SearchAndCount(Kernel, KERNEL_MAX_SIZE, KBESnowSearchEXT_i386, sizeof(KBESnowSearchEXT_i386));
    NumLion_i386_EXT = SearchAndCount(Kernel, KERNEL_MAX_SIZE, KBELionSearchEXT_i386, sizeof(KBELionSearchEXT_i386));
  }

  if (NumSnow_i386_EXT + NumSnow_X64_EXT + NumLion_i386_EXT + NumLion_X64_EXT > 1) {
    // more then one pattern found - we do not know what to do with it
    // and we'll skipp it
    AsciiPrint("\nERROR patching kernel for injected kexts:\nmultiple patterns found (Snowi386: %d, SnowX64: %d, Lioni386: %d, LionX64: %d) - skipping patching!\n", NumSnow_i386_EXT, NumSnow_X64_EXT, NumLion_i386_EXT, NumLion_X64_EXT);
    gBS->Stall(10000000);
    return;
  }

  // X64
  if (is64BitKernel) {
    if (NumSnow_X64_EXT == 1) {
      Num = SearchAndReplace(Kernel, KERNEL_MAX_SIZE, KBESnowSearchEXT_X64, sizeof(KBESnowSearchEXT_X64), KBESnowReplaceEXT_X64, 1);
      DBG_RT(Entry, "==> kernel Snow Leopard X64: %d replaces done.\n", Num);
    } else if (NumLion_X64_EXT == 1) {
      Num = SearchAndReplace(Kernel, KERNEL_MAX_SIZE, KBELionSearchEXT_X64, sizeof(KBELionSearchEXT_X64), KBELionReplaceEXT_X64, 1);
      DBG_RT(Entry, "==> kernel Lion X64: %d replaces done.\n", Num);
    } else {
      // EXT - load extra kexts besides kernelcache.
      for (i = 0; i < 0x1000000; i++) {
        // 01 00 31 FF BE 14 00 05
        if (Kernel[i+0] == 0x01 && Kernel[i+1] == 0x00 && Kernel[i+2] == 0x31 &&
            Kernel[i+3] == 0xFF && Kernel[i+4] == 0xBE && Kernel[i+5] == 0x14 &&
            Kernel[i+6] == 0x00 && Kernel[i+7] == 0x05) {
          for (y = i; y < 0x1000000; y++) {
            // E8 XX 00 00 00 EB XX XX
            if (Kernel[y+0] == 0xE8 && Kernel[y+2] == 0x00 && Kernel[y+3] == 0x00 &&
                Kernel[y+4] == 0x00 && Kernel[y+5] == 0xEB) {
                //(Kernel[y+7] == 0x48 || Kernel[y+7] == 0xE8)) { // 48:10.8-10.9/E8:10.10+
              patchLocation1 = y;
              DBG_RT(Entry, "==> found EXT (10.8 - recent macOS) at 0x%08x\n", patchLocation1);
              break;
            }
          }
          break;
        }
      }
            
      if (!patchLocation1) {
        DBG_RT(Entry, "==> can't find EXT (10.8 - recent macOS), kernel patch aborted.\n");
        gBS->Stall(3000000);
      }
            
      if (patchLocation1) {
        DBG_RT(Entry, "==> patched EXT (10.8 - recent macOS)\n");
        for (i = 5; i < 7; i++) {
          // E8 XX 00 00 00 EB XX XX
          // E8 XX 00 00 00 90 90 XX
          Kernel[patchLocation1 + i] = 0x90;
        }
      }
            
      // SIP - bypass kext check by System Integrity Protection.
      for (i = 0; i < 0x1000000; i++) {
        // 45 31 FF 41 XX 01 00 00 DC 48
        if (Kernel[i+0] == 0x45 && Kernel[i+1] == 0x31 && Kernel[i+3] == 0x41 &&
            //(Kernel[i+4] == 0xBF || Kernel[i+4] == 0xBE) && // BF:10.11/BE:10.12+
            Kernel[i+5] == 0x01 && Kernel[i+6] == 0x00 && Kernel[i+7] == 0x00 &&
            Kernel[i+8] == 0xDC && Kernel[i+9] == 0x48) {
          for (y = i; y < 0x1000000; y++) {
            // 48 85 XX 74 XX 48 XX XX 48
            if (Kernel[y+0] == 0x48 && Kernel[y+1] == 0x85 && Kernel[y+3] == 0x74 &&
                Kernel[y+5] == 0x48 && Kernel[y+8] == 0x48) {
              patchLocation2 = y;
              DBG_RT(Entry, "==> found SIP (10.11 - 10.14) at 0x%08x\n", patchLocation2);
              break;
            // 00 85 C0 0F 84 XX 00 00 00 49
            } else if (Kernel[y+0] == 0x00 && Kernel[y+1] == 0x85 && Kernel[y+2] == 0xC0 &&
                       Kernel[y+3] == 0x0F && Kernel[y+4] == 0x84 && Kernel[y+9] == 0x49) {
              patchLocation2 = y;
              DBG_RT(Entry, "==> found SIP (10.15 - recent macOS) at 0x%08x\n", patchLocation2);
              break;
            }
          }
          break;
        }
      }
            
      if (!patchLocation2) {
        DBG_RT(Entry, "==> can't find SIP (10.11 - recent macOS), kernel patch aborted.\n");
        gBS->Stall(3000000);
      }
                
      if (patchLocation2) {
        if (Kernel[patchLocation2 + 0] == 0x48 && Kernel[patchLocation2 + 1] == 0x85) {
            Kernel[patchLocation2 + 3] = 0xEB;
          DBG_RT(Entry, "==> patched SIP (10.11 - 10.14)\n");
          if (Kernel[patchLocation2 + 4] == 0x6C) {
            // 48 85 XX 74 6C 48 XX XX 48
            // 48 85 XX EB 15 48 XX XX 48
            Kernel[patchLocation2 + 4] = 0x15; // 10.14.4-10.14.6
          } else {
            // 48 85 XX 74 XX 48 XX XX 48
            // 48 85 XX EB 12 48 XX XX 48
            Kernel[patchLocation2 + 4] = 0x12; // 10.11-10.14.3
          }
        // PMheart
        } else if (Kernel[patchLocation2 + 0] == 0x00 && Kernel[patchLocation2 + 1] == 0x85) {
          DBG_RT(Entry, "==> patched SIP (10.15 - recent macOS)\n");
          for (i = 3; i < 9; i++) {
            // 00 85 C0 0F 84 XX 00 00 00 49
            // 00 85 C0 90 90 90 90 90 90 49
            Kernel[patchLocation2 + i] = 0x90;
          }
        }
      }
            
      // KxldUnmap by vit9696
      // Avoid race condition in OSKext::removeKextBootstrap when using booter kexts without keepsyms=1.
      for (i = 0; i < 0x1000000; i++) {
        // 55 48 89 E5 41 57 41 56 41 54 53 //10
        // 48 83 EC 30 48 C7 45 B8 XX XX XX //21
        // XX XX XX XX XX XX XX XX XX XX XX //32
        // XX XX XX XX XX XX XX XX XX XX XX //43
        // XX XX XX XX XX XX XX XX 31 FF BE //54
        // 14 XX XX XX 31 C0 E8 XX XX FF FF //65
        if (Kernel[i+0] == 0x55 && Kernel[i+1] == 0x48 && Kernel[i+2] == 0x89 &&
            Kernel[i+3] == 0xE5 && Kernel[i+4] == 0x41 && Kernel[i+5] == 0x57 &&
            Kernel[i+6] == 0x41 && Kernel[i+7] == 0x56 && Kernel[i+8] == 0x41 &&
            Kernel[i+9] == 0x54 && Kernel[i+10] == 0x53 && Kernel[i+11] == 0x48 &&
            Kernel[i+12] == 0x83 && Kernel[i+13] == 0xEC && Kernel[i+14] == 0x30 &&
            Kernel[i+15] == 0x48 && Kernel[i+16] == 0xC7 && Kernel[i+17] == 0x45 &&
            Kernel[i+18] == 0xB8 && Kernel[i+52] == 0x31 && Kernel[i+53] == 0xFF &&
            Kernel[i+54] == 0xBE && Kernel[i+55] == 0x14 && Kernel[i+59] == 0x31 &&
            Kernel[i+60] == 0xC0 && Kernel[i+61] == 0xE8 && Kernel[i+64] == 0xFF && Kernel[i+65] == 0xFF) {
          for (y = i; y < 0x1000000; y++) {
            // 00 0F 85 XX XX 00 00 48
            if (Kernel[y+0] == 0x00 && Kernel[y+1] == 0x0F && Kernel[y+2] == 0x85 &&
                Kernel[y+5] == 0x00 && Kernel[y+6] == 0x00 && Kernel[y+7] == 0x48) {
              patchLocation3 = y;
              DBG_RT(Entry, "==> found KxldUnmap (10.14 - recent macOS) at 0x%08x\n", patchLocation3);
              break;
            }
          }
          break;
        }
      }
            
      if (!patchLocation3) {
        DBG_RT(Entry, "==> can't find KxldUnmap (10.14 - recent macOS), kernel patch aborted.\n");
        gBS->Stall(3000000);
      }

      if (patchLocation3) {
        DBG_RT(Entry, "==> patched KxldUnmap (10.14 - recent macOS)\n");
        // 00 0F 85 XX XX 00 00 48
        // 00 90 E9 XX XX 00 00 48
        Kernel[patchLocation3 + 1] = 0x90;
        Kernel[patchLocation3 + 2] = 0xE9;
      }
    }
  } else {
    // i386
    if (NumSnow_i386_EXT == 1) {
      Num = SearchAndReplace(Kernel, KERNEL_MAX_SIZE, KBESnowSearchEXT_i386, sizeof(KBESnowSearchEXT_i386), KBESnowReplaceEXT_i386, 1);
      DBG_RT(Entry, "==> kernel Snow Leopard i386: %d replaces done.\n", Num);
    } else if (NumLion_i386_EXT == 1) {
      Num = SearchAndReplace(Kernel, KERNEL_MAX_SIZE, KBELionSearchEXT_i386, sizeof(KBELionSearchEXT_i386), KBELionReplaceEXT_i386, 1);
      DBG_RT(Entry, "==> kernel Lion i386: %d replaces done.\n", Num);
    } else {
      DBG_RT(Entry, "==> ERROR: NOT patched - unknown kernel.\n");
    }
  }

  if (Entry->KernelAndKextPatches->KPDebug) {
    DBG_RT(Entry, "Pausing 5 secs ...\n");
    gBS->Stall(5000000);
  }
}
