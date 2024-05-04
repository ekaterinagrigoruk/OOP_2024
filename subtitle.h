#pragma once
#include <string>
#include <utility>

class Subtitle final {
private:
    std::string text;
    int startTime;
    int endTime;
public:
    Subtitle(std::string text_, int startTime_, int endTime_) : text(std::move(text_)), startTime(startTime_), endTime(endTime_) {}
    [[nodiscard]] int get_startTime() const {
        return startTime;
    }
    [[nodiscard]] int get_endTime() const {
        return endTime;
    }
    [[nodiscard]] const std::string& get_text() const {
        return text;
    }
};