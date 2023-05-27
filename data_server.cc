#include "process_reader.h"


#include <process.h>
#include "mingw_header/mingw.thread.h"

int main() {
  ProcessReader *reader = new ProcessReader();
  std::thread thread1(ProcessReader::LoopUpdateUserPosition, reader, 1000 /*sleep_time*/);
	thread1.join();
}