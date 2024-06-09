#include <gtest/gtest.h>
#include "vertex.h"

TEST(VertexTest, ConstructorAndAccessors) {
    Vertex v(10, 20, 255.0);
    EXPECT_EQ(v.get_x(), 10);
    EXPECT_EQ(v.get_y(), 20);
    EXPECT_DOUBLE_EQ(v.get_intensity(), 255.0);
}

TEST(VertexTest, EqualityOperator) {
    Vertex v1(10, 20, 255.0);
    Vertex v2(10, 20, 255.0);
    Vertex v3(15, 25, 128.0);

    EXPECT_TRUE(v1 == v2);
    EXPECT_FALSE(v1 == v3);
}

TEST(VertexTest, DefaultConstructor) {
    Vertex v{};
    EXPECT_EQ(v.get_x(), 0);
    EXPECT_EQ(v.get_y(), 0);
    EXPECT_DOUBLE_EQ(v.get_intensity(), 0.0);
}

/*int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}*/
