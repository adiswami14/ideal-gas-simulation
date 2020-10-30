#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "box.h"

namespace idealgas {

using glm::vec2;
using std::vector;

class ParticleGenerator {
public:
    ParticleGenerator();

    void GenerateParticle(const vec2& pos, const vec2& vel);

    void SetBox(const Box& box);

    vector<Particle> GetParticleList() const;

    void UpdateParticles();

    void SetParticleRadius(size_t radius_size);

    size_t GetParticleRadius() const;
private:
    void CheckCollisions(Particle &p, size_t curr_index, const vec2 &p_position, vec2 &p_velocity);

    void CheckBounds(const Particle &p, vec2 &p_velocity);

    vector<Particle> particle_list_;
    Box box_;
    size_t particle_radius_;
};

} //namespace idealgas

