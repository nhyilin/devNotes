// macroApp.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>

// 定义常量#define
// 定义简单函数 #define
// 定义预处理代码块#ifdef..#else if ... #else ...#endif
// 定义成员函数或特定函数


#define Reg_Set(name,type) \
void Set##name(type value) \
{\
	m_##name = value;\
}


#define Reg_Get(name,type) \
type Get##name()\
{\
	return m_##name;\
}

#define Reg_Callback(EventType) \
void CallBack(EventType,...) \
{\
}

#define Reg_Callback(EventType1,EventType2) \
void CallBack(EventType1,...) \
{\
}

#define Reg_Callback(EventType1,EventType2,EventType3) \
void CallBack(EventType1,...) \
{\
}

enum MyEnum1
{

};


enum MyEnum2
{

};


enum MyEnum3
{

};

class BaseClass1 {
public :
	Reg_Callback(MyEnum1 type);
	Reg_Callback(MyEnum1 type, MyEnum2 type2);
	Reg_Callback(MyEnum1 type, MyEnum2 type2, MyEnum3 type3);
};




class Test {
public:
	Reg_Set(Age, int);
	Reg_Get(Age, int);

	Reg_Set(name, std::string);
	Reg_Get(name, std::string);


private:
	int m_Age;
	std::string m_name;

};

int main()
{
	Test test;
	test.SetAge(20);
	std::cout << test.GetAge() << std::endl;

	test.Setname("ZXZ");
	std::cout << test.Getname() << std::endl;

    std::cout << "Hello World!\n";

	getchar();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
