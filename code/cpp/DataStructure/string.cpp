//
// Created by 裴奕霖 on 2022/9/29.
//
#include <algorithm>
namespace string {
namespace ordered_string {

#define MAXLEN 255
struct SString {
    char ch[MAXLEN];
    int length;
    // 为了兼顾char存储一字节255数目太少以及位序和数组下标相同两个因素
    // 在这里我们采取ch[0]不使用且在ch最后几个位置存储整形length变量
};
struct HString {
    char* ch;
    int length;
};

void InitHString() {
    HString S;
    S.ch = new char;  // 使用完需要delete
    S.length = 0;
}

}  // namespace ordered_string

namespace linked_string {
struct StringNode {
    char ch;  // 这里是一个字符，为提高存储利用率，可以char ch[4]
    StringNode* next;
};
}  // namespace linked_string

namespace string_operation {
bool SubString(const ordered_string::SString& S, ordered_string::SString& sub,
               int pos, int len) {
    // 求字串，用sub返回串S的第pos个字符串起长度为len的字串
    if (len + pos - 1 > S.length) return false;  // TODO -1这里易错
    for (int i = 1; i < len + 1; ++i) {
        sub.ch[i] = S.ch[pos + i - 1];
    }
    sub.length = len;  // TODO 这里也很容易丢掉
    return true;
}
int CompareString(const ordered_string::SString& S,
                  const ordered_string::SString& T) {
    // 比较操作，若S>T，返回值>0，S=T返回0，否则<0
    //     bool ST = S.length > T.length ? true : false;
    //     if (ST){
    //           可以通过该方式来判定S、T的长度
    //     }
    for (int i = 1; i < std::min(S.length, T.length); ++i) {
        // TODO 第一次写的时候我把条件错写成i < std::min(S.length, T.length) + 1
        //  这里还是不确定的话带特殊值
        if (S.ch[i] > T.ch[i] != S.ch[i] < T.ch[i]) return (S.ch[i] - T.ch[i]);
    }
    return S.length - T.length;
}
int IndexString(const ordered_string::SString& S,
                const ordered_string::SString& Tsub) {
    // 定位操作，若主串S中存在与字串T值相同的字串，则返回他在主串S中第一次出现的位置，否则函数值为0
    ordered_string::SString sub;
    for (int i = 1; i < Tsub.length; ++i) {
        SubString(S,sub,i,Tsub.length);
        if (CompareString(sub,Tsub)==0)return i;
    }
    //书上写的while，无所谓了
    return 0;

}
}  // namespace string_operation
}  // namespace string