#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

class Simulator {
public:
    Simulator(const glm::vec2& top_left_corner, size_t box_size);

    void Draw() const;

private:
    glm::vec2 top_left_corner_;
    size_t box_size_;
};

} //namespace visualizer

} //namespace idealgas
