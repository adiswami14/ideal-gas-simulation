#include <visualizer/ideal_gas_app.h>

namespace idealgas {

namespace visualizer {

IdealGasApp::IdealGasApp() : simulator_(glm::vec2(kMargin, kMargin), 500){
    ci::app::setWindowSize((int) kWindowSize, (int) kWindowSize);
}

void IdealGasApp::draw() {
    ci::Color8u background_color(23, 23, 23);
    ci::gl::clear(background_color);
    simulator_.Draw();
}

} //namespace visualizer

} //namespace idealgas

