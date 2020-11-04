#include <core/white_particle.h>

namespace idealgas{

WhiteParticle::WhiteParticle(const vec2 &pos, const vec2 &vel) : Particle(pos, vel) {
    mass_ = 10;
    radius_ = 7;
}

}

