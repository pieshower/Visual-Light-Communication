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

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < bitstream.size(); ++i) {
        char bit = bitstream[i];
        cv::Mat frame;
        if (bit == '1') {
            frame = cv::Mat::ones(windowSize_, windowSize_, CV_8UC1) * 255;  // White
        } else {
            frame = cv::Mat::zeros(windowSize_, windowSize_, CV_8UC1);  // Black
        }
        cv::imshow("VLC Visualizer", frame);
        cv::pollKey();

        auto next_frame_time = start + std::chrono::milliseconds(symbolDurationMs_ * (i + 1));
        std::this_thread::sleep_until(next_frame_time);
    }

    cv::destroyWindow("VLC Visualizer");
}