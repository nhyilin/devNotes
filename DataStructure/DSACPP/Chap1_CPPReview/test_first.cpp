//
// Created by 裴奕霖 on 2022/12/22.
//
#include "first.h"
void devideAnswers(int questions) {
    std::cout << "**************\n";
    std::cout << "// " << questions << "\n";
}
int main() {
    // 1
    devideAnswers(1);
    int a = 0, b = 9;
    swap(a, b);

    std::cout << "a: " << a << "\t b: " << b << std::endl;

    // 2
    devideAnswers(2);
    int int_list[] = {1, 2, 3, 4, 9};
    double double_list[] = {1.2, 3.2, 7.9, 9.0, 8.99, 9.02};
    std::cout << count(int_list) << std::endl;
    std::cout << count(double_list) << std::endl;

    // 3
    devideAnswers(3);
    double x = 9.9;
    fill(double_list, 6, x);
    for (auto iter : double_list) {
        std::cout << iter << std::endl;
    }

    // 4
    devideAnswers(4);
    double list01[] = {1.2, 2.1, 3.4, 5.4};
    double list02[] = {9.2, 2.7, 1.4, 0.4};
    std::cout << "sum: " << inner_prodcut(list01, list02, 4) << std::endl;

    // 6
    devideAnswers(6);
    std::cout << "is_sorted: " << is_sorted(list01, 4) << std::endl;
    std::cout << "is_sorted: " << is_sorted(list02, 4) << std::endl;

    // 7
    devideAnswers(7);
    double list01_7[] = {1.2, 2.1, 3.4, 5.4};
    double list02_7[] = {1.2, 2.12, 3.4, 5.5};
    std::cout << "first mismatch element: " << mismatch(list01_7, list02_7, 4)
              << std::endl;

    // 12
    devideAnswers(12);
    int **myArray = nullptr;
    int rowSize[] = {1, 2, 3, 5};
    myMake2dArray(myArray, 9, rowSize);

    // 13
    devideAnswers(13);
    int devideAnswers_13[] = {1, 2, 3, 5};
    //    changeLength1D(devideAnswers_13, 4,6);//TODO 这里调用方法还不确定
    for (int i : devideAnswers_13) std::cout << i << std::endl;

    // 1-33
    devideAnswers(33);
    std::cout << sum(devideAnswers_13, 4);

    devideAnswers(34);
    std::cout<<Prodect(devideAnswers_13,4);

//    std::cin.get();
}
