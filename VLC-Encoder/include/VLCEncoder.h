#ifndef VLCENCODER_H
#define VLCENCODER_H

#include <iostream>
#include <cstdint> 
#include <vector>

#include <opencv4/opencv2/opencv.hpp>

class VLCEncoder {
private:
    static VLCEncoder sVLCEncoder_;

    cv::Mat image;
    std::string str;

    int threshold = 128;
    
    std::vector<uint8_t> bytesToBits(const std::vector<uint8_t>& byteBuffer);

    std::vector<uint8_t> imageToBinary(const cv::Mat& img);
    std::vector<uint8_t> stringToBinary(const std::string& str);
    std::vector<uint8_t> manchesterEncode(const std::vector<uint8_t>& binaryStream);
    
public:
    static VLCEncoder& getVLCEncoder() { return sVLCEncoder_; }

     VLCEncoder() = default;
    ~VLCEncoder() = default;

    static uint8_t option;

    int readInput(const std::string& input);
    std::vector<uint8_t> encode();
};

inline VLCEncoder VLCEncoder::sVLCEncoder_;

#endif