#include "./xmsg_server.h"
#include <iostream>

void XMsgServer::Stop() {
  is_exit_ = true;
  cv_.notify_all();
  Wait();
}

// 处理消息的线程入口函数
void XMsgServer::Main() {
  while (!is_exit()) {
    // std::this_thread::sleep_for(10ms);
    std::unique_lock<std::mutex> lock(mux_);
    cv_.wait(lock, [this] {
      std::cout << "wait cv" << std::endl;
      if (is_exit()) return true;
      return !msgs_.empty();
    });
    while (!msgs_.empty()) {
      // 消息处理业务逻辑
      std::cout << "recv : " << msgs_.front() << std::endl;
      msgs_.pop_front();
    }
  }
}

// 给当前线程发消息
void XMsgServer::SendMsg(const std::string& msg) {
  std::unique_lock<std::mutex> lock(mux_);
  msgs_.push_back(msg);
  lock.unlock();
  cv_.notify_one();
}
