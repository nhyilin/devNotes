//
// Created by 裴奕霖 on 2022/9/29.
//
namespace string {
#define MAXLEN 255
struct SString {
    char ch[MAXLEN];
    int length;
};
struct HString {
    char* ch;
    int length;
};

}  // namespace string