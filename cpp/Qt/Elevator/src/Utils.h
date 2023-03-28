//
// Created by 裴奕霖 on 2023/2/21.
//

#ifndef CHARTTHEMES_UTILS_H
#define CHARTTHEMES_UTILS_H


#include <cmath>
#include <vector>
#include <string>
#include "Net.h"

using std::vector;
using std::string;

namespace Utils {
    static double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }

    vector<double> getFileData(const string &filename,const std::string &file_type);//为了区分读取文件类型以及数据列数，只分为Train和Test

    vector<Sample> getTrainData(const string &filename);

    vector<Sample> getTestData(const string &filename);
}



#endif //CHARTTHEMES_UTILS_H
