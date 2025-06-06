#include "../include/VLCEncoder.h"
#include "../include/VLCVisualizer.h"

uint8_t VLCEncoder::option = 0; 

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Usage: ./VLC-Encode -option file_path/string" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "-i for image" << std::endl << "-s for string" << std::endl;
        return -1;
    }

    if (std::string(argv[1]) == "-i") {
        std::cout << "Encoding image..." << std::endl;
        VLCEncoder::option = 1;
    }
    else if (std::string(argv[1]) == "-s") {
        std::cout << "Encoding string..." << std::endl;
        VLCEncoder::option = 2;
    }

    int error = VLCEncoder::getVLCEncoder().readInput(std::string(argv[2]));

    if (error < 0) {
        std::cerr << "Exiting!" << std::endl;
        return -1;
    }

    std::vector<uint8_t> encodedStream = VLCEncoder::getVLCEncoder().encode();
    VLCVisualizer::getVLCVisualizer().play(encodedStream);

    std::cout << "Finished!" << std::endl;

    return 0;
}