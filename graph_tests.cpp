#include <gtest/gtest.h>
#include "vertex.h"
#include "edge.h"
#include "graph.h"

TEST(GraphTest, AddEdge) {
    Graph g;
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Edge e(v1, v2);

    g.add_edge(e);

    const auto& adj_table = g.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 2);
    EXPECT_EQ(adj_table.at(v1).size(), 1);
    EXPECT_EQ(adj_table.at(v2).size(), 1);
    EXPECT_EQ(adj_table.at(v1).count(e), 1);
    EXPECT_EQ(adj_table.at(v2).count(e), 1);
}

TEST(GraphTest, RemoveEdge) {
    Graph g;
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Edge e(v1, v2);

    g.add_edge(e);
    g.remove_edge(e);

    const auto& adj_table = g.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 2);
    EXPECT_EQ(adj_table.at(v1).size(), 0);
    EXPECT_EQ(adj_table.at(v2).size(), 0);
}

TEST(GraphTest, GraphStructure) {
    Graph g;
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Vertex v3(20, 30, 200.0);
    Edge e1(v1, v2);
    Edge e2(v2, v3);

    g.add_edge(e1);
    g.add_edge(e2);

    const auto& adj_table = g.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 3);
    EXPECT_EQ(adj_table.at(v1).size(), 1);
    EXPECT_EQ(adj_table.at(v2).size(), 2);
    EXPECT_EQ(adj_table.at(v3).size(), 1);
    EXPECT_EQ(adj_table.at(v1).count(e1), 1);
    EXPECT_EQ(adj_table.at(v2).count(e1), 1);
    EXPECT_EQ(adj_table.at(v2).count(e2), 1);
    EXPECT_EQ(adj_table.at(v3).count(e2), 1);
}