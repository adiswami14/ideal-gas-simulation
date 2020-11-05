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

void Histogram::Draw() {
    ci::gl::color(ci::Color("white"));
    vec2 x_axis_vec = bottom_left_corner_+vec2(histogram_size_, 0);
    vec2 y_axis_vec = bottom_left_corner_-vec2(0, histogram_size_);
    ci::gl::drawLine(bottom_left_corner_, x_axis_vec);
    ci::gl::drawLine(bottom_left_corner_, y_axis_vec);
    ci::gl::drawStringCentered("Speed", x_axis_vec+vec2(-20, 10));
    ci::gl::drawStringCentered("Frequency", y_axis_vec-vec2(40, -10));
    UpdateFrequencyMap();
    CreateHistogram();
}

void Histogram::SetParticleVector(const vector<Particle> &particle_vec) {
    particle_vec_ = particle_vec;
}

void Histogram::UpdateFrequencyMap() {
    frequency_map_.clear();
    for(Particle particle: particle_vec_) {
        double speed = glm::length(particle.GetVelocity());
        frequency_map_[round(2*speed)/2.0]++;
    }
}

void Histogram::CreateHistogram() {
    double width = histogram_size_/20;
    double height = 10.0;
    vec2 curr_vec = bottom_left_corner_;
    for(double x = 0; x<10.0; x+=0.5) {
        size_t num = frequency_map_[x];
        vec2 height_vec = curr_vec-vec2(0, num*height);
        curr_vec+=vec2(width, 0);
        ci::Rectf num_box(height_vec, curr_vec);
        ci::gl::drawSolidRect(num_box);
    }
}

}

}
