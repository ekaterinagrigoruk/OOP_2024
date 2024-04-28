#pragma once
#include <vector>
#include <sstream>
#include <string>
#include "edge.h"

class Parser final {
public:
    Parser() = delete;
    static std::vector<Edge> parse(const std::string& filename, const std::string& delimiter);
private:
    static std::vector<std::string> parse_line(std::string& line, const std::string& delimiter);
};

class ParserErrors: public std::exception {
public:
    explicit ParserErrors(std::string  message): message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};