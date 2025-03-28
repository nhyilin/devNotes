﻿#include "./xmsg_server.h"
#include <sstream>
#include <iostream>

int main(int argc, char* argv[]) {
  XMsgServer server;
  server.Start();
  for (int i = 0; i < 10; i++) {
    std::stringstream ss;
    ss << " msg : " << i + 1;
    server.SendMsg(ss.str());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  server.Stop();
  std::cout << "Server stoped!" << std::endl;
  return 0;
}
