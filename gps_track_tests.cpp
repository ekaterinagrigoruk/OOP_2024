#include <gtest/gtest.h>
#include "gps_track.h"

TEST(GPSTrackTest, ConstructorAndMethods) {
    std::vector<GeoPoint> points = {
            {0, 0, 0, 0},
            {10, 1, 1, 10},
            {20, 2, 2, 20},
            {30, 3, 3, 30},
            {40, 4, 4, 40}
    };

    GPS_track track(points);

    EXPECT_EQ(track.get_duration(), 40);
    EXPECT_NEAR(track.get_all_distance(), 4466, 1);
    EXPECT_NEAR(track.get_all_average_speed(), 4466.0 / 40.0, 1);

    EXPECT_EQ(track.get_movement_time(), 40);
    EXPECT_EQ(track.get_stop_time(), 0);

    EXPECT_NEAR(track.get_average_speed(), 4466.0 / 40.0, 1);
    EXPECT_NEAR(track.get_max_speed(), 111, 1);

    EXPECT_EQ(track.get_min_height(), 0);
    EXPECT_EQ(track.get_max_height(), 4);
}

TEST(GPSTrackTest, ConstructorAndMethods2) {
    std::vector<GeoPoint> points = {
            {0, 0, 0, 0},
            {10, 1, 1, 10},
            {20, 2, 2, 20},
            {20, 2, 2, 30},
            {40, 4, 4, 40}
    };

    GPS_track track(points);

    EXPECT_EQ(track.get_duration(), 40);
    EXPECT_NEAR(track.get_all_distance(), 4466, 1);
    EXPECT_NEAR(track.get_all_average_speed(), 4466.0 / 40.0, 1);

    EXPECT_EQ(track.get_movement_time(), 30);
    EXPECT_EQ(track.get_stop_time(), 10);

    EXPECT_NEAR(track.get_average_speed(), 4466.0 / 30.0, 1);
    EXPECT_NEAR(track.get_max_speed(), 223, 1);

    EXPECT_EQ(track.get_min_height(), 0);
    EXPECT_EQ(track.get_max_height(), 4);
}