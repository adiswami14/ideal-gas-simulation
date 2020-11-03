#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

class RedParticle : public Particle {
public:
    RedParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas
