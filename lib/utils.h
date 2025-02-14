#ifndef UTILS_H
#define UTILS_H

#include <random>

inline int randomInRange(const int min, const int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

template<typename T>
T choose(std::vector<T> array, std::vector<int> weights) {
    if (array.size() != weights.size())
        throw std::runtime_error("Array and weights must be the same length");

    const auto sum = std::accumulate(weights.begin(), weights.end(), 0);
    const auto randomNumber = randomInRange(0, sum);
    int threshold = 0;

    for (int i = 0; i < array.size(); ++i) {
        threshold += weights[i];
        if (threshold >= randomNumber)
            return array[i];
    }

    throw std::runtime_error("Something went wrong");
}

#endif //UTILS_H
