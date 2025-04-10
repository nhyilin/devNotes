﻿//
// Created by 裴奕霖 on 2023/2/21.
//

#include <iostream>
#include <fstream>
#include "Utils.h"
#include "Config.h"

#if defined(WIN64) || defined(_WIN64) || defined(WIN32) || defined(_WIN32)
#include <direct.h>
#else

#include <unistd.h>

#endif

vector<double> Utils::getFileData(const string &filename, const std::string &file_type) {
    vector<double> res;
    int iter;
    if (file_type == "Test")
        iter = 2;
    else if (file_type == "Train")
        iter = 3;
    else std::cerr << "please check the file type given to function getFileData";

    std::ifstream in(filename);
    if (in.is_open()) {
        while (!in.eof()) {
            double val;
            in >> val;
            res.push_back(val);
        }
        in.close();
    } else {
        // Data file not found
        printf("[ERROR] '%s' not found.\n", filename.c_str());
        // Prompt the correct storage path of data file
        char path[256];
        getcwd(path, sizeof(path));
        printf("Please check the path '%s' is relative to '%s'.\n", filename.c_str(), path);
        exit(1);
    }

    for (auto it = res.begin(); it != res.end();) {
        it = res.erase(it); // erase the time element
        if (it != res.end()) {
            it += iter;
        }
    }
    return res;
}

vector<Sample> Utils::getTrainData(const string &filename) {
    vector<Sample> trainDataSet;

    vector<double> buffer = getFileData(filename, "Train");

    for (size_t i = 0; i < buffer.size(); i += Config::INNODE + Config::OUTNODE) {
        Sample trainSample;
        // Read in training sample 'feature'
        for (size_t j = 0; j < Config::INNODE; ++j)
            trainSample.feature.push_back(buffer[i + j]);
        // Read in training sample 'label'
        for (size_t k = 0; k < Config::OUTNODE; ++k)
            trainSample.label.push_back(buffer[i + Config::INNODE + k]);
        // Add samples to the 'trainDataSet'
        trainDataSet.push_back(trainSample);
    }
    return trainDataSet;
}

vector<Sample> Utils::getTestData(const string &filename) {
    vector<Sample> testDataSet;
    vector<double> buffer = getFileData(filename, "Test");

    for (size_t i = 0; i < buffer.size(); i += Config::INNODE) {
        Sample testSample;
        // Read in test sample 'feature'
        for (size_t j = 0; j < Config::INNODE; ++j)
            testSample.feature.push_back(buffer[i + j]);
        // Add samples to the 'testDataSet'
        testDataSet.push_back(testSample);
    }
    return testDataSet;
}

