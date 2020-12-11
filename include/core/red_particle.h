#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

/**
 * An instance of small-sized particle of red color, subclass of Particle
 */
class RedParticle : public Particle {
public:
    /**
     * Constructor of RedParticle class
     * @param pos Position vector of current particle
     * @param vel Velocity vector of current particle
     */
    RedParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas
