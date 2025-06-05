#include "../include/VLCDecoder.h"

std::vector<uint8_t> VLCDecoder::videoToBinary(cv::VideoCapture& video, int threshold) {
    std::vector<uint8_t> bitStream;
    cv::Mat frame;

    for (int i = 0; i < static_cast<int>(video.get(cv::CAP_PROP_FRAME_COUNT)); ++i) {
        video >> frame;

        if (frame.empty()) break;
        
        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        double avgBrightness = cv::mean(frame)[0];
        
        if (avgBrightness > threshold) {
            bitStream.push_back(1);
        }
        else {
            bitStream.push_back(0);
        }
    }

    video.release();

    return bitStream;
}

std::vector<uint8_t> VLCDecoder::manchesterDecode(const std::vector<uint8_t>& bitStream) {
    std::vector<uint8_t> decoded;
    
    if (bitStream.size() % 2 != 0) {
        std::cerr << "Bit stream is not even!" << std::endl;
        return decoded;
    }

    for (size_t i = 0; i < bitStream.size(); i += 2) {
        uint8_t frst = bitStream[i];
        uint8_t scnd = bitStream[i + 1];

        if (frst == 1 && scnd == 0)
            decoded.push_back(1);
        else if (frst == 0 && scnd == 1)
            decoded.push_back(0);
        else {
            std::cerr << "Manchester decoding error at position " << i << ": invalid pair (" 
                      << (int)frst << "," << (int)scnd << ")" << std::endl;
            // optional: you can choose whether to push back some special error value
            // decoded.push_back(255); // 255 = error mark
        }
    }

    return decoded;
}

int VLCDecoder::readVideo(const std::string& path_to_file) {
    video = cv::VideoCapture(path_to_file);

    if (!video.isOpened()) {
        std::cerr << "Failed to open video..." << std::endl;
        return -1;
    }

    return 0;
}

std::vector<uint8_t> VLCDecoder::decodeVideo() {
    std::vector<uint8_t> bitStream = videoToBinary(video);
    return manchesterDecode(bitStream);
}