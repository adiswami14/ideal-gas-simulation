#pragma once

#include <core/box.h>
#include <core/particle_generator.h>
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

    /**
     * Gets instance of ParticleGenerator class in this instance of Simulator
     * @return The variable particle_generator_
     */
    ParticleGenerator GetParticleGenerator() const;

    /**
     * Sets value of current instance of ParticleGenerator variable to variable passed in
     * @param particle_generator The value to set particle_generator_ to
     */
    void SetParticleGenerator(const ParticleGenerator& particle_generator);
private:
    glm::vec2 top_left_corner_; //Top left corner of the Box
    size_t box_size_; //size of the Box
    ParticleGenerator particle_generator_; //Instance of Particle Generator in order to keep generating particles
    Histogram histogram_;
};

} //namespace visualizer

} //namespace idealgas
