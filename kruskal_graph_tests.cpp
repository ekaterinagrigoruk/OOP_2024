#include <gtest/gtest.h>
#include "graph.h"
#include "kruskal_graph.h"

TEST(ImageGraphKruskalMSTTest, BuildMST) {
    Vertex v1(0, 0, 1.0);
    Vertex v2(1, 0, 2.0);
    Vertex v3(0, 1, 3.0);
    Vertex v4(1, 1, 4.0);

    Graph graph;
    graph.add_edge(Edge(v1, v2));
    graph.add_edge(Edge(v1, v3));
    graph.add_edge(Edge(v2, v4));
    graph.add_edge(Edge(v3, v4));

    Graph mst = ImageGraphKruskalMST::build_mst(graph);
    const auto& adj_table = mst.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 4);

    EXPECT_EQ(adj_table.at(v1).size(), 2);
    EXPECT_EQ(adj_table.at(v2).size(), 1);
    EXPECT_EQ(adj_table.at(v3).size(), 2);
    EXPECT_EQ(adj_table.at(v4).size(), 1);
}