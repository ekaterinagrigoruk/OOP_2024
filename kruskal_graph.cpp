#include "kruskal_graph.h"
#include <vector>
#include <functional>

Graph ImageGraphKruskalMST::build_mst(const Graph &graph) {
    Graph mst;
    std::vector<Edge> edges;
    for (const auto& pair : graph.get_adjacency_table()) {
        for (const auto& edge : pair.second) {
            if (std::find(edges.begin(), edges.end(), edge) == edges.end()) {
                edges.push_back(edge);
            }
        }
    }

    std::sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1 < e2;
    });

    std::unordered_map<Vertex, Vertex, Graph::vertex_hash> parent;
    for (const auto& pair : graph.get_adjacency_table()) {
        parent[pair.first] = pair.first;
    }

    std::function<Vertex(const Vertex&)> find = [&parent, &find](const Vertex& vertex) -> Vertex {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }
        return parent[vertex];
    };

    auto unite = [&parent, &find](const Vertex& v1, const Vertex& v2) {
        Vertex root1 = find(v1);
        Vertex root2 = find(v2);
        if (root1 != root2) {
            parent[root2] = root1;
        }
    };

    for (const auto& edge : edges) {
        Vertex v1 = edge.get_v1();
        Vertex v2 = edge.get_v2();

        if (find(v1) != find(v2)) {
            mst.add_edge(edge);
            unite(v1, v2);
        }
    }

    return mst;
}

