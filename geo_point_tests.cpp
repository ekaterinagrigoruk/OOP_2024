#include <gtest/gtest.h>
#include "geo_point.h"

TEST(GeoPointTest, DefaultConstructor) {
    GeoPoint point;
    EXPECT_EQ(point.get_latitude(), 0);
    EXPECT_EQ(point.get_longitude(), 0);
    EXPECT_EQ(point.get_elevation(), 0);
    EXPECT_EQ(point.get_time(), 0);
}

TEST(GeoPointTest, Constructor) {
    GeoPoint point(40.7128, -74.0060, 10, 1620403200);
    EXPECT_EQ(point.get_latitude(), 40.7128);
    EXPECT_EQ(point.get_longitude(), -74.0060);
    EXPECT_EQ(point.get_elevation(), 10);
    EXPECT_EQ(point.get_time(), 1620403200);
}

TEST(GeoPointTest, Distance) {
    GeoPoint point1(40.7128, -74.0060, 0);
    GeoPoint point2(34.0522, -118.2437, 0);
    double distance = point1.distance(point2);
    EXPECT_NEAR(distance, 3930, 10);
}

TEST(GeoPointTest, ComparisonOperator) {
    GeoPoint point1(40.7128, -74.0060, 0, 1620403200);
    GeoPoint point2(34.0522, -118.2437, 0, 1620500000);
    EXPECT_TRUE(point1 < point2);
    EXPECT_FALSE(point2 < point1);
}

/*
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
