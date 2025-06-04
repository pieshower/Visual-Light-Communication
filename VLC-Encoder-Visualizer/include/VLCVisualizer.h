#ifndef VLCVISUALIZER_H
#define VLCVISUALIZER_H

#include <iostream>

class VLCVisualizer {
private:
    static VLCVisualizer sVLCVisualizer_;

    int windowSize_;
    int symbolDurationMs_;

public:
    static VLCVisualizer& getVLCVisualizer() { return sVLCVisualizer_; }

     VLCVisualizer(int windowSize = 500, int symbolDurationMs = 50);
    ~VLCVisualizer() {}

    void play(const std::string& bitstream);
};

inline VLCVisualizer VLCVisualizer::sVLCVisualizer_;

#endif