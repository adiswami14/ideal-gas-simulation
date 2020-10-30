#include <core/particle_generator.h>

namespace idealgas {

ParticleGenerator::ParticleGenerator() {}

void ParticleGenerator::GenerateParticle(const vec2& pos, const vec2& vel) {
    Particle particle(pos, vel);
    particle_list_.push_back(particle);
}

void ParticleGenerator::SetBox(const Box &box) {
    box_ = box;
}

void ParticleGenerator::SetParticleRadius(size_t radius_size) {
    particle_radius_ = radius_size;
}

void ParticleGenerator::UpdateParticles() {
    for(size_t index = 0; index < particle_list_.size(); index++) {
        Particle p = particle_list_.at(index);
        vec2 curr_particle_position = p.GetPosition();
        vec2 curr_particle_velocity = p.GetVelocity();

        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidCircle(curr_particle_position, particle_radius_);

        CheckCollisions(p, index, curr_particle_position, curr_particle_velocity);
        CheckBounds(p, curr_particle_velocity);

        curr_particle_position += curr_particle_velocity;
        p.SetPosition(curr_particle_position);
        p.SetVelocity(curr_particle_velocity);
        particle_list_.at(index) = p;
    }
}

void ParticleGenerator::CheckCollisions(Particle &p, size_t curr_index,  const vec2 &p_position, vec2 &p_velocity) {
    for(size_t index = 0; index < particle_list_.size(); index++) {
        if(index != curr_index) {
            Particle particle = particle_list_.at(index);
            if (p.HasCollidedWith(particle, particle_radius_)) {
                p.ChangePostCollisionVelocity(particle);
                particle.ChangePostCollisionVelocity(p);
                p_velocity = p.GetVelocity();
                particle_list_.at(index).SetVelocity(particle.GetVelocity());
            }
        }
    }
}

void ParticleGenerator::CheckBounds(const Particle &p, vec2 &p_velocity) {
    if(box_.IsAtXBoundary(p)) {
        p_velocity.x*=-1;
    }
    if(box_.IsAtYBoundary(p)) {
        p_velocity.y*=-1;
    }
}
} //namespace idealgas

