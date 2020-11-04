#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size)
: top_left_corner_(top_left_corner),
  box_size_(box_size){
    Box box(top_left_corner_, box_size_);
    particle_generator_.SetBox(box);
}

void Simulator::Draw() {
 vec2 bottom_right_corner = top_left_corner_+vec2(box_size_, box_size_);
 ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
 ci::gl::color(ci::Color("black"));
 ci::gl::drawSolidRect(pixel_bounding_box);
 ci::gl::color(ci::Color("grey")); //draws box within which simulation will take place
 ci::gl::drawStrokedRect(pixel_bounding_box);

 particle_generator_.UpdateParticles();
 for(Particle p : particle_generator_.GetParticleList()) {
     if(p.mass_ == 2) {
         ci::gl::color(ci::Color("red"));
     } else if(p.mass_ == 5) {
         ci::gl::color(ci::Color("blue"));
     } else if(p.mass_ == 10) ci::gl::color(ci::Color("white"));
     ci::gl::drawSolidCircle(p.GetPosition(), p.radius_);
 }
}

ParticleGenerator Simulator::GetParticleGenerator() const {
    return particle_generator_;
}

void Simulator::SetParticleGenerator(const ParticleGenerator &particle_generator) {
    particle_generator_ = particle_generator;
}
} //namespace visualizer

} //namespace idealgas

