#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size)
: top_left_corner_(top_left_corner),
  box_size_(box_size) {
    Box box(top_left_corner_, box_size_);
    box_ = box;
    vec2 test_pos(64.3, 912.4);
}

void Simulator::Draw() const {
 vec2 bottom_right_corner = top_left_corner_+vec2(box_size_, box_size_);
 ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
 ci::gl::color(ci::Color("black"));
 ci::gl::drawSolidRect(pixel_bounding_box);
 ci::gl::color(ci::Color("grey"));
 ci::gl::drawStrokedRect(pixel_bounding_box);
}

} //namespace visualizer

} //namespace idealgas

