#include <gtest/gtest.h>
#include "parser.h"

TEST(ParserTest, ParseGraphFile) {
    std::string filename = "graph.txt";
    std::vector<Edge> expected_edges = {
            Edge(Vertex("A"), Vertex("B")),
            Edge(Vertex("A"), Vertex("C")),
            Edge(Vertex("B"), Vertex("D")),
            Edge(Vertex("C"), Vertex("D")),
            Edge(Vertex("C"), Vertex("E")),
            Edge(Vertex("D"), Vertex("F")),
            Edge(Vertex("E"), Vertex("F")),
            Edge(Vertex("F"), Vertex("G")),
            Edge(Vertex("G"), Vertex("H"))
    };

    std::vector<Edge> edges = Parser::parse(filename, " - ");

    EXPECT_EQ(edges, expected_edges);
}

TEST(ParserTest, ParseInvalidGraphFile) {
    std::string filename = "invalid_graph.txt";

    EXPECT_THROW(Parser::parse(filename, " - "), ParserErrors);
}

