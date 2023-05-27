#include "process_reader.h"

#include "memory_util.h"
#include <iostream>

const char kClientModule[] = "client.dll";
const char kCSGOWindow[] = "Counter-Strike: Global Offensive - Direct3D 9";
const int kOffset1 = 0xDE997C;
const int kOffset2 = 0x138;
const int kGap = 4;

ProcessReader::ProcessReader() {
  HWND hWnd = FindWindowA(NULL, kCSGOWindow);
  DWORD dwPid = -1;
  GetWindowThreadProcessId(hWnd, &dwPid);
  game_handle_ = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);
  char *clientBase = MemoryUtil::GetModuleBase(kClientModule, dwPid);
  player_base_addr_ = MemoryUtil::RPM<int>((HANDLE)game_handle_,
                                           (LPCVOID)(clientBase + kOffset1));
}

void ProcessReader::UpdateUserPosition() {
  float player_position_x = MemoryUtil::RPM<float>(
      game_handle_, (LPCVOID)((DWORD)player_base_addr_ + kOffset2));
  float player_position_y = MemoryUtil::RPM<float>(
      game_handle_, (LPCVOID)((DWORD)player_base_addr_ + kOffset2 + kGap));
  std::cout << "Player is on x: " << player_position_x << std::endl;
  std::cout << "Player is on y: " << player_position_y << std::endl;
  player_position_ = base::Point(player_position_x, player_position_y);
}

void ProcessReader::LoopUpdateUserPosition(int sleep_time) {
  while (true) {
    UpdateUserPosition();
    Sleep(sleep_time);
  }
}