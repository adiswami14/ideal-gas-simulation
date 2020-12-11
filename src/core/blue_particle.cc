#include <core/blue_particle.h>

namespace idealgas{

BlueParticle::BlueParticle(const vec2 &pos, const vec2 &vel) : Particle(pos, vel) {
    mass_ = 5;
    radius_ = 4;
}

}