#pragma once

#include <core/box.h>
#include <core/particle_manager.h>
#include "cinder/gl/gl.h"
#include "histogram.h"

namespace idealgas {

namespace visualizer {

/**
 * Class that acts as the general environment of the project
 */
class Simulator {
public:
    /**
     * The constructor for the Simulator class
     * @param top_left_corner The top left corner of the Box
     * @param box_size The size of the box
     */
    Simulator(const glm::vec2& top_left_corner, size_t box_size);

    /**
     * Draws Box and all particle values in simulation
     */
    void Draw();

    /**
     * Updates all Particle position and velocity
     */
    void Update();

    /**
     * Gets instance of ParticleManager class in this instance of Simulator
     * @return The variable particle_generator_
     */
    ParticleManager GetParticleGenerator() const;

    /**
     * Sets value of current instance of ParticleManager variable to variable passed in
     * @param particle_generator The value to set particle_generator_ to
     */
    void SetParticleGenerator(const ParticleManager& particle_generator);
private:
    /**
     * Sets particle vectors of histograms and draws histograms onto screen
     */
    void DrawHistograms();

    /**
     * Updates the vectors of RedParticles, BlueParticles, and WhiteParticles to pass into histogram
     */
    void UpdateHistogramVectors();

    glm::vec2 top_left_corner_; //Top left corner of the Box
    size_t box_size_; //size of the Box
    ParticleManager particle_generator_; //Instance of Particle Generator in order to keep generating particles
    Histogram red_histogram_; //histogram for RedParticles
    Histogram blue_histogram_; //histogram for BlueParticles
    Histogram white_histogram_; //histogram for WhiteParticles
    vector<Particle> red_particle_list_; //list of all RedParticles in simulation
    vector<Particle> blue_particle_list_; //list of all BlueParticles in simulation
    vector<Particle> white_particle_list_; //list of all WhiteParticles in simulation
};

} //namespace visualizer

} //namespace idealgas
