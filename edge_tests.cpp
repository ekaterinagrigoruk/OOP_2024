#include <gtest/gtest.h>
#include "edge.h"

TEST(EdgeTest, Constructor) {
    Vertex v1("V1");
    Vertex v2("V2");
    Edge edge(v1, v2);
    EXPECT_EQ(edge.get_v1(), v1);
    EXPECT_EQ(edge.get_v2(), v2);
}

TEST(EdgeTest, EqualityOperator) {
    Vertex v1("V1");
    Vertex v2("V2");
    Edge edge1(v1, v2);
    Edge edge2(v1, v2);
    Edge edge3(v2, v1);

    EXPECT_TRUE(edge1 == edge2);
    EXPECT_TRUE(edge1 == edge3);
}

TEST(EdgeTest, InequalityOperator) {
    Vertex v1("V1");
    Vertex v2("V2");
    Vertex v3("V3");
    Edge edge1(v1, v2);
    Edge edge2(v1, v3);
    Edge edge3(v3, v1);

    EXPECT_TRUE(edge1 != edge2);
    EXPECT_TRUE(edge1 != edge3);
    EXPECT_TRUE(edge2 == edge3);
}
