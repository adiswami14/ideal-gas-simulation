#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

class WhiteParticle : public Particle {
public:
    WhiteParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas

