#include <core/particle_generator.h>
#include <core/red_particle.h>
#include <core/blue_particle.h>

namespace idealgas {

ParticleGenerator::ParticleGenerator() {}

void ParticleGenerator::GenerateParticle(const vec2& pos, const vec2& vel, bool is_red_particle) {
    if(is_red_particle) {
        RedParticle red_particle(pos, vel);
        particle_list_.push_back(red_particle);
    } else  {
        BlueParticle blue_particle(pos, vel);
        particle_list_.push_back(blue_particle);
    }
}

void ParticleGenerator::SetBox(const Box &box) {
    box_ = box;
}

void ParticleGenerator::SetParticleRadius(size_t radius_size) {
    particle_radius_ = radius_size;
}

size_t ParticleGenerator::GetParticleRadius() const {
    return particle_radius_;
}

vector<Particle> ParticleGenerator::GetParticleList() const {
    return particle_list_;
}

void ParticleGenerator::UpdateParticles() {
    for(size_t index = 0; index < particle_list_.size(); index++) {
        Particle p = particle_list_.at(index);
        vec2 curr_particle_position = p.GetPosition(); //update velocities and positions and set them at the end
        vec2 curr_particle_velocity = p.GetVelocity();

        CheckCollisions(p, index, curr_particle_position, curr_particle_velocity);
        CheckBounds(p, curr_particle_velocity);

        curr_particle_position += curr_particle_velocity;
        p.SetPosition(curr_particle_position);
        p.SetVelocity(curr_particle_velocity);
        particle_list_.at(index) = p;
    }
}

void ParticleGenerator::CheckCollisions(Particle &p, size_t curr_index,  const vec2 &p_position, vec2 &p_velocity) {
    for(size_t index = 0; index < particle_list_.size(); index++) { //re-iterate through particle list
        if(index != curr_index) {
            Particle particle = particle_list_.at(index);
            Particle placeholder = p; //temporary particle to avoid messing up post-collision velocity values
            if (p.HasCollidedWith(particle)) {
                p.ChangePostCollisionVelocity(particle);
                particle.ChangePostCollisionVelocity(placeholder);
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

