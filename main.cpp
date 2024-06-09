#include <opencv2/opencv.hpp>
#include "segmenter_graph.h"

int main() {
    cv::Mat image = cv::imread("test.png", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Could not open or find the image" << std::endl;
        return -1;
    }

    int num_segments = 3;
    cv::Mat segmented_image = SegmentImage::segment(image, num_segments);

    cv::imshow("Segmented Image", segmented_image);
    if (!cv::imwrite("segmented_image.png", segmented_image)) {
        std::cerr << "Ошибка: не удалось сохранить изображение." << std::endl;
        return -1;
    }
    cv::waitKey(0);

    return 0;
}
