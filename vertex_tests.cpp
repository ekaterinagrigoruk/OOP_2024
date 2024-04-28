#include <gtest/gtest.h>
#include "vertex.h"

TEST(VertexTest, DefaultConstructor) {
Vertex vertex;
EXPECT_EQ(vertex.get_name(), "");
}

TEST(VertexTest, Name) {
Vertex vertex1("V1");
Vertex vertex2("V2");
Vertex vertex3("V1");

EXPECT_FALSE(vertex1 != vertex3);
EXPECT_TRUE(vertex1 != vertex2);
}

TEST(VertexTest, GetName) {
Vertex vertex("Test");
const std::string& name_ref = vertex.get_name();
EXPECT_EQ(&name_ref, &vertex.get_name());
}
