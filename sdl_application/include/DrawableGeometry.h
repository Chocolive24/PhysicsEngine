#pragma once

/**
 * @headerfile DrawableGeometry.h
 * This file defines the DrawableGeometry namespace that lets you create displayable geometric shapes using vertices
 * and indices.
 * 
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
     * @param centerPos The position of the center of the circle.
     * @param radius The radius of the circle.
     * @param color The color of the circle.
     */
    void Circle(Math::Vec2F centerPos, float radius, std::size_t segments, SDL_Color color) noexcept;

    /**
     * @brief Rectangle is a method that creates vertices and indices to form a rectangle.
     * @param centerPos The position of the center of the rectangle.
     * @param size The width and height of the rectangle.
     * @param color The color of the rectangle.
     */
    void Rectangle(Math::Vec2F centerPos, Math::Vec2F size, SDL_Color color) noexcept;

    /**
     * @brief Polygon is a method that creates vertices and indices to form a polygon.
     * @param vertices The vertices of the polygon.
     * @param color The color of the polygon.
     */
    void Polygon(Math::Vec2F centerPos, const std::vector<Math::Vec2F>& vertices, SDL_Color color) noexcept;

    /**
     * @brief Line is a method that creates vertices and indices to form a line.
     * @param startPoint The position of start point of the line.
     * @param endPoint The position of start point of the line.
     * @param thickness The thickness of the line.
     * @param color The color of the rectangle.
     */
    void Line(Math::Vec2F startPoint, Math::Vec2F endPoint, float thickness, SDL_Color color) noexcept;
}