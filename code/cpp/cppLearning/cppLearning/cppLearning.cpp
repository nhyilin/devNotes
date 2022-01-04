#include <iostream>
#include<string>
#include <memory>

class Entity {
public:
    void Print()const { std::cout << "hello" << std::endl; }
};

class ScopedPtr {//ÖÇÄÜÖ¸ÕëÀà
private:
    Entity* m_Obj;
public:
    ScopedPtr(Entity*entity)
        : m_Obj(entity) {
    }

    ~ScopedPtr() {
        delete m_Obj;
    }

    Entity* operator->() {
        return m_Obj;
    }

    const Entity* operator->() const{
        return m_Obj;
    }

};


int main() {
    {
        const ScopedPtr entity = new Entity();
        entity->Print();
    }
    std::cin.get();
}



























