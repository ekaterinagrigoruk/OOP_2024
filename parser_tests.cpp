#include <gtest/gtest.h>
#include "parser.h"

TEST(ParserSRTSubtitlesTest, ParseSubtitlesFromFile) {
    std::vector<Subtitle> subtitles = ParserSRTSubtitles::parse("subtitles.txt");

    EXPECT_EQ(subtitles.size(), 8);

    EXPECT_EQ(subtitles[0].get_text(), "Раз\nдва\nтри");
    EXPECT_EQ(subtitles[0].get_startTime(), 1000);
    EXPECT_EQ(subtitles[0].get_endTime(), 5500);

    EXPECT_EQ(subtitles[1].get_text(), "четыре пять");
    EXPECT_EQ(subtitles[1].get_startTime(), 6000);
    EXPECT_EQ(subtitles[1].get_endTime(), 9500);
}

TEST(ParserSRTSubtitlesTest, ParseInvalidFile) {
    EXPECT_THROW({ ParserSRTSubtitles::parse("invalid_file.txt");}, ParserErrors);
}

