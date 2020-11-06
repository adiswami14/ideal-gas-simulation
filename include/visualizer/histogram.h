#pragma once

#include <core/particle.h>
#include "cinder/gl/gl.h"

namespace idealgas {

namespace visualizer {

using std::map;
using std::vector;

class Histogram {
public:
    Histogram();

    Histogram(glm::vec2 bottom_left_corner, size_t histogram_size);

    void SetParticleVector(const vector<Particle> &particle_vec);

    void Draw();

    void Update();

    void SetColor(const ci::Color &color);
private:
    void UpdateFrequencyMap();
    void CreateHistogram();
    glm::vec2 bottom_left_corner_;
    map<double, size_t> frequency_map_;
    size_t histogram_size_;
    vector<Particle> particle_vec_;
    ci::Color color_;
};

} //namespace visualizer

} //namespace idealgas
