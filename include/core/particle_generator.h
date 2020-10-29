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
        bool HasCollidedWith(const Particle& p, size_t particle_radius) {
            double particle_distance = sqrt(pow(position.x - p.position.x, 2) + pow(position.y - p.position.y, 2));
            return (particle_distance <= 2*particle_radius);
        }
    };

    ParticleGenerator();

    void GenerateParticle(const vec2& pos, const vec2& vel);

    vector<Particle> GetParticleList() const;

    void SetParticleList(const vector<Particle>& particle_list);
private:
    vector<Particle> particle_list_;
};

} //namespace idealgas

