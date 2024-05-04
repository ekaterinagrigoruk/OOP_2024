#include <fstream>
#include <sstream>
#include "parser.h"

std::pair<int, int> ParserSRTSubtitles::parse_time_line(const std::string& line) {
    int start_time, end_time;
    int startTimeH, startTimeM, startTimeS, startTimeMs, endTimeH, endTimeM, endTimeS, endTimeMs;
    char arrow, colon;

    std::istringstream iss(line);
    iss >> startTimeH >> colon >> startTimeM >> colon >> startTimeS >> colon >> startTimeMs >> arrow >> arrow >> arrow
        >> endTimeH >> colon >> endTimeM >> colon >> endTimeS >> colon >> endTimeMs;

    start_time = startTimeH * 3600000 + startTimeM * 60000 + startTimeS * 1000 + startTimeMs;
    end_time = endTimeH * 3600000 + endTimeM * 60000 + endTimeS * 1000 + endTimeMs;

    return {start_time, end_time};
}

std::vector<Subtitle> ParserSRTSubtitles::parse(const std::string& filename) {
    std::vector<Subtitle> subtitles;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ParserErrors("File doesn't open");
    }
    std::string line;
    while (std::getline(file, line)) {
        int number;
        if (std::istringstream(line) >> number) {
            std::getline(file, line);

            auto [start_time, end_time] = parse_time_line(line);

            std::string subtitleText;
            while (std::getline(file, line) && !line.empty()) {
                subtitleText += line + "\n";
            }
            if (!subtitleText.empty()) {
                subtitleText.pop_back();
            }

            subtitles.emplace_back(subtitleText, start_time, end_time);
        }
    }
    file.close();
    return subtitles;
}
