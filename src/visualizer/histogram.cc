#include <visualizer/histogram.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Histogram::Histogram() {

}

Histogram::Histogram(glm::vec2 bottom_left_corner, size_t histogram_size) :
bottom_left_corner_(bottom_left_corner),
histogram_size_(histogram_size){
    increment_factor_ = 0.5;
}

void Histogram::Update() {
    UpdateFrequencyMap();
}

void Histogram::Draw() {
    ci::gl::color(ci::Color("white"));
    vec2 x_axis_vec = bottom_left_corner_+vec2(histogram_size_, 0);
    vec2 y_axis_vec = bottom_left_corner_-vec2(0, histogram_size_);
    ci::gl::drawLine(bottom_left_corner_, x_axis_vec);
    ci::gl::drawLine(bottom_left_corner_, y_axis_vec);
    ci::gl::drawStringCentered("Speed", x_axis_vec+vec2(-20, 30));
    ci::gl::drawStringCentered("Frequency", y_axis_vec-vec2(40, -10));
    double max = std::max_element(frequency_map_.begin(), frequency_map_.end())->first;
    double min = std::min_element(frequency_map_.begin(), frequency_map_.end())->first;
    ci::gl::drawString(std::to_string(max), x_axis_vec+vec2(0, 10));
    ci::gl::drawString(std::to_string(min), bottom_left_corner_+vec2(0, 10));
    ci::gl::color(color_);
    CreateHistogram();
}

void Histogram::SetParticleVector(const vector<Particle> &particle_vec) {
    particle_vec_ = particle_vec;
}

void Histogram::SetColor(const ci::Color &color) {
    color_ = color;
}

void Histogram::UpdateFrequencyMap() {
    frequency_map_.clear();
    double mult_factor = 1/increment_factor_;
    for(Particle particle: particle_vec_) {
        double speed = glm::length(particle.GetVelocity());
        frequency_map_[round(mult_factor*speed)/mult_factor]++;
    }
}

void Histogram::CreateHistogram() {
    double width;

    if(frequency_map_.empty()) {
        width = 0.0;
    } else width = histogram_size_/frequency_map_.size();

    double height = 10.0;
    vec2 curr_vec = bottom_left_corner_;
    for(auto const &x: frequency_map_) {
        size_t num = frequency_map_[x.first];
        vec2 height_vec = curr_vec-vec2(0, num*height);
        curr_vec+=vec2(width, 0);
        ci::Rectf num_box(height_vec, curr_vec);
        ci::gl::drawSolidRect(num_box);
    }
}
}

}
