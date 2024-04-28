#include "graph.h"

void Graph::add_edge(const Edge& edge) {
    adjacency_table[edge.get_v1()].insert(edge);
    adjacency_table[edge.get_v2()].insert(edge);
}