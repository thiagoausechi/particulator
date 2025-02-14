#ifndef UTILS_H
#define UTILS_H

#include <random>

inline int randomInRange(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

#endif //UTILS_H
