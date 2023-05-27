#include "process_reader.h"


#include <process.h>
#include "mingw_header/mingw.thread.h"
#include "socket_server.h"

int main() {
  ProcessReader *reader = new ProcessReader();
  SocketServer *server = new SocketServer(1000 /*interval*/);
  server->Init();
  std::thread read_data_thread(ProcessReader::LoopUpdateUserPosition, reader, 1000 /*sleep_time*/);
  std::thread transfer_data_thread(SocketServer::TransferData, server);
	read_data_thread.join();
  transfer_data_thread.join();

  delete reader;
  delete server;

  return 0;
}