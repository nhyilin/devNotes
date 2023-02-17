//
// Created by 裴奕霖 on 2023/2/16.
//

#ifndef CHARTTHEMES_DATAMANAGER_H
#define CHARTTHEMES_DATAMANAGER_H


#include <QPointF>
#include <QVector>
#include <iostream>
#include <fstream>

class DataManager {
public:
    static DataManager *instance() {
        static DataManager instance;
        return &instance;
    }

    void loadData(const std::string &fileName);

    void processData();

    const QVector<QPointF> &getData() const;

    const QVector<QPointF> &getResult() const;

    void generateRandomPoints();

private:
    DataManager() {}

    DataManager(const DataManager &) = delete;

    DataManager &operator=(const DataManager &) = delete;

    QVector<QPointF> m_data;
    QVector<QPointF> m_result;
};


#endif //CHARTTHEMES_DATAMANAGER_H
