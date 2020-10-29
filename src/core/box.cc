#include <core/box.h>

namespace idealgas {

Box::Box() {}

Box::Box(const vec2 &top_left_corner, size_t box_size, size_t particle_radius)
: top_left_corner_(top_left_corner), box_size_(box_size), particle_radius_(particle_radius){
    InitializeBounds();
}

glm::vec2 Box::GetTopLeftCorner() const {
    return top_left_corner_;
}

size_t Box::GetBoxSize() const {
    return box_size_;
}

bool Box::IsAtXBoundary(const Particle& p) const {
    for(double x_pos : x_boundary_positions_) {
        double x_diff = p.GetPosition().x - x_pos;
        double x_velocity_component = p.GetVelocity().x;
        double multiplier = x_diff * x_velocity_component;
        if(multiplier<0) {
            if (abs(p.GetPosition().x - x_pos) <= particle_radius_) {
                return true;
            }
        }
    }
    return false;
}

bool Box::IsAtYBoundary(const Particle &p) const {
    for(double y_pos : y_boundary_positions_) {
        double y_diff = p.GetPosition().y - y_pos;
        double y_velocity_component = p.GetVelocity().y;
        double multiplier = y_diff * y_velocity_component;
        if(multiplier<0) {
            if (abs(p.GetPosition().y - y_pos) <= particle_radius_) {
                return true;
            }
        }
    }
    return false;
}

void Box::InitializeBounds() {
    x_boundary_positions_.clear();
    y_boundary_positions_.clear();
    x_boundary_positions_.insert(top_left_corner_.x);
    x_boundary_positions_.insert(top_left_corner_.x + box_size_);
    y_boundary_positions_.insert(top_left_corner_.y);
    y_boundary_positions_.insert(top_left_corner_.y + box_size_);
}

} //namespace idealgas