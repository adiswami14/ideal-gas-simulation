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

 vector<Particle> particle_list = particle_generator_.GetParticleList();
 vector<Particle> removed_particle_list = particle_list;
 for(size_t index = 0; index < particle_list.size(); index++) {
     Particle p = particle_list.at(index);
     vec2 curr_particle_position = p.GetPosition();
     vec2 curr_particle_velocity = p.GetVelocity();
     auto it=std::find(removed_particle_list.begin(),removed_particle_list.end(),p);
     if(it!=removed_particle_list.end()) {
         removed_particle_list.erase(it);
     }
     ci::gl::color(ci::Color("white"));
     ci::gl::drawSolidCircle(curr_particle_position, particle_radius_);
     for(size_t indexs = 0; indexs < removed_particle_list.size(); indexs++) {
         Particle particle = removed_particle_list.at(indexs);
         vec2 diff_position = curr_particle_position - particle.GetPosition();
         vec2 diff_velocity = curr_particle_velocity - particle.GetVelocity();
         if(p.HasCollidedWith(particle, particle_radius_) && glm::dot(diff_position, diff_velocity) <0) {
             p.ChangePostCollisionVelocity(particle);
             particle.ChangePostCollisionVelocity(p);
             curr_particle_velocity = p.GetVelocity();
             particle_list.at(indexs).SetVelocity(particle.GetVelocity());
         }
     }
     if(box_.IsAtXBoundary(curr_particle_position)) {
         curr_particle_velocity.x*=-1;
     }
     if(box_.IsAtYBoundary(curr_particle_position)) {
         curr_particle_velocity.y*=-1;
     }
     curr_particle_position += curr_particle_velocity;
     p.SetPosition(curr_particle_position);
     p.SetVelocity(curr_particle_velocity);
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

