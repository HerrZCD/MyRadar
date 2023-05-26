#include "memory_util.h"

namespace MemoryUtil {
template <typename T> T RPM(HANDLE hProcess, DWORD address) {
    T buffer;
    ReadProcessMemory(hProcess, (LPCVOID)address, &buffer, sizeof(T), NULL);
    return buffer;
}
template <typename T> T ReadMemory(DWORD address) { return *((T*)address); }
template <typename T> void WriteMemory(DWORD address, T content) {
    *((T*)address) = content;
}
template <typename T> T* PointMemory(DWORD address) { return (T*)address; }

template <typename T> DWORD protectMemory(DWORD address, DWORD prot) {
    DWORD oldProt;
    VirtualProtect((LPVOID)address, sizeof(T), prot, &oldProt);
    return oldProt;
}
} // namespace MemoryUtil