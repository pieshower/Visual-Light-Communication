#include "../include/VLCVisualizer.h"

#include <opencv4/opencv2/opencv.hpp>
#include <thread>
#include <chrono>

VLCVisualizer::VLCVisualizer(int windowSize, int symbolDurationMs) {
    windowSize_ = windowSize;
    symbolDurationMs_ = symbolDurationMs;
}

void VLCVisualizer::sendDataPAK(const std::vector<uint8_t>& bitStream) {
    size_t totalBits = bitStream.size();
    size_t frameSize = 64 * 64;
    size_t numFrames = (totalBits + frameSize - 1) / frameSize;

    auto start = std::chrono::steady_clock::now();

    for (size_t frameIdx = 0; frameIdx < numFrames; ++frameIdx) {
        cv::Mat frame(64, 64, CV_8UC1, cv::Scalar(0));

        for (size_t i = 0; i < frameSize; ++i) {
            size_t bitIndex = frameIdx * frameSize + i;
            int row = i / 64;
            int col = i % 64;

            if (bitIndex < totalBits) {
                if (bitStream[bitIndex] == 1) {
                    frame.at<uchar>(row, col) = 255; // white
                }
                else {
                    frame.at<uchar>(row, col) = 0; // black
                }
            } else {
                frame.at<uchar>(row, col) = 0; // padding
            }
        }

        cv::imshow("VLC Visualizer", frame);
        cv::pollKey();

        auto next_frame_time = start + std::chrono::milliseconds(symbolDurationMs_ * (frameIdx + 1));
        std::this_thread::sleep_until(next_frame_time);
    }
}

void VLCVisualizer::sendDataOOK(const std::vector<uint8_t>& bitStream) {
    auto start = std::chrono::steady_clock::now();

    for (size_t i = 0; i < bitStream.size(); ++i) {
        uint8_t bit = bitStream[i];
        cv::Mat frame;

        if (bit == 1) {
            frame = cv::Mat::ones(windowSize_, windowSize_, CV_8UC1) * 255;  // White
        } else {
            frame = cv::Mat::zeros(windowSize_, windowSize_, CV_8UC1);  // Black
        }
        
        cv::imshow("VLC Visualizer", frame);
        cv::pollKey();

        auto next_frame_time = start + std::chrono::milliseconds(symbolDurationMs_ * (i + 1));
        std::this_thread::sleep_until(next_frame_time);
    }
}

void VLCVisualizer::play(const std::vector<uint8_t>& bitStream) {
    cv::namedWindow("VLC Visualizer", cv::WINDOW_NORMAL);
    cv::resizeWindow("VLC Visualizer", windowSize_, windowSize_);

    // sendDataPAK(bitStream);
    sendDataOOK(bitStream);

    cv::destroyWindow("VLC Visualizer");
}