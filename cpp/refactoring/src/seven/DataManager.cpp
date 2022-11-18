//
// Created by 裴奕霖 on 2022/6/2.
//

#include "DataManager.h"
//初始化静态成员变量
DataManager *DataManager::m_SingleInstance = nullptr;
std::mutex DataManager::m_Mutex;

// 注意：返回的是指针的引用
DataManager *& DataManager::GetInstance()
{
    if (m_SingleInstance == nullptr)
    {
        std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
        if (m_SingleInstance == nullptr)
        {
            m_SingleInstance = new (std::nothrow) DataManager();
        }
    }
    
    return m_SingleInstance;
}

void DataManager::deleteInstance()
{
    std::unique_lock<std::mutex> lock(m_Mutex); // 加锁
    if (m_SingleInstance)
    {
        delete m_SingleInstance;
        m_SingleInstance = nullptr;
    }
}

DataManager::DataManager()
= default;

DataManager::~DataManager()
= default;

void DataManager::generate(int num){
    person.clear();
    for(int i=0;i<num;i++){
        Student s;
        s.id=i+1;
    person.push_back(s);
    }
}
