#pragma once
#include <unordered_map>
#include <vector>
#include <string>
#include <iterator>
#include <functional>

class HashFunction final{
public:
    std::size_t operator()(const std::string& s) const {
        std::size_t h = 0;
        for (char c : s) {
            h = h * 31 + c;
        }
        return h;
    }
};

class Histogram final {
public:
    Histogram() = default;
    void add_element(const std::pair<double, double>& element);

    using iterator = std::unordered_map<std::string, double>::const_iterator;

    iterator begin() const {
        return vocabulary.begin();
    }

    iterator end() const {
        return vocabulary.end();
    }

private:
    std::unordered_map<const std::string, double, HashFunction> vocabulary;
    static std::string get_range(double speed);
};
