#include <core/particle_manager.h>
#include <core/red_particle.h>
#include <core/blue_particle.h>
#include <core/white_particle.h>

namespace idealgas {

ParticleManager::ParticleManager() {}

void ParticleManager::GenerateParticle(const vec2& pos, const vec2& vel, std::string particle_type) {
    if(particle_type == "red") {
        RedParticle red_particle(pos, vel);
        particle_list_.push_back(red_particle);
    } else if(particle_type == "blue") {
        BlueParticle blue_particle(pos, vel);
        particle_list_.push_back(blue_particle);
    } else {
        WhiteParticle white_particle(pos, vel);
        particle_list_.push_back(white_particle);
    }
}

void ParticleManager::SetBox(const Box &box) {
    box_ = box;
}

vector<Particle> ParticleManager::GetParticleList() const {
    return particle_list_;
}

void ParticleManager::UpdateParticles() {
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

void ParticleManager::ChangeVelocities(double factor) {
    if(factor<0) {
        return;
    }
    for(Particle &p: particle_list_) {
        vec2 vel = p.GetVelocity();
        vel*=factor;
        p.SetVelocity(vel);
    }
}

void ParticleManager::CheckCollisions(Particle &p, size_t curr_index, const vec2 &p_position, vec2 &p_velocity) {
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

void ParticleManager::CheckBounds(const Particle &p, vec2 &p_velocity) {
    if(box_.IsAtXBoundary(p)) {
        p_velocity.x*=-1;
    }
    if(box_.IsAtYBoundary(p)) {
        p_velocity.y*=-1;
    }
}
} //namespace idealgas

