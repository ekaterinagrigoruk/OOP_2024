#pragma once
#include <utility>
#include "subtitle.h"

class Command {
public:
    virtual ~Command() = default;
    [[nodiscard]] virtual const Subtitle& get_subtitle() const = 0;
    [[nodiscard]] virtual int get_time() const = 0;
    [[nodiscard]] virtual std::string get_command_type_str() const = 0;
};

class HideCommand final : public Command {
public:
    HideCommand(Subtitle subtitle, int time) : subtitle(std::move(subtitle)), time(time) {}
    [[nodiscard]] const Subtitle& get_subtitle() const override { return subtitle; }
    [[nodiscard]] int get_time() const override { return time; }
    [[nodiscard]] std::string get_command_type_str() const override { return "hide '"; }
private:
    Subtitle subtitle;
    int time;
};

class ShowCommand final : public Command {
public:
    ShowCommand(Subtitle subtitle, int time) : subtitle(std::move(subtitle)), time(time) {}
    [[nodiscard]] const Subtitle& get_subtitle() const override { return subtitle; }
    [[nodiscard]] int get_time() const override { return time; }
    [[nodiscard]] std::string get_command_type_str() const override { return "show '"; }
private:
    Subtitle subtitle;
    int time;
};
