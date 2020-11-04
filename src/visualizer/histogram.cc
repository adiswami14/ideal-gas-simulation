#include <visualizer/histogram.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Histogram::Histogram() {

}

Histogram::Histogram(glm::vec2 bottom_left_corner, size_t histogram_size) :
bottom_left_corner_(bottom_left_corner),
histogram_size_(histogram_size)
{}

void Histogram::Draw() const {
    ci::gl::color(ci::Color("white"));
    vec2 x_axis_vec = bottom_left_corner_+vec2(histogram_size_, 0);
    vec2 y_axis_vec = bottom_left_corner_-vec2(0, histogram_size_);
    ci::gl::drawLine(bottom_left_corner_, x_axis_vec);
    ci::gl::drawLine(bottom_left_corner_, y_axis_vec);
    ci::gl::drawStringCentered("Speed", x_axis_vec+vec2(-20, 10));
    ci::gl::drawStringCentered("Frequency", y_axis_vec-vec2(40, -10));
}

}

}
