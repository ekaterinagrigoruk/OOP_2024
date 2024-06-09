#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "vertex.h"
#include "edge.h"

class Graph final {
public:
    struct vertex_hash {
        size_t operator() (const Vertex& key) const {
            return std::hash<double>()(key.get_intensity());
        }
    };
    struct edge_hash {
        size_t operator() (const Edge& key) const {
            return std::hash<double>()(key.get_v1().get_intensity()) * std::hash<double>()(key.get_v2().get_intensity());
        }
    };
    void add_edge(const Edge& edge){
        adjacency_table[edge.get_v1()].insert(edge);
        adjacency_table[edge.get_v2()].insert(edge);
    }
    void remove_edge(const Edge& edge) {
        adjacency_table[edge.get_v1()].erase(edge);
        adjacency_table[edge.get_v2()].erase(edge);
    }
    [[nodiscard]] const std::unordered_map<Vertex, std::unordered_set<Edge, edge_hash>, vertex_hash>& get_adjacency_table() const {
        return adjacency_table;
    }
private:
    std::unordered_map<Vertex, std::unordered_set<Edge, edge_hash>, vertex_hash> adjacency_table;
};