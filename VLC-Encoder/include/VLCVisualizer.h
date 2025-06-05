#ifndef VLCVISUALIZER_H
#define VLCVISUALIZER_H

#include <iostream>
#include <cstdint> 
#include <vector>

class VLCVisualizer {
private:
    static VLCVisualizer sVLCVisualizer_;

    int windowSize_;
    int symbolDurationMs_;

public:
    static VLCVisualizer& getVLCVisualizer() { return sVLCVisualizer_; }

     VLCVisualizer(int windowSize = 256, int symbolDurationMs = 50);
    ~VLCVisualizer() = default;

    void play(const std::vector<uint8_t>& bitstream);
};

inline VLCVisualizer VLCVisualizer::sVLCVisualizer_;

#endif