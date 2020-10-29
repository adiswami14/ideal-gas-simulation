#include <core/particle_generator.h>

namespace idealgas {

ParticleGenerator::ParticleGenerator() {}

void ParticleGenerator::GenerateParticle(const vec2& pos, const vec2& vel) {
    Particle particle = {pos, vel};
    particle_list_.push_back(particle);
}

vector<ParticleGenerator::Particle> ParticleGenerator::GetParticleList() const {
    return particle_list_;
}

void ParticleGenerator::SetParticleList(const vector<Particle> &particle_list) {
    particle_list_ = particle_list;
}
} //namespace idealgas

