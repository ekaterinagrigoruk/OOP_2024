#pragma once
#include <string>
#include <utility>

class Vertex final {
public:
    Vertex() = default;
    explicit Vertex(std::string  name) : name(std::move(name)) {};
    [[nodiscard]] const std::string& get_name() const {
        return name;
    }
    bool operator==(const Vertex& vertex) const = default;
private:
    std::string name;
};
