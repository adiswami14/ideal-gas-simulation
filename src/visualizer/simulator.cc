#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size, size_t particle_radius)
: top_left_corner_(top_left_corner),
  box_size_(box_size),
  particle_radius_(particle_radius){
    Box box(top_left_corner_, box_size_, particle_radius_);
    box_ = box;
    vec2 test_pos(64.3, 912.4);
}

void Simulator::Draw() {
 vec2 bottom_right_corner = top_left_corner_+vec2(box_size_, box_size_);
 ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
 ci::gl::color(ci::Color("black"));
 ci::gl::drawSolidRect(pixel_bounding_box);
 ci::gl::color(ci::Color("grey"));
 ci::gl::drawStrokedRect(pixel_bounding_box);

 vector<ParticleGenerator::Particle> particle_list = particle_generator_.GetParticleList();
 for(size_t index = 0; index < particle_list.size(); index++) {
     ParticleGenerator::Particle p = particle_list.at(index);
     ci::gl::color(ci::Color("white"));
     ci::gl::drawSolidCircle(p.position, particle_radius_);
     if(box_.IsAtXBoundary(p.position)) {
         p.velocity.x*=-1;
     }
     if(box_.IsAtYBoundary(p.position)) {
         p.velocity.y*=-1;
     }
     p.position+=p.velocity;
     particle_list.at(index) = p;
 }
 particle_generator_.SetParticleList(particle_list);
}

ParticleGenerator Simulator::GetParticleGenerator() const {
    return particle_generator_;
}

void Simulator::SetParticleGenerator(const ParticleGenerator &particle_generator) {
    particle_generator_ = particle_generator;
}
} //namespace visualizer

} //namespace idealgas

