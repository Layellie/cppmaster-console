#pragma once

#include <random>

struct ParameterDomain {
    int min;
    int max;

    [[nodiscard]] int draw(std::mt19937_64& randomEngine) const {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(randomEngine);
    }

    [[nodiscard]] ParameterDomain expanded() const {
        const int span = max - min;
        const int growth = span > 0 ? span : 1;
        return ParameterDomain{min - growth, max + growth};
    }
};
