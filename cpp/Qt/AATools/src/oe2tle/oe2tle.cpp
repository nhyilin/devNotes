//
// Created by 裴奕霖 on 2023/6/9.
//
#include "../../pch.h"
#include "oe2tle.h"

template <typename T>
T oe2tle::extract(const std::string& s, int pos, int len) {
  std::string sub = s.substr(pos - 1, len); // 提取子串，注意下标从0开始，所以要减1
  T value; // 定义一个变量，用于存储转换后的值
  if constexpr (std::is_same_v<T, std::string>) { // 如果目标类型是字符串，就直接赋值
    value = sub;
  }
  else if constexpr (std::is_same_v<T, char>) { // 如果目标类型是字符，就取第一个字符
    value = sub[0];
  }
  else if constexpr (std::is_same_v<T, int>) { // 如果目标类型是整数，就使用stoi函数转换，并处理负号和空格的情况
    if (sub[0] == '-') {
      value = -stoi(sub.substr(1));
    }
    else if (sub[0] == ' ') {
      value = stoi(sub.substr(1));
    }
    else {
      value = stoi(sub);
    }
  }
  else if constexpr (std::is_same_v<T, double>) { // 如果目标类型是浮点数，就使用stod函数转换，并处理负号、空格和小数点的情况
    if (sub[0] == '-') {
      value = -stod("0." + sub.substr(1));
    }
    else if (sub[0] == ' ') {
      value = stod("0." + sub.substr(1));
    }
    else if (sub[0] == '.') {
      value = stod("0" + sub);
    }
    else {
      value = stod(sub);
    }
  }
  return value; // 返回转换后的值
}
TLE oe2tle::parse(const std::string &line1, const std::string &line2) {
    // 从两个字符串中解析出两行根数的信息，并存储到结构体中
    TLE tle; // 定义一个结构体变量，用于存储两行根数的信息
    tle.sat_num = extract<int>(line1, 3, 5); // 从第一行提取卫星编号（第3-7列）
    tle.classification = extract<char>(line1, 8, 1); // 从第一行提取分类（第8列）
    tle.int_designator = extract<std::string>(line1, 10, 8); // 从第一行提取国际标识符（第10-17列）
    tle.epoch_year = extract<int>(line1, 19, 2); // 从第一行提取轨道历时年份（第19-20列）
    tle.epoch_day = extract<double>(line1, 21, 12); // 从第一行提取轨道历时年积日和当天时刻（第21-32列）
    tle.first_deriv = extract<double>(line1, 34, 10); // 从第一行提取平均运动的一阶时间导数（第34-43列）
    tle.second_deriv = extract<double>(line1, 45, 8); // 从第一行提取平均运动的二阶时间导数（第45-52列）
    tle.bstar = extract<double>(line1, 54, 8); // 从第一行提取BSTAR阻力系数（第54-61列）
    tle.ephemeris_type = extract<int>(line1, 63, 1); // 从第一行提取星历类型（第63列）
    tle.element_num = extract<int>(line1, 65, 4); // 从第一行提取星历编号（第65-68列）
    tle.checksum1 = extract<int>(line1, 69, 1); // 从第一行提取校验和（第69列）
    tle.inclination = extract<double>(line2, 9, 8); // 从第二行提取轨道倾角（第9-16列）
    tle.raan = extract<double>(line2, 18, 8); // 从第二行提取升交点赤经（第18-25列）
    tle.eccentricity = extract<double>(line2, 27, 7); // 从第二行提取轨道偏心率（第27-33列）
    tle.arg_perigee = extract<double>(line2, 35, 8); // 从第二行提取近地点幅角（第35-42列）
    tle.mean_anomaly = extract<double>(line2, 44, 8); // 从第二行提取平近点角（第44-51列）
    tle.mean_motion = extract<double>(line2, 53, 11); // 从第二行提取平均运动（第53-63列）
    tle.rev_num = extract<int>(line2, 64, 5); // 从第二行提取发射以来飞行的圈数（第64-68列）
    tle.checksum2 = extract<int>(line2, 69, 1); // 从第二行提取校验和（第69列）
    return tle; // 返回结构体变量

}