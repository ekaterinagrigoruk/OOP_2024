#include "subtitles_player.h"

std::set<std::unique_ptr<Command>, CompareCommandPtr> SubtitlesPlayer::generate_commands(const std::vector<Subtitle>& subtitles) {
    std::set<std::unique_ptr<Command>, CompareCommandPtr> commands;
    for (const auto& subtitle : subtitles) {
        commands.emplace(std::make_unique<ShowCommand>(subtitle, subtitle.get_startTime()));
        commands.emplace(std::make_unique<HideCommand>(subtitle, subtitle.get_endTime()));
    }
    return commands;
}

void SubtitlesPlayer::write_commands_to_file(const std::string& filename, const std::set<std::unique_ptr<Command>, CompareCommandPtr>& commands) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw PlayerErrors("Failed to open file for writing: " + filename);
    }

    for (const auto& command : commands) {
        int time_ms = command->get_time();
        int hours = time_ms / 3600000;
        int minutes = (time_ms % 3600000) / 60000;
        int seconds = (time_ms % 60000) / 1000;
        int milliseconds = time_ms % 1000;

        file << "at " << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2) << std::setfill('0') << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
        if (milliseconds > 0) {
            file << "," << std::setw(3) << std::setfill('0') << milliseconds;
        }
        file << " ";

        std::string commandType = command->get_command_type_str();
        file << commandType << command->get_subtitle().get_text() << "'\n";
    }

    file.close();
}