#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size)
: top_left_corner_(top_left_corner),
  box_size_(box_size){
    Box box(top_left_corner_, box_size_);
    particle_generator_.SetBox(box);

    Histogram histogram(vec2(150, 750), 100, ci::Color("red"), 0.5);
    Histogram histogram2(vec2(450, 750), 100, ci::Color("blue"), 0.5);
    Histogram histogram3(vec2(750, 750), 100, ci::Color("white"), 0.5);
    red_histogram_ = histogram;
    blue_histogram_ = histogram2;
    white_histogram_ = histogram3;

}

void Simulator::Update() {
    particle_generator_.UpdateParticles();
    UpdateHistogramVectors();
    red_histogram_.UpdateFrequencyMap();
    blue_histogram_.UpdateFrequencyMap();
    white_histogram_.UpdateFrequencyMap();
}

void Simulator::Draw() {
 red_particle_list_.clear();
 blue_particle_list_.clear();
 white_particle_list_.clear();

 vec2 bottom_right_corner = top_left_corner_+vec2(box_size_, box_size_);
 ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
 ci::gl::color(ci::Color("black"));
 ci::gl::drawSolidRect(pixel_bounding_box);
 ci::gl::color(ci::Color("grey")); //draws box within which simulation will take place
 ci::gl::drawStrokedRect(pixel_bounding_box);

 for(Particle p : particle_generator_.GetParticleList()) {
     if(p.mass_ == 2 && p.radius_ == 2) { //red particle
         ci::gl::color(ci::Color("red"));
         red_particle_list_.push_back(p);
     } else if(p.mass_ == 5 && p.radius_ == 4) {  //blue particle
         ci::gl::color(ci::Color("blue"));
         blue_particle_list_.push_back(p);
     } else if(p.mass_ == 10 && p.radius_ == 7) {  //white particle
         ci::gl::color(ci::Color("white"));
         white_particle_list_.push_back(p);
     }
     ci::gl::drawSolidCircle(p.GetPosition(), p.radius_);
 }

 DrawHistograms();
}

ParticleManager Simulator::GetParticleGenerator() const {
    return particle_generator_;
}

void Simulator::SetParticleGenerator(const ParticleManager &particle_generator) {
    particle_generator_ = particle_generator;
}

void Simulator::UpdateHistogramVectors() {
    red_histogram_.SetParticleVector(red_particle_list_);
    blue_histogram_.SetParticleVector(blue_particle_list_);
    white_histogram_.SetParticleVector(white_particle_list_);
}

void Simulator::DrawHistograms() {
    red_histogram_.Draw();
    blue_histogram_.Draw();
    white_histogram_.Draw();
}
} //namespace visualizer

} //namespace idealgas

