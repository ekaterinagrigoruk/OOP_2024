#pragma once
#include <algorithm>
#include "graph.h"

class ImageGraphKruskalMST final{
public:
    ImageGraphKruskalMST() = delete;
    static Graph build_mst(const Graph& graph);
};