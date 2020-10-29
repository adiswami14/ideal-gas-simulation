#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

class Box {
public:
    Box();

    Box(const vec2& top_left_corner, size_t box_size, size_t particle_radius);

    vec2 GetTopLeftCorner() const;

    size_t GetBoxSize() const;

    bool IsAtXBoundary(const Particle &p) const;

    bool IsAtYBoundary(const Particle &p) const;

private:
    void InitializeBounds();
    std::vector<double> x_boundary_positions_;
    std::vector<double> y_boundary_positions_;
    vec2 top_left_corner_;
    size_t box_size_;
    size_t particle_radius_;
};

} //namespace idealgas
