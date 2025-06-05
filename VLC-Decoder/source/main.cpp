#include "../include/VLCDecoder.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./VLC-Decode path_to_video" << std::endl;
        return -1;
    }

    int error = VLCDecoder::getVLCDecoder().readVideo(argv[1]);

    if (error < 0) {
        std::cerr << "Exiting!" << std::endl;
        return -1;
    }
}