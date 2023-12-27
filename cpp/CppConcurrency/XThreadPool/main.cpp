//
// Created by 裴奕霖 on 2023/12/4.
//
#include <iostream>
#include "XThreadPool.h"
int main(int argc, char* argv[]) {
  XThreadPool pool;
  pool.Init(16);
  pool.Start();
  std::cin.get();
  return 0;
}
