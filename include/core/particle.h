#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

class Particle {
public:
    Particle(const vec2 &pos, const vec2& vel);

    vec2 GetPosition() const;

    vec2 GetVelocity() const;

    void SetPosition(const vec2& pos);

    void SetVelocity(const vec2& vel);

    double GetDistanceTo(const Particle &p) const;

    bool HasCollidedWith(const Particle &p, size_t particle_radius) const;

    bool operator==(const Particle& p) const;

    void ChangePostCollisionVelocity(const Particle &p);

private:
    vec2 position_;
    vec2 velocity_;
};
}
