#include "gtest/gtest.h"
#include "histogram.h"

TEST(HistogramTest, Constructor1) {
    std::vector<std::pair<double, double>> book = {
            {10.0, 5.0},
            {20.0, 7.0},
            {30.0, 9.0},
            {40.0, 11.0}
    };

    Histogram histogram(book);
    auto histogram_data = histogram.get_histogram();

    EXPECT_EQ(histogram_data["4-6"], 10.0);
    EXPECT_EQ(histogram_data["8-10"], 30.0);
    EXPECT_EQ(histogram_data["10-12"], 40.0);
}

TEST(HistogramTest, Constructor2) {
    std::vector<std::pair<double, double>> data = {
            {15.0, 4.0},
            {25.0, 8.0},
            {35.0, 10.0},
            {45.0, 12.0}
    };
    Histogram histogram(data);
    auto histogram_data = histogram.get_histogram();

    EXPECT_EQ(histogram_data["12-14"], 45.0);
    EXPECT_EQ(histogram_data["4-6"], 15.0);
    EXPECT_EQ(histogram_data["8-10"], 25.0);
    EXPECT_EQ(histogram_data["10-12"], 35.0);
}


TEST(HistogramTest, HistogramEmptyData) {
    std::vector<std::pair<double, double>> data;
    Histogram histogram(data);
    auto histogram_data = histogram.get_histogram();

    EXPECT_TRUE(histogram_data.empty());
}
