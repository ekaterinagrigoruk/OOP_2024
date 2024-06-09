#pragma once
#include <algorithm>
#include "graph.h"

class CutGraph final {
public:
    CutGraph() = delete;
    static Graph cut(const Graph& mst, int num_segments);
};
