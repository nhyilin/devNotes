#include <iostream>
#include<string>

class Example
{
public:
    Example() {
        std::cout << "default function" << std::endl;
    }
    Example(int x) {
        std::cout << "define with " << x << std::endl;
    }
};

class Entity
{
private:
    std::string m_Name;
    Example m_Example;//调用了默认构造
public:
    const std::string& GetName()const { return m_Name; }
    Entity()
        :m_Name("Unknown"), m_Example(8)//或者
    {
    }

    Entity(const std::string& name)
        :m_Name(name)
    {
    }
};

int main()
{
    Entity e0;

    std::cin.get();
    return 0;
}



