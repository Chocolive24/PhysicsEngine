#pragma once

/**
 * @headerfile DrawableGeometry is a namespace that lets you create displayable geometric shapes using vertices
 * and indices.
 * @author Olivier Pachoud
 */

#include "Vec2.h"

#include "SDL.h"

#include <vector>

namespace DrawableGeometry
{
    /**
     * @brief Vertices are the fundamental elements used to define the shape and structure of graphics objects.
     */
    extern std::vector<SDL_Vertex> Vertices;

    /**
     * @brief Indices are the values used to represent the connectivity information for vertices.
     */
    extern std::vector<int> Indices;

    /**
     * @brief ClearGeometry is a method that deletes all vertices and indices.
     */
    void ClearGeometry()  noexcept;

    /**
     * @brief Circle is a method that creates vertices and indices to form a circle.
     * @param position The position of the center of the circle.
     * @param radius The radius of the circle.
     * @param color The color of the circle.
     */
    void Circle(Math::Vec2F position, float radius, std::size_t segments, SDL_Color color) noexcept;
};