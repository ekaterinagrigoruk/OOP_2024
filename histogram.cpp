#include "histogram.h"

void Histogram::add_element(const std::pair<double, double>& element) {
    const std::string range = get_range(element.second);
    vocabulary[range] += element.first;
}

std::string Histogram::get_range(double speed) {
    int min = static_cast<int>(speed / 2) * 2;
    int max = min + 2;
    return std::to_string(min) + "-" + std::to_string(max);
}
