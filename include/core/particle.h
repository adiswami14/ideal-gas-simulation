#pragma once

#include "cinder/gl/gl.h"

namespace idealgas {

using glm::vec2;

/**
 * Class representing a single particle in the simulation
 */
class Particle {
public:
    /**
     * Constructor of the Particle class
     * @param pos Position vector of particle to be set
     * @param vel Velocity vector of particle to be set
     */
    Particle(const vec2 &pos, const vec2& vel);

    /**
     * Gets position vector of this particle
     * @return Value of position_ variable
     */
    vec2 GetPosition() const;

    /**
     * Gets velocity vector of this particle
     * @return Value of velocity_ variable
     */
    vec2 GetVelocity() const;

    /**
     * Sets position vector of this particle to a given value
     * @param pos Value of position vector to set position_ variable to
     */
    void SetPosition(const vec2& pos);

    /**
     * Sets velocity vector of this particle to a given value
     * @param pos Value of velocity vector to set velocity_ variable to
     */
    void SetVelocity(const vec2& vel);

    /**
     * Checks if this instance of Particle has collided with a given particle
     * @param p The particle to check collision with
     * @return Whether the particles are due for a collision
     */
    bool HasCollidedWith(const Particle &p) const;

    /**
     * Given a particle, will set velocity to the post-collision velocity provided these two particle have collided
     * @param p The particle to check a collision with
     */
    void ChangePostCollisionVelocity(const Particle &p);

    size_t mass_; //mass of the current particle
    size_t radius_; //radius of the current particle
private:
    /**
     * Given a particle, will find how far this instance of particle is to the given particle
     * @param p The particle to find distance to
     * @return Distance to given particle
     */
    double GetDistanceTo(const Particle &p) const;

    vec2 position_; //position vector of this instance of particle
    vec2 velocity_; //velocity vector of this instance of particle
};
}
