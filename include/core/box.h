#pragma once

#include "cinder/gl/gl.h"
#include "particle.h"

namespace idealgas {

using glm::vec2;

/**
 * The class that represents the bounds of a box in which the particles will bounce around
 */
class Box {
public:
    /**
     * Default constructor of Box class
     */
    Box();

    /**
     * Overloaded constructor of Box class
     * @param top_left_corner Top left corner of this instance of box
     * @param box_size The size of this instance of box
     * @param particle_radius The radius of each particle in the box
     */
    Box(const vec2& top_left_corner, size_t box_size);

    /**
     * The top left corner position in this instance of box
     * @return The top_left_corner_ variable
     */
    vec2 GetTopLeftCorner() const;

    /**
     * The size of this instance of box
     * @return The box_size_ variable
     */
    size_t GetBoxSize() const;

    /**
     * Checks if a given particle is at a x-wall boundary
     * @param p The particle whose position we are checking
     * @return Whether the given particle is at a x-wall
     */
    bool IsAtXBoundary(const Particle &p) const;

    /**
     * Checks if a given particle is at a y-wall boundary
     * @param p The particle whose position we are checking
     * @return Whether the given particle is at a y-wall
     */
    bool IsAtYBoundary(const Particle &p) const;

private:
    /**
     * Sets values of boundary positions (the x and y values of each wall)
     */
    void InitializeBounds();

    std::vector<double> x_boundary_positions_; //vector that keeps track of the x-wall x-positions
    std::vector<double> y_boundary_positions_; //vector that keeps track of the y-wall y-positions
    vec2 top_left_corner_; //top left corner position of the instance of box
    size_t box_size_; //size of this instance of box
};

} //namespace idealgas
