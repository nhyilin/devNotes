//
// Created by 裴奕霖 on 2023/6/9.
//
#ifndef AATOOLS_SRC_OE2TLE_OE2TLE_H_
#define AATOOLS_SRC_OE2TLE_OE2TLE_H_
#include "../../pch.h"

class oe2tle {
 public:
  TLE parse(const std::string &line1, const std::string &line2);
 private:
  template<typename T>
  T extract(const std::string &s, int pos, int len);
};

#endif //AATOOLS_SRC_OE2TLE_OE2TLE_H_
