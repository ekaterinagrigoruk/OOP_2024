#include <gtest/gtest.h>
#include "subtitle.h"

TEST(SubtitleTest, Constructor) {
    Subtitle subtitle("Hello, World!", 1000, 2000);

    EXPECT_EQ(subtitle.get_text(), "Hello, World!");
    EXPECT_EQ(subtitle.get_startTime(), 1000);
    EXPECT_EQ(subtitle.get_endTime(), 2000);
}

TEST(SubtitleTest, GetText) {
    Subtitle subtitle("Hello, World!", 500, 1500);

    EXPECT_EQ(subtitle.get_text(), "Hello, World!");
}

TEST(SubtitleTest, GetStartTime) {
    Subtitle subtitle("Hello, World!", 200, 1500);

    EXPECT_EQ(subtitle.get_startTime(), 200);
}

TEST(SubtitleTest, GetEndTime) {
    Subtitle subtitle("Hello, World!", 200, 1500);

    EXPECT_EQ(subtitle.get_endTime(), 1500);
}

/*int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
