#include <iostream>
#include <variant>
#include <string>
#include <cassert>

int main()
{
    std::variant<int, float> v, w;
    v = 12; // v 含 int
    int i = std::get<int>(v);
    w = std::get<int>(v);
    w = std::get<0>(v); // 与前一行效果相同
    w = v; // 与前一行效果相同

    //  std::get<double>(v); // 错误： [int, float] 中无 double
    //  std::get<3>(v);      // 错误：合法下标值为 0 与 1

    try {
        std::get<float>(w); // w 含 int 而非 float ：将抛出
    }
    catch (const std::bad_variant_access&) {}

    using namespace std::literals;

    std::variant<std::string> x("abc"); // 转换构造函数在无歧义时起作用
    x = "def"; // 转换赋值在无歧义时亦起作用

    std::variant<std::string, void const*> y("abc");
    // 传递 char const * 时转换成 void const *
    assert(std::holds_alternative<void const*>(y)); // 成功
    y = "xyz"s;
    assert(std::holds_alternative<std::string>(y)); // 成功
}


