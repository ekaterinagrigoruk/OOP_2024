#pragma once
#include <stack>
#include <opencv2/opencv.hpp>
#include "kruskal_graph.h"
#include "mincut_graph.h"
#include "creater_graph.h"

class SegmentImage final {
public:
    SegmentImage() = delete;
    static cv::Mat segment(const cv::Mat& image, int num_segments);

private:
    static void flood_fill(const Graph& graph, const Vertex& start_vertex, int component,
                    std::unordered_map<Vertex, int, Graph::vertex_hash>& component_map);
};


