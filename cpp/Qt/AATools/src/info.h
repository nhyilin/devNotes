//
// Created by 裴奕霖 on 2023/6/9.
//

#ifndef AATOOLS__INFO_H_
#define AATOOLS__INFO_H_

struct TLE {
  // 两行根数的信息
  std::string name; // 卫星名称
  int sat_num; // 卫星编号
  char classification; // 分类
  std::string int_designator; // 国际标识符
  int epoch_year; // 轨道历时年份
  double epoch_day; // 轨道历时年积日和当天时刻
  double first_deriv; // 平均运动的一阶时间导数
  double second_deriv; // 平均运动的二阶时间导数
  double bstar; // BSTAR阻力系数
  int ephemeris_type; // 星历类型
  int element_num; // 星历编号
  int checksum1; // 第一行校验和
  double inclination; // 轨道倾角
  double raan; // 升交点赤经
  double eccentricity; // 轨道偏心率
  double arg_perigee; // 近地点幅角
  double mean_anomaly; // 平近点角
  double mean_motion; // 平均运动
  int rev_num; // 发射以来飞行的圈数
  int checksum2; // 第二行校验和
};


#endif //AATOOLS__INFO_H_
