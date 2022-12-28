//
// Created by 裴奕霖 on 2022/12/22.
//
#include "first.h"
int main() {
    // 1
    int a = 0, b = 9;
    swap(a, b);
    std::cout << "// 1\n";
    std::cout << "**************\n";
    std::cout << "a: " << a << "\t b: " << b << std::endl;
    std::cout << "**************\n";
    // 2
    std::cout << "// 2\n";
    int int_list[] = {1, 2, 3, 4, 9};
    double double_list[] = {1.2, 3.2, 7.9, 9.0, 8.99, 9.02};
    std::cout << count(int_list) << std::endl;
    std::cout << count(double_list) << std::endl;
    std::cout << "**************\n";

    // 3
    std::cout << "// 3\n";
    double x = 9.9;
    fill(double_list, 6, x);
    for (auto iter : double_list) {
        std::cout << iter << std::endl;
    }
    std::cout << "**************\n";

    // 4
    std::cout << "// 4\n";
    double list01[] = {1.2, 2.1, 3.4, 5.4};
    double list02[] = {9.2, 2.7, 1.4, 0.4};
    std::cout << "sum: " << inner_prodcut(list01, list02, 4) << std::endl;
    std::cout << "**************\n";

    // 6
    std::cout << "// 6\n";
    std::cout << "is_sorted: " << is_sorted(list01, 4) << std::endl;
    std::cout << "is_sorted: " << is_sorted(list02, 4) << std::endl;
    std::cout << "**************\n";

    //7
    std::cout << "// 7\n";
    double list01_7[] = {1.2, 2.1, 3.4, 5.4};
    double list02_7[] = {1.2, 2.12, 3.4, 5.5};
    std::cout << "first mismatch element: " << mismatch(list01_7,list02_7, 4) << std::endl;
    std::cout << "**************\n";
}
