#pragma once
#include "graph.h"
#include <opencv2/opencv.hpp>
#include <utility>

class ImageGraphBuilder {
public:
    ImageGraphBuilder() = delete;
    static Graph build_image_graph(const cv::Mat& image);
};
