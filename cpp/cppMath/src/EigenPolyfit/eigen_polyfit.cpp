#include <Eigen/Dense>
#include <Eigen/QR>
#include <cmath>
#include <iostream>
#include <vector>

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void polyfit(const std::vector<double> &t, const std::vector<double> &v,
             std::vector<double> &coeff, int order

) {
    // Create Matrix Placeholder of size n x k, n= number of datapoints, k =
    // order of polynomial, for exame k = 3 for cubic polynomial
    Eigen::MatrixXd T(t.size(), order + 1);
    Eigen::VectorXd V = Eigen::VectorXd::Map(&v.front(), v.size());
    // std::cout<<"ceshi"<<std::endl;
    // std::cout<<V<<std::endl;
    Eigen::VectorXd result;

    // check to make sure inputs are correct
    assert(t.size() == v.size());
    assert(t.size() >= order + 1);
    // Populate the matrix
    for (size_t i = 0; i < t.size(); ++i) {
        for (size_t j = 0; j < order + 1; ++j) {
            T(i, j) = pow(t.at(i), j);
        }
    }
    std::cout << T << std::endl;

    // Solve for linear least square fit
    result = T.householderQr().solve(V);
    coeff.resize(order + 1);
    for (int k = 0; k < order + 1; k++) {
        coeff[k] = result[k];
    }
}

int main() {
    // time value
    std::vector<double> time = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    // velocity value
    std::vector<double> velocity = {9, 7, 6, 3, -1, 2, 5, 7, 20};

    // placeholder for storing polynomial coefficient
    std::vector<double> coeff;
    polyfit(time, velocity, coeff, 3);

    std::vector<double> fitted_velocity;
    std::cout << "Printing fitted values" << std::endl;
    for (int p = 0; p < time.size(); ++p) {
        double vfitted = coeff[0] + coeff[1] * time.at(p) +
                         coeff[2] * (pow(time.at(p), 2)) +
                         coeff[3] * (pow(time.at(p), 3));
        std::cout << vfitted << ", ";
        fitted_velocity.push_back(vfitted);
    }
    std::cout << std::endl;

    /*原始数据*/
    plt::figure();
    // plt::subplot(2,2,1);
    plt::title("originaldata");
    plt::plot(time, velocity);
    plt::figure();
    /*最小二乘拟合后的数据*/
    // plt::subplot(2,2,2);
    plt::title("polyfitdata");
    plt::plot(time, fitted_velocity);
    plt::show();
    return 0;
}
