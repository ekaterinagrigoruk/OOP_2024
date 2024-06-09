#include <gtest/gtest.h>
#include <opencv2/opencv.hpp>
#include "graph.h"
#include "creater_graph.h"

TEST(ImageGraphBuilderTest, BuildImageGraph) {
    cv::Mat image = (cv::Mat_<uchar>(3, 3) << 0, 1, 2, 3, 4, 5, 6, 7, 8);
    Graph graph = ImageGraphBuilder::build_image_graph(image);
    const auto& adj_table = graph.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 9);

    Vertex v0(0, 0, 0);
    Vertex v1(1, 0, 1);
    Vertex v2(2, 0, 2);
    Vertex v3(0, 1, 3);
    Vertex v4(1, 1, 4);
    Vertex v5(2, 1, 5);
    Vertex v6(0, 2, 6);
    Vertex v7(1, 2, 7);
    Vertex v8(2, 2, 8);

    EXPECT_EQ(adj_table.at(v0).size(), 2); // (0,1) and (1,0)
    EXPECT_EQ(adj_table.at(v1).size(), 3); // (0,0), (2,0), (1,1)
    EXPECT_EQ(adj_table.at(v4).size(), 4); // (1,0), (1,2), (0,1), (2,1)
}