#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "simulator.h"

namespace idealgas {

namespace visualizer {

/**
 * The class that extends Cinder and acts as a GUI
 */
class IdealGasApp : public ci::app::App {
public:
    const double kWindowSize = 900;//size of the Cinder window
    const double kXMargin = 250; //margin to keep Box at
    const double kYMargin = 100;
    const size_t kBoxSize = 400; //the size of the Box

    /**
     * Default constructor for this class
     */
    IdealGasApp();
    void draw() override;
    void update() override;
    void keyDown(ci::app::KeyEvent event) override;
private:
    Simulator simulator_; //instance of Simulator class to update particles
    std::string particle_mode_;
};

} //namespace visualizer

} //namespace idealgas