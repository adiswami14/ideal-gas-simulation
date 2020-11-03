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
    const double kWindowSize = 600;//size of the Cinder window
    const double kMargin = 50; //margin to keep Box at
    const size_t kBoxSize = 500; //the size of the Box

    /**
     * Default constructor for this class
     */
    IdealGasApp();
    void draw() override;
    void keyDown(ci::app::KeyEvent event) override;
private:
    Simulator simulator_; //instance of Simulator class to update particles
    bool particle_mode_; //true for red particle, false for blue particle
};

} //namespace visualizer

} //namespace idealgas