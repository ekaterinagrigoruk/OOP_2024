#include "mincut_graph.h"

Graph CutGraph::cut(const Graph &mst, int num_segments) {
    std::vector<Edge> edges;
    for (const auto& pair : mst.get_adjacency_table()) {
        for (const auto& edge : pair.second) {
            if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
                edges.push_back(edge);
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.get_weight() > e2.get_weight();
    });

    Graph segmented_graph = mst;
    for (int i = 0; i < num_segments - 1 && i < edges.size(); ++i) {
        segmented_graph.remove_edge(edges[i]);
    }

    return segmented_graph;
}
