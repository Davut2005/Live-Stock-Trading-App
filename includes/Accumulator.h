#pragma once
#include <vector>
#include <stdexcept>

// TEMPLATE CLASS with meaning:
// Used to accumulate numeric values (prices, quantities, values)
template<typename T>
class Accumulator {
    std::vector<T> values;

public:
    void add(T value) {
        values.push_back(value);
    }

    T sum() const {
        if (values.empty())
            throw std::runtime_error("No values to accumulate");

        T result{};
        for (const auto& v : values)
            result += v;
        return result;
    }

    T max() const {
        if (values.empty())
            throw std::runtime_error("No values to accumulate");

        T m = values[0];
        for (const auto& v : values)
            if (v > m)
                m = v;
        return m;
    }
};

// TEMPLATE FUNCTION with meaning:
// Used to clamp numeric values (prices, quantities, percentages)
template<typename T>
T clampValue(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
