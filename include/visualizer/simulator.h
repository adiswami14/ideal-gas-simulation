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
     * @param particle_radius The radius of each particle
     */
    Simulator(const glm::vec2& top_left_corner, size_t box_size);

    /**
     * Updates Particle values and redraws them
     */
    void Draw();

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
    void DrawHistograms(const vector<Particle> &red_particle_list, const vector<Particle> &blue_particle_list, const vector<Particle> &white_particle_list);

    glm::vec2 top_left_corner_; //Top left corner of the Box
    size_t box_size_; //size of the Box
    ParticleManager particle_generator_; //Instance of Particle Generator in order to keep generating particles
    Histogram red_histogram_;
    Histogram blue_histogram_;
    Histogram white_histogram_;
};

} //namespace visualizer

} //namespace idealgas
