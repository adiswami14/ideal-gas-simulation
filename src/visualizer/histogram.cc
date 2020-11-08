#include <visualizer/histogram.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Histogram::Histogram() {

}

Histogram::Histogram(const glm::vec2 &bottom_left_corner, size_t histogram_size, const ci::Color &color, double rounding_factor) :
bottom_left_corner_(bottom_left_corner),
histogram_size_(histogram_size),
color_(color),
rounding_factor_(rounding_factor){}

void Histogram::Draw() {
    //draw x and y axis
    ci::gl::color(ci::Color("white"));
    vec2 x_axis_vec = bottom_left_corner_+vec2(histogram_size_, 0);
    vec2 y_axis_vec = bottom_left_corner_-vec2(0, histogram_size_);
    ci::gl::drawLine(bottom_left_corner_, x_axis_vec);
    ci::gl::drawLine(bottom_left_corner_, y_axis_vec);

    ci::gl::drawStringCentered("Speed", x_axis_vec+vec2(-20, 30));
    ci::gl::drawStringCentered("Frequency", y_axis_vec-vec2(40, -10));

    //draw min and max on x axis
    double max = std::max_element(frequency_map_.begin(), frequency_map_.end())->first;
    double min = std::min_element(frequency_map_.begin(), frequency_map_.end())->first;
    ci::gl::drawString(std::to_string(max), x_axis_vec+vec2(0, 10));
    ci::gl::drawString(std::to_string(min), bottom_left_corner_+vec2(0, 10));

    ci::gl::color(color_);
    DrawBars();
}

void Histogram::SetParticleVector(const vector<Particle> &particle_vec) {
    particle_vec_ = particle_vec;
}

map<double, size_t> Histogram::GetFrequencyMap() const {
    return frequency_map_;
}

ci::Color Histogram::GetColor() const {
    return color_;
}

glm::vec2 Histogram::GetBottomLeftCorner() const {
    return bottom_left_corner_;
}

size_t Histogram::GetHistogramSize() const {
    return histogram_size_;
}

double Histogram::GetRoundingFactor() const {
    return rounding_factor_;
}

vector<Particle> Histogram::GetParticleVector() const {
    return particle_vec_;
}

void Histogram::UpdateFrequencyMap() {
    frequency_map_.clear();
    double mult_factor = 1 / rounding_factor_; //used to help round speed values to nearest rounding_factor_ value
    for(Particle particle: particle_vec_) {
        double speed = glm::length(particle.GetVelocity());
        frequency_map_[round(mult_factor*speed)/mult_factor]++;
    }
}

void Histogram::DrawBars(){
    double width;

    if(frequency_map_.empty()) {
        width = 0.0;
    } else width = histogram_size_/frequency_map_.size(); //as speeds become more diverse, there will be more units on histogram to account for it

    vec2 curr_vec = bottom_left_corner_;
    for(auto const &x: frequency_map_) { //iterates through frequency_map
        size_t frequency = frequency_map_[x.first];
        vec2 height_vec = curr_vec-vec2(0, frequency*unit_frequency_height_); //top left corner of rectangle
        curr_vec+=vec2(width, 0); //bottom right corner of rectangle
        ci::Rectf num_box(height_vec, curr_vec);
        ci::gl::drawSolidRect(num_box); //draws a frequency bar on histogram
    }
}
}

}
