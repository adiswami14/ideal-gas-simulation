#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size, size_t particle_radius)
: top_left_corner_(top_left_corner),
  box_size_(box_size),
  particle_radius_(particle_radius){
    Box box(top_left_corner_, box_size_, particle_radius_);
    particle_generator_.SetBox(box);
    particle_generator_.SetParticleRadius(particle_radius_);
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
     ci::gl::color(ci::Color("white"));
     ci::gl::drawSolidCircle(p.GetPosition(), particle_radius_);
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

