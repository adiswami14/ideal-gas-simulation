#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

/**
 * An instance of medium-sized particle of blue color, subclass of Particle
 */
class BlueParticle : public Particle {
public:
    /**
     * Constructor of BlueParticle class
     * @param pos Position vector of current particle
     * @param vel Velocity vector of current particle
     */
    BlueParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas
