#include "../include/VLCEncoder.h"

std::vector<uint8_t> VLCEncoder::imageToBinary(const cv::Mat& img, int threshold) {
    std::vector<uint8_t> binaryStream;

    for (int i = 0; i < img.rows; ++i) {
        for (int j = 0; j < img.cols; ++j) {
            uchar pixel = img.at<uchar>(i, j);
            if (pixel > threshold) {
                binaryStream.push_back(1);
            } else {
                binaryStream.push_back(0);
            }
        }
    }

    std::cout << "Image Binary Size: " << binaryStream.size() << std::endl;
    // std::cout << "Image Binary Stream: " << std::endl;
    // for (size_t i = 0; i < binaryStream.size(); ++i) {
    //     std::cout << (int)binaryStream[i];
    //     if ((i + 1) % 1024 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    return binaryStream;
}

std::vector<uint8_t> VLCEncoder::manchesterEncode(const std::vector<uint8_t>& binaryStream) {
    std::vector<uint8_t> encoded;

    for (size_t i = 0; i < binaryStream.size(); ++i) {
        uint8_t byte = binaryStream[i];
        
        if (byte == 1) {
            encoded.push_back(1);
            encoded.push_back(0);
        } else {
            encoded.push_back(0);
            encoded.push_back(1);
        }
    }

    std::cout << "Encoded Stream Size: " << encoded.size() << std::endl;
    // std::cout << "Encoded Stream: " << std::endl;
    // for (size_t i = 0; i < encoded.size(); ++i) {
    //     std::cout << (int)encoded[i];
    //     if ((i + 1) % 128 == 0) {
    //         std::cout << std::endl;
    //     }
    // }

    return encoded;
}

int VLCEncoder::readImage(const std::string& path_to_file) {
    image = cv::imread(path_to_file, cv::IMREAD_GRAYSCALE);

    if (image.empty()) {
        std::cerr << "File provided was empty..." << std::endl;
        return -1;
    }

    std::cout << std::to_string(image.rows) + " Rows and " + std::to_string(image.cols) + " Cols" << std::endl;

    // if (image.rows != 64 || image.cols != 64) {
    //     std::cerr << "File provided was not 64x64 pixels..." << std::endl;
    //     return -1;
    // }

    return 0;
}

std::vector<uint8_t> VLCEncoder::encodeImage() {
    std::vector<uint8_t> bitStream = imageToBinary(image);
    return manchesterEncode(bitStream);
}
