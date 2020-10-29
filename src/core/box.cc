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

bool Box::IsAtXBoundary(const vec2 &position) const {
    for(double x_pos : x_boundary_positions_) {
        if (abs(position.x - x_pos)<=particle_radius_) {
            return true;
        }
    }
    return false;
}

bool Box::IsAtYBoundary(const vec2 &position) const {
    for(double y_pos : y_boundary_positions_) {
        if (abs(position.y - y_pos)<=particle_radius_) {
            return true;
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