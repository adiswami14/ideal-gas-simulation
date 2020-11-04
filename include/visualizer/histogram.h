#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::map;
using std::vector;

class Histogram {
public:
    Histogram();

    Histogram(glm::vec2 bottom_left_corner, size_t histogram_size);

    void Draw() const;
private:
    glm::vec2 bottom_left_corner_;
    //map<double, size_t> frequency_map_;
    size_t histogram_size_;
};

} //namespace visualizer

} //namespace idealgas
