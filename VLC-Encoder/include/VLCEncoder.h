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
    
    std::vector<uint8_t> imageToBinary(const cv::Mat& img, int threshold = 128);
    std::vector<uint8_t> manchesterEncode(const std::vector<uint8_t>& binaryStream);
    
public:
    static VLCEncoder& getVLCEncoder() { return sVLCEncoder_; }

     VLCEncoder() = default;
    ~VLCEncoder() = default;
    
    int readImage(const std::string& path_to_file);
    std::vector<uint8_t> encodeImage();
};

inline VLCEncoder VLCEncoder::sVLCEncoder_;

#endif