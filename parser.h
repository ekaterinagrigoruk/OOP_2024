#pragma once
#include <vector>
#include "subtitle.h"

class ParserSRTSubtitles final {
public:
    ParserSRTSubtitles() = delete;
    static std::vector<Subtitle> parse(const std::string& filename);
private:
    static std::pair<int, int> parse_time_line(const std::string& line);
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