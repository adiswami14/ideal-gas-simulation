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

bool Particle::HasCollidedWith(const Particle &p, size_t particle_radius) const {
    return (GetDistanceTo(p) <= 2*particle_radius);
}

double Particle::GetDistanceTo(const Particle &p) const {
    return sqrt(pow(position_.x - p.position_.x, 2) + pow(position_.y - p.position_.y, 2));
}

bool Particle::operator==(const Particle &p) const {
    return (position_ == p.position_ && velocity_ == p.velocity_);
}

void Particle::ChangePostCollisionVelocity(const Particle &p) {
    double dot_product = glm::dot((velocity_-p.velocity_),(position_-p.position_));
    double squared_length = glm::pow(glm::length(position_ -p.position_), 2);
    double curr_particle_factor = dot_product/squared_length;
    vec2 distance_between_particles = position_ - p.position_;
    distance_between_particles *= curr_particle_factor;
    velocity_ -= distance_between_particles;
}
}

