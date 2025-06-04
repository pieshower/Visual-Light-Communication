#include "../include/VLCEncoder.h"

std::string VLCEncoder::imageToBinary(const cv::Mat& img, int threshold) {
    std::string binaryString;
    
    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            uchar pixel = img.at<uchar>(i, j);
            binaryString += (pixel > threshold) ? '1' : '0';
        }
    }

    // std::cout << "Image Binary String: " << std::endl;
    // for (size_t i = 0; i < binaryString.size(); ++i) {
    //     std::cout << binaryString[i];
    //     if ((i + 1) % 64 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    return binaryString;
}

std::string VLCEncoder::manchesterEncode(const std::string& binaryInput) {
    std::string encoded;

    for (char bit : binaryInput) {
        encoded += (bit == '1') ? "10" : "01";
    }

    return encoded;
}

int VLCEncoder::readImage(const std::string& path_to_file) {
    image = cv::imread(path_to_file, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "File provided was empty..." << std::endl;
        return -1;
    }

    if (image.rows != 64 || image.cols != 64) {
        std::cerr << "File provided was not 64x64 pixels..." << std::endl;
        return -1;
    }

    return 0;
}

std::string VLCEncoder::encodeImage() {
    std::string binaryStream = imageToBinary(image);
    return manchesterEncode(binaryStream);
}