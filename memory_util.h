#ifndef BASE_PROCESS_UTIL_H_
#define BASE_PROCESS_UTIL_H_

#include <windows.h>
#include <tlHelp32.h>

namespace MemoryUtil {
template <typename T>
T RPM(HANDLE hProcess, DWORD address);
template <typename T>
T ReadMemory(DWORD address);
template <typename T>
void WriteMemory(DWORD address, T content);
template <typename T>
T* PointMemory(DWORD address);
template <typename T>
DWORD protectMemory(DWORD address, DWORD prot);
char* GetModuleBase(const wchar_t* ModuleName, DWORD procID);
}  // namespace MemoryUtil

#endif  // BASE_PROCESS_UTIL_H_