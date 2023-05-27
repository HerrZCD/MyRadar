#ifndef BASE_PROCESS_UTIL_H_
#define BASE_PROCESS_UTIL_H_

#include <windows.h>

#include <stdio.h>
#include <tlhelp32.h>
#include <wchar.h>
#include <iostream>

namespace MemoryUtil {
template <typename T> T RPM(HANDLE hProcess, LPCVOID address) {
  T buffer;
  ReadProcessMemory(hProcess, address, &buffer, sizeof(T), NULL);
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

char* GetModuleBase(const char* ModuleName, DWORD procID);
BOOL ListProcessModules( DWORD dwPID );

} // namespace MemoryUtil

#endif // BASE_PROCESS_UTIL_H_