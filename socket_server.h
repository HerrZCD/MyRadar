#ifndef SOCKET_SERVER_H_
#define SOCKET_SERVER_H_

#include <winsock2.h>

class SocketServer {
public:
  SocketServer() = default;
  SocketServer(int interval): interval_(interval) {};
  void Init();
  void TransferData();
  ~SocketServer();
private:
  SOCKET socket_;
  int interval_;
};
#endif // SOCKET_SERVER_H_