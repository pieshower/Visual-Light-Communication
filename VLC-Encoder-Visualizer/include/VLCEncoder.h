#ifndef VLCENCODER_H
#define VLCENCODER_H

#include <iostream>
#include <fstream>
#include <string>

#include <opencv4/opencv2/opencv.hpp>

class VLCEncoder {
private:
    static VLCEncoder sVLCEncoder_;

    cv::Mat image;
    
    std::string imageToBinary(const cv::Mat& img, int threshold = 128);
    std::string manchesterEncode(const std::string& binaryInput);
    
public:
    static VLCEncoder& getVLCEncoder() { return sVLCEncoder_; }

     VLCEncoder() = default;
    ~VLCEncoder() = default;
    
    int readImage(const std::string& path_to_file);
    std::string encodeImage();
};

inline VLCEncoder VLCEncoder::sVLCEncoder_;

#endif