#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

/**
 * An instance of large-sized particle of white color, subclass of Particle
 */
class WhiteParticle : public Particle {
public:
    /**
     * Constructor of WhiteParticle class
     * @param pos Position vector of current Particle
     * @param vel Velocity vector of current Particle
     */
    WhiteParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas

