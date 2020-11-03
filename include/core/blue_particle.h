#pragma once

#include "cinder/gl/gl.h"
#include <core/particle.h>

namespace idealgas {

class BlueParticle : public Particle {
public:
    BlueParticle(const vec2 &pos, const vec2 &vel);
};

} //namespace idealgas
