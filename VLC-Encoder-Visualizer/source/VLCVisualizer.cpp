#include "../include/VLCVisualizer.h"

#include <opencv4/opencv2/opencv.hpp>
#include <thread>
#include <chrono>

VLCVisualizer::VLCVisualizer(int windowSize, int symbolDurationMs) {
    windowSize_ = windowSize;
    symbolDurationMs_ = symbolDurationMs_;
}

void VLCVisualizer::play(const std::string& bitstream) {
    cv::namedWindow("VLC Visualizer", cv::WINDOW_NORMAL);
    cv::resizeWindow("VLC Visualizer", windowSize_, windowSize_);

    // std::cout << "Econded String Size: " << bitstream.size() << std::endl;
    // std::cout << "Image Encoded String: " << std::endl;
    // for (size_t i = 0; i < bitstream.size(); ++i) {
    //     std::cout << bitstream[i];
    //     if ((i + 1) % 128 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    for (char bit : bitstream) {
        cv::Mat frame;
        if (bit == '1') {
            frame = cv::Mat::ones(windowSize_, windowSize_, CV_8UC1) * 255;  // White
        } else {
            frame = cv::Mat::zeros(windowSize_, windowSize_, CV_8UC1);  // Black
        }
        cv::imshow("VLC Visualizer", frame);
        cv::pollKey();

        std::this_thread::sleep_for(std::chrono::milliseconds(symbolDurationMs_));
    }

    cv::destroyWindow("VLC Visualizer");
}