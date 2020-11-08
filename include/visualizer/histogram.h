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

    Histogram(const glm::vec2 &bottom_left_corner, size_t histogram_size, const ci::Color& color, double rounding_factor);

    void SetParticleVector(const vector<Particle> &particle_vec);

    void Draw();

    void UpdateFrequencyMap();

    glm::vec2 GetBottomLeftCorner() const;

    size_t GetHistogramSize() const;

    ci::Color GetColor() const;

    vector<Particle> GetParticleVector() const;

    double GetRoundingFactor() const;

    map<double, size_t> GetFrequencyMap() const;
private:
    void DrawBars();
    glm::vec2 bottom_left_corner_;
    map<double, size_t> frequency_map_;
    size_t histogram_size_;
    vector<Particle> particle_vec_;
    ci::Color color_;
    double rounding_factor_;
};

} //namespace visualizer

} //namespace idealgas
