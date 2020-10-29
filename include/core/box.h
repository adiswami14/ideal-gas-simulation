#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

class Box {
public:
    Box();

    Box(const vec2& top_left_corner, size_t box_size, size_t particle_radius);

    vec2 GetTopLeftCorner() const;

    size_t GetBoxSize() const;

    bool IsAtXBoundary(const vec2& position) const;

    bool IsAtYBoundary(const vec2& position) const;

private:
    void InitializeBounds();
    std::set<double> x_boundary_positions_;
    std::set<double> y_boundary_positions_;
    vec2 top_left_corner_;
    size_t box_size_;
    size_t particle_radius_;
};

} //namespace idealgas
