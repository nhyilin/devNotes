//
// Created by 裴奕霖 on 2022/9/29.
//
namespace string {
namespace ordered_string{

#define MAXLEN 255
struct SString {
    char ch[MAXLEN];
    int length;
    //为了兼顾char存储一字节255数目太少以及位序和数组下标相同两个因素
    //在这里我们采取ch[0]不使用且在ch最后几个位置存储整形length变量
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

}//namespace ordered_string

namespace linked_string{
struct StringNode{
    char ch;//这里是一个字符，为提高存储利用率，可以char ch[4]
    StringNode *next;
};
}//namespace linked_string
}  // namespace string