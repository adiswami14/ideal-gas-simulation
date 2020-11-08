#pragma once

#include <core/particle.h>
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::map;
using std::vector;

/**
 * Class that is responsible of the display of a singular histogram in the simulation
 */
class Histogram {
public:
    /**
     * Default constructor of Histogram class
     */
    Histogram();

    /**
     * Overloaded constructor of Histogram class
     * @param bottom_left_corner Location of origin point of histogram
     * @param histogram_size Size of histogram in each direction
     * @param color Color of bars in histogram
     * @param rounding_factor Factor to round to the nearest of
     */
    Histogram(const glm::vec2 &bottom_left_corner, size_t histogram_size, const ci::Color& color, double rounding_factor);

    /**
     * Sets value of current instance of vector of Particles to vector passed in
     * @param particle_vec The value to set particle_vec_ to
     */
    void SetParticleVector(const vector<Particle> &particle_vec);

    /**
     * Draws all of the histogram onto the screen
     */
    void Draw();

    /**
     * Updates the frequency map based on the vector of Particles passed in
     * Called in simulator Update() function
     */
    void UpdateFrequencyMap();

    /**
     * Returns position of origin point of histogram
     * @return The bottom_left_corner_ variable
     */
    glm::vec2 GetBottomLeftCorner() const;

    /**
     * Returns size of histogram
     * @return The histogram_size_ variable
     */
    size_t GetHistogramSize() const;

    /**
     * Returns current color of histogram
     * @return The color_ variable
     */
    ci::Color GetColor() const;

    /**
     * Returns list of all particles to draw data from
     * @return The particle_vec_ vector
     */
    vector<Particle> GetParticleVector() const;

    /**
     * Returns speed rounding factor of the histogram
     * @return The rounding_factor_ variable
     */
    double GetRoundingFactor() const;

    /**
     * Returns map that connects speeds of particles to frequency
     * @return The frequency_map_ variable
     */
    map<double, size_t> GetFrequencyMap() const;
private:
    /**
     * Draws the frequency bars of the histogram based on data of the frequency map
     * Should only be called upon after frequency map is updated
     */
    void DrawBars();

    glm::vec2 bottom_left_corner_; //origin point of the histogram
    map<double, size_t> frequency_map_; //map used to map each speed onto the frequency of each speed
    size_t histogram_size_; //size of the histogram instance
    vector<Particle> particle_vec_; //vector of Particles to draw data from
    ci::Color color_; //color of the overall histogram bars
    double rounding_factor_; //nearest factor to round speed data to
};

} //namespace visualizer

} //namespace idealgas
