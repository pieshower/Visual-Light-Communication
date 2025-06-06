#include "../include/VLCEncoder.h"

std::vector<uint8_t> VLCEncoder::bytesToBits(const std::vector<uint8_t>& byteBuffer) {
    std::vector<uint8_t> bitBuffer;
    bitBuffer.reserve(byteBuffer.size() * 8);

    for (size_t i = 0; i < byteBuffer.size(); ++i) {
        uint8_t byte = byteBuffer[i];
        
        for (int j = 7; j >= 0; --j) {  // MSB first
            uint8_t bit = (byte >> j) & 0x01;
            bitBuffer.push_back(bit);
        }
    }

    return bitBuffer;
}

std::vector<uint8_t> VLCEncoder::imageToBinary(const cv::Mat& img, int threshold) {
    std::vector<uint8_t> binaryStream;

    // for (int i = 0; i < img.rows; ++i) {
    //     for (int j = 0; j < img.cols; ++j) {
    //         uchar pixel = img.at<uchar>(i, j);
    //         if (pixel > threshold) {
    //             binaryStream.push_back(1);
    //         } else {
    //             binaryStream.push_back(0);
    //         }
    //     }
    // }

    // return binaryStream;
    
    cv::imencode(".jpg", img, binaryStream, {cv::IMWRITE_JPEG_QUALITY, 100});
    return bytesToBits(binaryStream);
}

std::vector<uint8_t> VLCEncoder::stringToBinary(const std::string& str) {
    std::vector<uint8_t> binaryStream(str.begin(), str.end());
    return bytesToBits(binaryStream);
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

    return encoded;
}

int VLCEncoder::readInput(const std::string& input) {
    switch (option) {
        case 1: {
            image = cv::imread(input, cv::IMREAD_GRAYSCALE);

            if (image.empty()) {
                std::cerr << "File provided was empty..." << std::endl;
                return -1;
            }
            break;
        }
        case 2: {
            str = input;
            break;
        }
        default: {
            std::cerr << "No input was given..." << std::endl;
            return -1;
        }
    }

    return 0;
}

std::vector<uint8_t> VLCEncoder::encode() {
    std::vector<uint8_t> binaryStream;
    
    switch (option) {
        case 1: {
            binaryStream = imageToBinary(image);
            break;
        }
        case 2: {
            binaryStream = stringToBinary(str);
            break;
        }
        default : {
            return binaryStream;
        }
    }

    return manchesterEncode(binaryStream);
}
