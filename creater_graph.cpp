#include "creater_graph.h"

Graph ImageGraphBuilder::build_image_graph(const cv::Mat& image) {
    Graph graph;
    for (int y = 0; y < image.rows; ++y) {
        for (int x = 0; x < image.cols; ++x) {
            Vertex v(x, y, image.at<uchar>(y, x));
            if (x > 0) {
                Vertex left(x - 1, y, image.at<uchar>(y, x - 1));
                graph.add_edge(Edge(v, left));
            }
            if (y > 0) {
                Vertex up(x, y - 1, image.at<uchar>(y - 1, x));
                graph.add_edge(Edge(v, up));
            }
        }
    }
    return graph;
}
