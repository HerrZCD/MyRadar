#include "memory_util.h"

namespace MemoryUtil {
char *GetModuleBase(const char *ModuleName, DWORD procID) {
  MODULEENTRY32 ModuleEntry = {0};
  HANDLE SnapShot =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procID);

  if (!SnapShot) {
    std::cout << "no SnapShot" << std::endl;
    return NULL;
  }

  ModuleEntry.dwSize = sizeof(MODULEENTRY32);

  if (!Module32First(SnapShot, &ModuleEntry)) {
    std::cout << "no Module32First(SnapShot, &ModuleEntry))" << std::endl;
  }

  do {
    if (!strcmp(ModuleEntry.szModule, ModuleName)) {
      CloseHandle(SnapShot);
      return (char *)ModuleEntry.modBaseAddr;
    }
  } while (Module32Next(SnapShot, &ModuleEntry));

  CloseHandle(SnapShot);
  return NULL;
}

BOOL ListProcessModules(DWORD dwPID) {
  HANDLE hModuleSnap = INVALID_HANDLE_VALUE;
  MODULEENTRY32 me32;

  //  Take a snapshot of all modules in the specified process.
  hModuleSnap =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwPID);
  if (hModuleSnap == INVALID_HANDLE_VALUE) {
    return (FALSE);
  }

  //  Set the size of the structure before using it.
  me32.dwSize = sizeof(MODULEENTRY32);

  //  Retrieve information about the first module,
  //  and exit if unsuccessful
  if (!Module32First(hModuleSnap, &me32)) {
    CloseHandle(hModuleSnap); // Must clean up the snapshot object!
    return (FALSE);
  }

  //  Now walk the module list of the process,
  //  and display information about each module
  do {
    printf_s(TEXT("\n\n     MODULE NAME:     %s"), me32.szModule);
    printf_s(TEXT("\n     executable     = %s"), me32.szExePath);
    printf_s(TEXT("\n     process ID     = 0x%08X"), me32.th32ProcessID);
    printf_s(TEXT("\n     ref count (g)  =     0x%04X"), me32.GlblcntUsage);
    printf_s(TEXT("\n     ref count (p)  =     0x%04X"), me32.ProccntUsage);
    printf_s(TEXT("\n     base address   = 0x%08X"), (DWORD)me32.modBaseAddr);
    printf_s(TEXT("\n     base size      = %d"), me32.modBaseSize);

  } while (Module32Next(hModuleSnap, &me32));

  printf_s(TEXT("\n"));

  //  Do not forget to clean up the snapshot object.
  CloseHandle(hModuleSnap);
  return (TRUE);
}
} // namespace MemoryUtil