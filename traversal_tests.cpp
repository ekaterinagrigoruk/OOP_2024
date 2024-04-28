#include <gtest/gtest.h>
#include "Traversal.h"

TEST(TraversalTest, FillGraph) {
    Traversal traversal;
    std::vector<Edge> edges = {
            Edge(Vertex("A"), Vertex("B")),
            Edge(Vertex("B"), Vertex("C")),
            Edge(Vertex("C"), Vertex("D"))
    };
    EXPECT_NO_THROW(traversal.fill_graph(edges));
}

TEST(TraversalTest, FindWayAF) {
    Traversal traversal;
    std::vector<Edge> edges = {
            Edge(Vertex("A"), Vertex("B")),
            Edge(Vertex("B"), Vertex("C")),
            Edge(Vertex("C"), Vertex("D")),
            Edge(Vertex("D"), Vertex("E")),
            Edge(Vertex("E"), Vertex("F"))
    };
    traversal.fill_graph(edges);
    std::vector<Vertex> path = traversal.find_way(Vertex("A"), Vertex("F"));

    std::vector<Vertex> expected_path = {Vertex("A"), Vertex("B"), Vertex("C"), Vertex("D"), Vertex("E"), Vertex("F")};
    EXPECT_EQ(path, expected_path);
}

TEST(TraversalTest, FindWayBH) {
    Traversal traversal;
    std::vector<Edge> edges = {
            Edge(Vertex("A"), Vertex("B")),
            Edge(Vertex("B"), Vertex("D")),
            Edge(Vertex("D"), Vertex("F")),
            Edge(Vertex("F"), Vertex("G")),
            Edge(Vertex("G"), Vertex("H"))
    };
    traversal.fill_graph(edges);
    std::vector<Vertex> path = traversal.find_way(Vertex("B"), Vertex("H"));

    std::vector<Vertex> expected_path = {Vertex("B"), Vertex("D"), Vertex("F"), Vertex("G"), Vertex("H")};
    EXPECT_EQ(path, expected_path);
}

TEST(TraversalTest, FindWayCE) {
    Traversal traversal;
    std::vector<Edge> edges = {
            Edge(Vertex("A"), Vertex("C")),
            Edge(Vertex("C"), Vertex("E"))
    };
    traversal.fill_graph(edges);
    std::vector<Vertex> path = traversal.find_way(Vertex("C"), Vertex("E"));

    std::vector<Vertex> expected_path = {Vertex("C"), Vertex("E")};
    EXPECT_EQ(path, expected_path);
}

TEST(TraversalTest, FindWayDG) {
    Traversal traversal;
    std::vector<Edge> edges = {
            Edge(Vertex("A"), Vertex("B")),
            Edge(Vertex("B"), Vertex("D")),
            Edge(Vertex("D"), Vertex("G"))
    };
    traversal.fill_graph(edges);
    std::vector<Vertex> path = traversal.find_way(Vertex("D"), Vertex("G"));

    std::vector<Vertex> expected_path = {Vertex("D"), Vertex("G")};
    EXPECT_EQ(path, expected_path);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}