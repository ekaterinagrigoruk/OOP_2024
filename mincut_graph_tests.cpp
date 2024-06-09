#include <gtest/gtest.h>
#include "kruskal_graph.h"
#include "mincut_graph.h"

TEST(CutGraphTest, CutMSTIntoSegments) {
    Vertex v1(0, 0, 1.0);
    Vertex v2(1, 0, 2.0);
    Vertex v3(0, 1, 3.0);
    Vertex v4(1, 1, 4.0);
    Vertex v5(2, 0, 5.0);

    Graph graph;
    graph.add_edge(Edge(v1, v2));
    graph.add_edge(Edge(v3, v4));
    graph.add_edge(Edge(v4, v5));
    graph.add_edge(Edge(v2, v4));

    Graph mst = ImageGraphKruskalMST::build_mst(graph);
    Graph segmented_graph = CutGraph::cut(mst, 2);

    const auto& adj_table = segmented_graph.get_adjacency_table();
    EXPECT_EQ(adj_table.size(), 5);

    int edge_count = 0;
    for (const auto& pair : adj_table) {
        for (const auto& edge : pair.second) {
            edge_count++;
        }
    }
    edge_count /= 2;

    EXPECT_EQ(edge_count, 3);

    std::unordered_set<Edge, Graph::edge_hash> remaining_edges;
    for (const auto& pair : adj_table) {
        for (const auto& edge : pair.second) {
            remaining_edges.insert(edge);
        }
    }

    for (const auto& edge : remaining_edges) {
        EXPECT_EQ(edge.get_weight(), 1);
    }
}