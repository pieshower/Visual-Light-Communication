#include "../include/VLCVisualizer.h"

#include <opencv4/opencv2/opencv.hpp>
#include <thread>
#include <chrono>

VLCVisualizer::VLCVisualizer(int windowSize, int symbolDurationMs) {
    windowSize_ = windowSize;
    symbolDurationMs_ = symbolDurationMs;
}

void VLCVisualizer::play(const std::vector<uint8_t>& bitstream) {
    cv::namedWindow("VLC Visualizer", cv::WINDOW_NORMAL);
    cv::resizeWindow("VLC Visualizer", windowSize_, windowSize_);

    size_t totalBits = bitstream.size();
    size_t frameSize = 64 * 64;
    size_t numFrames = (totalBits + frameSize - 1) / frameSize;  // ceiling division

    auto start = std::chrono::steady_clock::now();

    for (size_t frameIdx = 0; frameIdx < numFrames; ++frameIdx) {
        cv::Mat image(64, 64, CV_8UC1, cv::Scalar(0));

        for (size_t i = 0; i < frameSize; ++i) {
            size_t bitIndex = frameIdx * frameSize + i;
            int row = i / 64;
            int col = i % 64;

            if (bitIndex < totalBits) {
                image.at<uchar>(row, col) = (bitstream[bitIndex] == 1) ? 255 : 0;
            } else {
                image.at<uchar>(row, col) = 0; // padding with black if stream runs out
            }
        }

        cv::Mat resized;
        cv::resize(image, resized, cv::Size(windowSize_, windowSize_), 0, 0, cv::INTER_NEAREST);
        cv::imshow("VLC Visualizer", resized);
        cv::pollKey();

        auto next_frame_time = start + std::chrono::milliseconds(symbolDurationMs_ * (frameIdx + 1));
        std::this_thread::sleep_until(next_frame_time);
    }

    cv::destroyWindow("VLC Visualizer");
}