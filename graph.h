#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "vertex.h"
#include "edge.h"

class Graph final {
public:
    struct vertex_hash {
        size_t operator() (const Vertex& key) const {
            return std::hash<std::string>()(key.get_name());
        }
    };
    struct edge_hash {
        size_t operator() (const Edge& key) const {
            return std::hash<std::string>()(key.get_v1().get_name()) * std::hash<std::string>()(key.get_v2().get_name());
        }
    };
private:
    std::unordered_map<Vertex, std::unordered_set<Edge, edge_hash>, vertex_hash> adjacency_table;
public:
    void add_edge(const Edge& edge);

    const std::unordered_map<Vertex, std::unordered_set<Edge, edge_hash>, vertex_hash>& get_adadjacency_table() const {
        return adjacency_table;
    }
};
