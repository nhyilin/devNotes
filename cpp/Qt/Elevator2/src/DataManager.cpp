//
// Created by 裴奕霖 on 2023/2/16.
//


#include <random>
#include <sstream>
#include <fstream>
#include "DataManager.h"

void DataManager::loadData(const std::string &fileName) {
    // 读取数据、存储数据

    std::ifstream inFile(fileName);
    std::vector<double> data;

    if (inFile.is_open()) {
        std::string line;
        while (std::getline(inFile, line)) {
            std::stringstream ss(line);
            double val;
            while (ss >> val) {
                data.push_back(val);
            }
        }
        inFile.close();
    }

//    return data;
}

void DataManager::processData() {
    // 计算数据、存储结果
}

void DataManager::getRandomPoints(std::string filename) {
    std::vector<double> data;
    std::ifstream file("/Users/peiyilin/dev/devNotes/cpp/Qt/chartthemes/bin/debug/Rador.txt");

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            double value = stod(line);
            data.push_back(value);
        }

        file.close();
        m_fake_data = data;
//        for (int i = 0; i < data.size(); i++)
//            std::cout << data[i] << std::endl;

    } else
        std::cout << "无法打开文件" << std::endl;

}

const std::vector<double> &DataManager::getFakeData() const {
    return m_fake_data;
}

const QVector<QPointF> &DataManager::getData() const {
    return m_data;
}

const QVector<QPointF> &DataManager::getResult() const {
    return m_result;
}