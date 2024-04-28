#include <iostream>
#include <fstream>
#include <queue>
#include "graph.h"
#include "parser.h"

class Traversal final {
private:
    Graph graph;
public:
    void fill_graph (const std::vector<Edge>& edges);
    std::vector<Vertex> find_way(const Vertex& start, const Vertex& end);
};
