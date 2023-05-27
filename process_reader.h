#ifndef PROCESS_READER_H_
#define PROCESS_READER_H_

#include "base.h"
#include <windows.h>

class ProcessReader {
public:
  ProcessReader();
  void UpdateUserPosition();
  void LoopUpdateUserPosition(int sleep_time = 1000);
  ProcessReader(const ProcessReader &) = delete;
  ProcessReader &operator=(const ProcessReader &) = delete;
  base::Point GetPlayerPosition() { return player_position_; }

private:
  HANDLE game_handle_;
  DWORD player_base_addr_;
  base::Point player_position_;
};
#endif // PROCESS_READER_H_
