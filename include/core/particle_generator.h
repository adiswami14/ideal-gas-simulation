#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;
using std::vector;

class ParticleGenerator {
public:
    ParticleGenerator();

    void GenerateParticle(const vec2& pos, const vec2& vel);

    vector<Particle> GetParticleList() const;

    void SetParticleList(const vector<Particle>& particle_list);
private:
    vector<Particle> particle_list_;
};

} //namespace idealgas

