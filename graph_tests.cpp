#include <gtest/gtest.h>
#include "graph.h"

TEST(GraphTest, AddEdge) {
Graph graph;
Vertex v1("V1");
Vertex v2("V2");
Edge edge(v1, v2);
graph.add_edge(edge);

const auto& adjacency_table = graph.get_adadjacency_table();

EXPECT_TRUE(adjacency_table.find(v1) != adjacency_table.end());
EXPECT_TRUE(adjacency_table.find(v2) != adjacency_table.end());

EXPECT_EQ(adjacency_table.at(v1).size(), 1);
EXPECT_EQ(adjacency_table.at(v2).size(), 1);

EXPECT_EQ(*adjacency_table.at(v1).begin(), edge);
EXPECT_EQ(*adjacency_table.at(v2).begin(), edge);
}

TEST(GraphTest, AddDuplicateEdge) {
    Graph graph;
    Vertex v1("V1");
    Vertex v2("V2");
    Edge edge(v1, v2);

    graph.add_edge(edge);
    graph.add_edge(edge);

    const auto& adjacency_table = graph.get_adadjacency_table();

    EXPECT_TRUE(adjacency_table.find(v1) != adjacency_table.end());

    EXPECT_EQ(adjacency_table.at(v1).size(), 1);
    EXPECT_EQ(adjacency_table.at(v2).size(), 1);

    EXPECT_EQ(*adjacency_table.at(v1).begin(), edge);
    EXPECT_EQ(*adjacency_table.at(v2).begin(), edge);
}