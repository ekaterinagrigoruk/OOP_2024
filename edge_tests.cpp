#include <gtest/gtest.h>
#include "vertex.h"
#include "edge.h"

TEST(EdgeTest, ConstructorAndAccessors) {
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Edge e(v1, v2);

    EXPECT_EQ(e.get_v1(), v1);
    EXPECT_EQ(e.get_v2(), v2);
    EXPECT_DOUBLE_EQ(e.get_weight(), 50.0);
}

TEST(EdgeTest, EqualityOperator) {
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Vertex v3(20, 30, 200.0);

    Edge e1(v1, v2);
    Edge e2(v1, v2);
    Edge e3(v2, v1);
    Edge e4(v1, v3);

    EXPECT_TRUE(e1 == e2);
    EXPECT_TRUE(e1 == e3);
    EXPECT_FALSE(e1 == e4);
}

TEST(EdgeTest, LessThanOperator) {
    Vertex v1(10, 20, 100.0);
    Vertex v2(15, 25, 150.0);
    Vertex v3(20, 30, 200.0);

    Edge e1(v1, v2);
    Edge e2(v2, v3);

    EXPECT_FALSE(e1 < e2);
    EXPECT_FALSE(e2 < e1);
}