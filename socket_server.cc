#include "socket_server.h"

#include <windows.h>
#include <iostream>

constexpr int kSocketPort = 8888;

void SocketServer::Init() {
  WORD sockVersion = MAKEWORD(2, 2);
  WSADATA wsaData;
  if (WSAStartup(sockVersion, &wsaData) != 0) {
    return;
  }

  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (socket_ == INVALID_SOCKET) {
    return;
  }
}

void SocketServer::TransferData() {
  sockaddr_in sin;
  sin.sin_family = AF_INET;
  sin.sin_port = htons(kSocketPort);
  sin.sin_addr.S_un.S_addr = INADDR_ANY;
  if (bind(socket_, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR) {
    std::cout << "Bind socket error." << std::endl;
  }

  if (listen(socket_, 5) == SOCKET_ERROR) {
    std::cout << "Listen socket error." << std::endl;
    return;
  }

  SOCKET client;
  sockaddr_in remote_addr;
  int nAddrlen = sizeof(remote_addr);
  char revData[255];
  while (true) {
    client = accept(socket_, (SOCKADDR *)&remote_addr, &nAddrlen);
    if (client == INVALID_SOCKET) {
      continue;
    }
    std::cout << "Found connection." << std::endl;

    int ret = recv(client, revData, 255, 0);
    if (ret > 0) {
      revData[ret] = 0x00;
      printf(revData);
    }

    const char *sendData = "hello Client\n";
    while (true) {
      send(client, sendData, strlen(sendData), 0);
      Sleep(interval_);
    }

    closesocket(client);
  }
}

SocketServer::~SocketServer() {
  closesocket(socket_);
  WSACleanup();
}
