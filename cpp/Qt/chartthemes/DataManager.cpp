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

void DataManager::generateRandomPoints() {
    std::ofstream outFile("random_numbers.txt ");
    if (!outFile.is_open()) {
        std::cerr << "Failed to open output file." << std::endl;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(999.9, 1000.0);

    for (int i = 0; i < 500; i++) {
        double randomNum = dis(gen);
        outFile << std::fixed << std::setprecision(1) << randomNum << std::endl;
    }

    outFile.close();
}

const QVector<QPointF> &DataManager::getData() const {
    return m_data;
}

const QVector<QPointF> &DataManager::getResult() const {
    return m_result;
}