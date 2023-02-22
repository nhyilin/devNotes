//
// Created by 裴奕霖 on 2023/2/21.
//

#ifndef CHARTTHEMES_CONFIG_H
#define CHARTTHEMES_CONFIG_H



using std::size_t;

namespace Config {
    const size_t INNODE = 2;
    const size_t HIDENODE = 4;
    const size_t OUTNODE = 1;

    const double lr = 0.8;
    const double threshold = 1e-4;
    const size_t max_epoch = 1e6;
}

#endif //CHARTTHEMES_CONFIG_H
