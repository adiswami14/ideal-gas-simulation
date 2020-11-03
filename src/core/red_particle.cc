#include <core/red_particle.h>

namespace idealgas {

RedParticle::RedParticle(const vec2 &pos, const vec2 &vel) : Particle(pos, vel) {
    mass_ = 2;
    radius_ = 2;
}

}