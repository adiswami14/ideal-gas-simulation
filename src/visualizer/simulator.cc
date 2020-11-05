#include <visualizer/simulator.h>

namespace idealgas {

namespace visualizer {

using glm::vec2;

Simulator::Simulator(const glm::vec2 &top_left_corner, size_t box_size)
: top_left_corner_(top_left_corner),
  box_size_(box_size){
    Box box(top_left_corner_, box_size_);
    particle_generator_.SetBox(box);
    Histogram histogram(vec2(150, 750), 100);
    Histogram histogram2(vec2(450, 750), 100);
    Histogram histogram3(vec2(750, 750), 100);
    red_histogram_ = histogram;
    red_histogram_.SetColor(ci::Color("red"));
    blue_histogram_ = histogram2;
    blue_histogram_.SetColor(ci::Color("blue"));
    white_histogram_ = histogram3;
    white_histogram_.SetColor(ci::Color("white"));

}

void Simulator::Draw() {
 vec2 bottom_right_corner = top_left_corner_+vec2(box_size_, box_size_);
 ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner);
 ci::gl::color(ci::Color("black"));
 ci::gl::drawSolidRect(pixel_bounding_box);
 ci::gl::color(ci::Color("grey")); //draws box within which simulation will take place
 ci::gl::drawStrokedRect(pixel_bounding_box);

 vector<Particle> red_particle_list;
 vector<Particle> blue_particle_list;
 vector<Particle> white_particle_list;

 particle_generator_.UpdateParticles();
 for(Particle p : particle_generator_.GetParticleList()) {
     if(p.mass_ == 2) {
         ci::gl::color(ci::Color("red"));
         red_particle_list.push_back(p);
     } else if(p.mass_ == 5) {
         ci::gl::color(ci::Color("blue"));
         blue_particle_list.push_back(p);
     } else if(p.mass_ == 10) {
         ci::gl::color(ci::Color("white"));
         white_particle_list.push_back(p);
     }
     ci::gl::drawSolidCircle(p.GetPosition(), p.radius_);
 }
 DrawHistograms(red_particle_list, blue_particle_list, white_particle_list);
}

ParticleGenerator Simulator::GetParticleGenerator() const {
    return particle_generator_;
}

void Simulator::SetParticleGenerator(const ParticleGenerator &particle_generator) {
    particle_generator_ = particle_generator;
}

void Simulator::DrawHistograms(const vector<Particle> &red_particle_list, const vector<Particle> &blue_particle_list, const vector<Particle> &white_particle_list) {
    red_histogram_.SetParticleVector(red_particle_list);
    red_histogram_.Draw();
    blue_histogram_.SetParticleVector(blue_particle_list);
    blue_histogram_.Draw();
    white_histogram_.SetParticleVector(white_particle_list);
    white_histogram_.Draw();
}
} //namespace visualizer

} //namespace idealgas

