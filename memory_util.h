#ifndef BASE_PROCESS_UTIL_H_
#define BASE_PROCESS_UTIL_H_

#include <windows.h>

#include <stdio.h>
#include <tlHelp32.h>
#include <wchar.h>

namespace MemoryUtil {
template <typename T> T RPM(HANDLE hProcess, DWORD address) {
  T buffer;
  ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
  return buffer;
}
template <typename T> T ReadMemory(DWORD address) { return *((T *)address); }
template <typename T> void WriteMemory(DWORD address, T content) {
  *((T *)address) = content;
}
template <typename T> T *PointMemory(DWORD address) { return (T *)address; }

template <typename T> DWORD protectMemory(DWORD address, DWORD prot) {
  DWORD oldProt;
  VirtualProtect((LPVOID)address, sizeof(T), prot, &oldProt);
  return oldProt;
}

char *GetModuleBase(const wchar_t *ModuleName, DWORD procID) {
  MODULEENTRY32 ModuleEntry = {0};
  HANDLE SnapShot =
      CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE, procID);

  if (!SnapShot)
    return NULL;

  ModuleEntry.dwSize = sizeof(ModuleEntry);

  if (!Module32First(SnapShot, &ModuleEntry))
    return NULL;

  do {
    if (!wcscmp((const wchar_t *)ModuleEntry.szModule, ModuleName)) {
      CloseHandle(SnapShot);
      return (char *)ModuleEntry.modBaseAddr;
    }
  } while (Module32Next(SnapShot, &ModuleEntry));

  CloseHandle(SnapShot);
  return NULL;
}
} // namespace MemoryUtil

#endif // BASE_PROCESS_UTIL_H_