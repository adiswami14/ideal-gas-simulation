#pragma once

#include <core/box.h>
#include <core/particle_generator.h>
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

class Simulator {
public:
    Simulator(const glm::vec2& top_left_corner, size_t box_size);

    void Draw() const;

    ParticleGenerator GetParticleGenerator() const;

    void SetParticleGenerator(const ParticleGenerator& particle_generator);
private:
    glm::vec2 top_left_corner_;
    size_t box_size_;
    Box box_;
    ParticleGenerator particle_generator_;
};

} //namespace visualizer

} //namespace idealgas
