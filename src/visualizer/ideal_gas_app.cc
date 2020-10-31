#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() : simulator_(glm::vec2(kMargin, kMargin), kBoxSize, kParticleRadius){
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::draw() {
    ci::Color8u background_color(23, 23, 23);
    ci::gl::clear(background_color);
    simulator_.Draw();
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
    ParticleGenerator pg = simulator_.GetParticleGenerator();
    switch (event.getCode()) {
        case ci::app::KeyEvent::KEY_SPACE:
            glm::vec2 position(55.5, 56.7); //every particle starts at same position and velocity
            glm::vec2 velocity(1.4, -0.8);
            pg.GenerateParticle(position, velocity);
            simulator_.SetParticleGenerator(pg);
            break;
    }
}
} //namespace visualizer

} //namespace idealgas

