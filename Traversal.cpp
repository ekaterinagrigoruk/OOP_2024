#include <algorithm>
#include "Traversal.h"

void Traversal::fill_graph(const std::vector<Edge>& edges) {
    for (const auto& edge : edges) {
        graph.add_edge(edge);
    }
}


std::vector<Vertex> Traversal::find_way(const Vertex& start, const Vertex& end) {
    std::unordered_map<Vertex, Vertex, Graph::vertex_hash> parent_map;
    std::queue<Vertex> queue;
    queue.push(start);

    while (!queue.empty()) {
        Vertex current = queue.front();
        queue.pop();

        if (current == end) {
            std::vector<Vertex> path;
            while (current != start) {
                path.emplace_back(current);
                current = parent_map.at(current);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (const Edge& edge : graph.get_adadjacency_table().at(current)) {
            const Vertex& next_vertex = (edge.get_v1() == current) ? edge.get_v2() : edge.get_v1();
            if (parent_map.find(next_vertex) == parent_map.end()) {
                parent_map[next_vertex] = current;
                queue.push(next_vertex);
            }
        }
    }

    return {};
}