//
// Created by 裴奕霖 on 2022/6/2.
//
#pragma once

#include <iostream>
#include <vector>
#include "Student.h"

class DataManager {
public:
    // 获取单实例对象
    static DataManager *&GetInstance();
    
    //释放单实例，进程退出时调用
    static void deleteInstance();
    
    void generate(int num);
    
    void getPersons(std::vector<Student> &person);

private:
    // 将其构造和析构成为私有的, 禁止外部构造和析构
    DataManager();
    
    ~DataManager();
    
    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    DataManager(const DataManager &signal);
    
    const DataManager &operator=(const DataManager &signal);
//    void checkoutConfiect();

private:
    // 唯一单实例对象指针
    static DataManager *m_SingleInstance;
    static std::mutex m_Mutex;
    std::vector<Student> person;
};



