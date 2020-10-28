#include <core/box.h>

namespace idealgas {

Box::Box() {}

Box::Box(const vec2 &top_left_corner, size_t box_size) : top_left_corner_(top_left_corner), box_size_(box_size){
    InitializeBounds();
}

glm::vec2 Box::GetTopLeftCorner() const {
    return top_left_corner_;
}

size_t Box::GetBoxSize() const {
    return box_size_;
}

bool Box::IsAtXBoundary(const vec2 &position) const {
    return (std::find(x_boundary_positions_.begin(), x_boundary_positions_.end(), position.x)
            != x_boundary_positions_.end());
}

bool Box::IsAtYBoundary(const vec2 &position) const {
    return (std::find(y_boundary_positions_.begin(), y_boundary_positions_.end(), position.y)
            != y_boundary_positions_.end());
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