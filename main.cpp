#include <iostream>
#include <vector>
#include "subtitle.h"
#include "command.h"
#include "subtitles_player.h"
#include "parser.h"

int main() {
    try {
        std::vector<Subtitle> subtitles = ParserSRTSubtitles::parse("subtitles.txt");
        std::set<std::unique_ptr<Command>, CompareCommandPtr> commands = SubtitlesPlayer::generate_commands(subtitles);
        SubtitlesPlayer::write_commands_to_file("output.txt", commands);

        std::cout << "Commands have been successfully written to output.txt." << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
