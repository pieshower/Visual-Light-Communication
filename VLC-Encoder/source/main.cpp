#include "../include/VLCEncoder.h"
#include "../include/VLCVisualizer.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: ./VLC-Encode path_to_image" << std::endl;
        return -1;
    }

    int error = VLCEncoder::getVLCEncoder().readImage(argv[1]);

    if (error < 0) {
        std::cerr << "Exiting!" << std::endl;
        return -1;
    }

    std::vector<uint8_t> encodedStream = VLCEncoder::getVLCEncoder().encodeImage();
    VLCVisualizer::getVLCVisualizer().play(encodedStream);

    std::cout << "Finished!" << std::endl;

    return 0;
}