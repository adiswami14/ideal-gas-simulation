#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"
#include "box.h"

namespace idealgas {

using glm::vec2;
using std::vector;

/**
 * Class used for the generation and storing of all Particles in the simulation
 */
class ParticleGenerator {
public:
    /**
     * Default constructor for ParticleGenerator class
     */
    ParticleGenerator();

    /**
     * Given a position and velocity vector, creates a new Particle
     * @param pos Position vector of particle to be created
     * @param vel Velocity vector of particle to be created
     */
    void GenerateParticle(const vec2& pos, const vec2& vel, std::string particle_type);

    /**
     * Sets instance of Box within the instance of ParticleGenerator
     * @param box The value to set box_ variable's value to
     */
    void SetBox(const Box& box);

    /**
     * Returns list of all particles in simulations
     * @return The particle_list_ vector
     */
    vector<Particle> GetParticleList() const;

    /**
     * Updates all Particle positions and velocities in simulations, and checks for collisions
     */
    void UpdateParticles();

    void ChangeVelocities(double factor);
private:
    /**
     * Checks for particle-to-particle collisions
     * @param p The particle we are checking collisions for
     * @param curr_index Current index of that particle in list
     * @param p_position Position of the particle
     * @param p_velocity Velocity of the particle
     */
    void CheckCollisions(Particle &p, size_t curr_index, const vec2 &p_position, vec2 &p_velocity);

    /**
     * Checks if a particle has hit one of the walls of the box
     * @param p The particle we are checking wall collisions for
     * @param p_velocity Velocity of the particle
     */
    void CheckBounds(const Particle &p, vec2 &p_velocity);

    vector<Particle> particle_list_; //vector containing all Particles in the simulation
    Box box_; //instance of Box within where the simulation takes place
};

} //namespace idealgas

