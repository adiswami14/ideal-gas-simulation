#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

class IdealGasApp : public ci::app::App {
public:
    IdealGasApp();

    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    void mouseDrag(ci::app::MouseEvent event) override;
    void keyDown(ci::app::KeyEvent event) override;

    const double kWindowSize = 475;
    const double kMargin = 50;
    const size_t kImageDimension = 28;
};

} //namespace visualizer

} //namespace idealgas