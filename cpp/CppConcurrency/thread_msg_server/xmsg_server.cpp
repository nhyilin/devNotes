#include "xmsg_server.h"
#include <iostream>

// 处理消息的线程入口函数
void XMsgServer::Main() {
  std::this_thread::sleep_for(std::chrono::milliseconds(500));
  while (!is_exit()) {
    // 最大消息处理时延
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::unique_lock<std::mutex> lock(mux_);
    if (msgs_.empty()) continue;
    while (!msgs_.empty()) {
      // 消息处理业务逻辑
      std::cout << "recv : " << msgs_.front() << std::endl;
      msgs_.pop_front();
    }
  }
}

// 给当前线程发消息
void XMsgServer::SendMsg(std::string msg) {
  std::unique_lock<std::mutex> lock(mux_);
  msgs_.push_back(msg);
}
