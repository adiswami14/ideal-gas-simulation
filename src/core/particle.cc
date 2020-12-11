#include <core/particle.h>

namespace idealgas {

Particle::Particle(const vec2 &pos, const vec2 &vel) {
    position_ = pos;
    velocity_ = vel;
}

vec2 Particle::GetPosition() const {
    return position_;
}

vec2 Particle::GetVelocity() const {
    return velocity_;
}

void Particle::SetPosition(const vec2 &pos) {
    position_ = pos;
}

void Particle::SetVelocity(const vec2 &vel) {
    velocity_ = vel;
}

bool Particle::HasCollidedWith(const Particle &p) const {
    vec2 diff_position = position_ - p.position_;
    vec2 diff_velocity = velocity_ - p.velocity_;
    double dot = glm::dot(diff_position, diff_velocity);
    return (GetDistanceTo(p) <= (radius_+p.radius_) && dot <0);
}

double Particle::GetDistanceTo(const Particle &p) const {
    return sqrt(pow(position_.x - p.position_.x, 2) + pow(position_.y - p.position_.y, 2));
}

void Particle::ChangePostCollisionVelocity(const Particle &p) {
    double dot_product = glm::dot((velocity_-p.velocity_),(position_-p.position_));
    double squared_length = glm::pow(glm::length(position_ -p.position_), 2);
    if(squared_length == 0) { //this particle and p are at same position — this cannot happen
        return;
    }

    double curr_particle_factor = dot_product/squared_length;
    double mass_factor = ((double)(2*p.mass_))/(mass_+p.mass_);
    curr_particle_factor*=mass_factor;
    vec2 distance_between_particles = position_ - p.position_;
    distance_between_particles *= curr_particle_factor;
    velocity_ -= distance_between_particles;
}
}

