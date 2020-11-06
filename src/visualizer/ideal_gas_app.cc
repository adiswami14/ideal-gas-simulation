#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() : simulator_(glm::vec2(kXMargin, kYMargin), kBoxSize){
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
    particle_mode_ = "red";
}

void IdealGasApp::draw() {
    ci::Color8u background_color(23, 23, 23);
    ci::gl::clear(background_color);
    simulator_.Draw();
}

void IdealGasApp::update() {
    simulator_.Update();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
    ParticleGenerator pg = simulator_.GetParticleGenerator();
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_RIGHT:
            pg.ChangeVelocities(1.2);
            simulator_.SetParticleGenerator(pg);
            break;
        case ci::app::KeyEvent::KEY_LEFT:
            pg.ChangeVelocities(0.8);
            simulator_.SetParticleGenerator(pg);
            break;
        case ci::app::KeyEvent::KEY_r:
            particle_mode_ = "red";
            break;
        case ci::app::KeyEvent::KEY_b:
            particle_mode_ = "blue";
            break;
        case ci::app::KeyEvent::KEY_w:
            particle_mode_ = "white";
            break;
        case ci::app::KeyEvent::KEY_SPACE:
            glm::vec2 position(255.5, 106.7); //every particle starts at same position and velocity
            glm::vec2 velocity(1.4, -0.8);
            pg.GenerateParticle(position, velocity, particle_mode_);
            simulator_.SetParticleGenerator(pg);
            break;
    }
}
} //namespace visualizer

} //namespace idealgas

