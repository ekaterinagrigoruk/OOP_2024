#pragma once
#include <map>
#include <vector>
#include <string>

class Histogram final {
public:
    explicit Histogram(const std::vector<std::pair<double, double>>& book) {
        for (const auto& element : book) {
            add_element(element);
        }
    }
    [[nodiscard]] std::map<const std::string, double> get_histogram() const{
        return vocabulary;
    }

private:
    std::map<const std::string, double> vocabulary;
    void add_element(const std::pair<double, double>& element);
    static std::string get_range(const double& speed);
};
