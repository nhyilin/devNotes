//
// Created by 裴奕霖 on 2023/12/4.
//

#include "XThreadPool.h"

#include <iostream>

void XThreadPool::Init(int num) {
  std::unique_lock<std::mutex> lock(mux_);
  this->thread_num_ = num;
  std::cout << "Thread pool Init " << num << std::endl;
}

// 启动所有线程，必须先调用Init
void XThreadPool::Start() {
  std::unique_lock<std::mutex> lock(mux_);
  if (thread_num_ <= 0) {
    std::cerr << "Please Init XThreadPool" << std::endl;
    return;
  }
  if (!threads_.empty()) {
    std::cerr << "Thread pool has start!" << std::endl;
    return;
  }
  // 启动线程
  for (int i = 0; i < thread_num_; i++) {
    auto th = new std::thread(&XThreadPool::Run, this);
    threads_.push_back(th);
  }
  std::cout << "Thread pool start " << thread_num_ << " threads" << std::endl;
  return;
}

/**
 * @brief 线程池线程的入口函数
 */
void XThreadPool::Run() {
  std::cout << "begin XThreadPool Run " << std::this_thread::get_id()
            << std::endl;

  std::cout << "end XThreadPool Run " << std::this_thread::get_id()
            << std::endl;
}
