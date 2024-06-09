#pragma once
#include "vertex.h"

class Edge final {
public:
    Edge(const Vertex& v1, const Vertex& v2) : v1(v1), v2(v2) {
        weight = abs(v1.get_intensity() - v2.get_intensity());
    }
    [[nodiscard]] Vertex get_v1() const{
        return v1;
    }
    [[nodiscard]] Vertex get_v2() const{
        return v2;
    }
    [[nodiscard]] double get_weight() const{
        return weight;
    }
    bool operator==(const Edge& other_edge) const {
        return  (v1 == other_edge.v1 && v2 == other_edge.v2 ||
                v1 == other_edge.v2 && v2 == other_edge.v1) ;
    }
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
private:
    Vertex v1;
    Vertex v2;
    double weight;
};
