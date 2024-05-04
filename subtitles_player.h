#pragma once
#include <algorithm>
#include <fstream>
#include <memory>
#include <set>
#include <iomanip>
#include "parser.h"
#include "command.h"

struct CompareCommandPtr {
    bool operator()(const std::unique_ptr<Command>& lhs, const std::unique_ptr<Command>& rhs) const {
        return lhs->get_time() < rhs->get_time();
    }
};


class SubtitlesPlayer final {
public:
    SubtitlesPlayer() = delete;

    static std::set<std::unique_ptr<Command>, CompareCommandPtr> generate_commands(const std::vector<Subtitle>& subtitles);
    static void write_commands_to_file(const std::string& filename, const std::set<std::unique_ptr<Command>, CompareCommandPtr>& commands);
};

class PlayerErrors: public std::exception {
public:
    explicit PlayerErrors(std::string  message): message{std::move(message)} {}
    [[nodiscard]] const char* what() const noexcept override {
        return message.c_str();
    }
private:
    std::string message;
};