#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;
using std::vector;

class ParticleGenerator {
public:
    struct Particle {
    public:
        vec2 position;
        vec2 velocity;
    };

    ParticleGenerator();

    void GenerateParticle(const vec2& pos, const vec2& vel);

    vector<Particle> GetParticleList() const;
private:
    vector<Particle> particle_list_;
};

} //namespace idealgas

