#ifndef VLCDECODER_H
#define VLCDECODER_H

#include <iostream>
#include <vector>

#include <opencv4/opencv2/opencv.hpp>

class VLCDecoder {
private:
    static VLCDecoder sVLCDecoder_;

    cv::VideoCapture video;

    std::vector<uint8_t> videoToBinary(cv::VideoCapture& video, int threshold = 128);
    std::vector<uint8_t> manchesterDecode(const std::vector<uint8_t>& bitStream);

public:
    static VLCDecoder& getVLCDecoder() { return sVLCDecoder_; }

     VLCDecoder() = default;
    ~VLCDecoder() = default;

    int readVideo(const std::string& path_to_file);
    std::vector<uint8_t> decodeVideo();
};

inline VLCDecoder VLCDecoder::sVLCDecoder_;

#endif