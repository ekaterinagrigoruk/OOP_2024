#pragma once
#include <utility>
#include "vertex.h"

class Edge final {
public:
    Edge(Vertex  vertex1, Vertex  vertex2) : vertex1(std::move(vertex1)), vertex2(std::move(vertex2)) {};
    [[nodiscard]] const Vertex& get_v1() const {
        return vertex1;
    }
    [[nodiscard]] const Vertex& get_v2() const {
        return vertex2;
    }
    bool operator==(const Edge& other_edge) const {
        return  (vertex1 == other_edge.vertex1 && vertex2 == other_edge.vertex2 ||
                 vertex1 == other_edge.vertex2 && vertex2 == other_edge.vertex1) ;
    }
private:
    Vertex vertex1;
    Vertex vertex2;
};
