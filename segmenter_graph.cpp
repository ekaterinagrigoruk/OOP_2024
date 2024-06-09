#include "segmenter_graph.h"

cv::Mat SegmentImage::segment(const cv::Mat &image, int num_segments) {
    Graph graph = ImageGraphBuilder::build_image_graph(image);
    Graph mst = ImageGraphKruskalMST::build_mst(graph);
    Graph segmented_graph = CutGraph::cut(mst, num_segments);

    std::unordered_map<Vertex, int, Graph::vertex_hash> component;
    int current_component = 0;

    for (const auto& pair : segmented_graph.get_adjacency_table()) {
        const Vertex& v = pair.first;
        if (component.find(v) == component.end()) {
            flood_fill(segmented_graph, v, current_component++, component);
        }
    }

    std::vector<cv::Vec3b> colors(current_component);
    std::srand(std::time(nullptr));
    for (int i = 0; i < current_component; ++i) {
        colors[i] = cv::Vec3b(std::rand() % 256, std::rand() % 256, std::rand() % 256); // Random color
    }

    cv::Mat result(image.rows, image.cols, CV_8UC3);
    for (const auto& pair : component) {
        const Vertex& v = pair.first;
        int x = v.get_x();
        int y = v.get_y();
        if (x >= 0 && x < image.cols && y >= 0 && y < image.rows) {
            result.at<cv::Vec3b>(y, x) = colors[pair.second];
        }
    }

    return result;
}

void SegmentImage::flood_fill(const Graph &graph, const Vertex &start_vertex, int component,
                              std::unordered_map<Vertex, int, Graph::vertex_hash> &component_map) {
    std::stack<Vertex> stack;
    stack.push(start_vertex);
    while (!stack.empty()) {
        Vertex v = stack.top();
        stack.pop();
        if (component_map.find(v) != component_map.end()) {
            continue;
        }
        component_map[v] = component;
        for (const auto& edge : graph.get_adjacency_table().at(v)) {
            Vertex neighbor = (edge.get_v1() == v) ? edge.get_v2() : edge.get_v1();
            if (component_map.find(neighbor) == component_map.end()) {
                stack.push(neighbor);
            }
        }
    }
}
