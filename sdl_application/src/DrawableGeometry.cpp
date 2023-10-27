//
// Created by Olivier on 18.10.2023.
//

#include <iostream>
#include "DrawableGeometry.h"
#include "Shape.h"

namespace DrawableGeometry
{
    std::vector<SDL_Vertex> Vertices;
    std::vector<int> Indices;

    void addVertex(Math::Vec2F pos, SDL_Color color, float u = 1.f, float v = 1.f) noexcept
    {
        SDL_Vertex vertex;
        vertex.position.x = pos.X;
        vertex.position.y = pos.Y;
        vertex.color.r = color.r;
        vertex.color.g = color.g;
        vertex.color.b = color.b;
        vertex.color.a = color.a;
        vertex.tex_coord.x = u;
        vertex.tex_coord.y = v;

        Vertices.push_back(vertex);
    }

    void ClearGeometry() noexcept
    {
        Vertices.clear();
        Indices.clear();
    }

    void Circle(const Math::Vec2F centerPos,
                const float radius,
                const std::size_t segments,
                const SDL_Color color) noexcept
    {
        const int indicesOffset = static_cast<int>(Vertices.size());

        // Calculate vertices for the circle
        for (int i = 0; i < segments; i++)
        {
            float angle = 2.0f * Math::Pi * static_cast<float>(i) / static_cast<float>(segments);
            float x = centerPos.X + radius * cos(angle);
            float y = centerPos.Y + radius * sin(angle);

            addVertex(Math::Vec2F(x, y), color, 1, 1);

            if (i == segments - 1) break;

            Indices.push_back(indicesOffset); // Center point
            Indices.push_back(indicesOffset + i);
            Indices.push_back(indicesOffset + i + 1);
        }

        Indices.push_back(indicesOffset); // Center point
        Indices.push_back(indicesOffset + static_cast<int>(segments) - 1);
        Indices.push_back(indicesOffset);  // Connect the last vertex to the center
    }

    void Rectangle(const Math::Vec2F centerPos, const Math::Vec2F size, const SDL_Color color) noexcept
    {
        const int indicesOffset = static_cast<int>(Vertices.size());

        auto halfWidth = size.X * 0.5f, halfHeight = size.Y * 0.5f;

        // Left-down corner.
        addVertex(Math::Vec2F(centerPos.X - halfWidth, centerPos.Y - halfHeight), color);
        // Left-up corner.
        addVertex(Math::Vec2F(centerPos.X - halfWidth, centerPos.Y + halfHeight), color);
        // Right-up corner.
        addVertex(Math::Vec2F(centerPos.X + halfWidth, centerPos.Y + halfHeight), color);
        // Right-down corner.
        addVertex(Math::Vec2F(centerPos.X + halfWidth, centerPos.Y - halfHeight), color);

        // First triangle.
        Indices.push_back(indicesOffset);
        Indices.push_back(indicesOffset + 1);
        Indices.push_back(indicesOffset + 2);

        // Second triangle.
        Indices.push_back(indicesOffset);
        Indices.push_back(indicesOffset + 2);
        Indices.push_back(indicesOffset + 3);
    }

    void Polygon(const Math::Vec2F centerPos, const std::vector<Math::Vec2F>& vertices, const SDL_Color color) noexcept
    {
        if (vertices.size() < 3) return;

        const int indicesOffset = static_cast<int>(Vertices.size());

        for (const Math::Vec2F& v : vertices)
        {
            // Update the vertices based on the provided center position
            Math::Vec2F updatedVertex = centerPos + v;
            Vertices.push_back({{updatedVertex.X, updatedVertex.Y}, color, {1.0f, 1.0f}});
        }

        for (int i = 1; i < vertices.size() - 1; ++i)
        {
            Indices.push_back(indicesOffset);
            Indices.push_back(indicesOffset + i);
            Indices.push_back(indicesOffset + i + 1);
        }

        // Connect the last vertex to the first vertex to close the polygon.
        Indices.push_back(indicesOffset);
        Indices.push_back(indicesOffset + static_cast<int>(vertices.size()) - 1);
        Indices.push_back(indicesOffset + 1);
    }

    void Line(Math::Vec2F startPoint, Math::Vec2F endPoint, float thickness, SDL_Color color) noexcept
    {
        const int indicesOffset = static_cast<int>(Vertices.size());

        const auto lineVector = endPoint - startPoint;
        const auto lineDirection = lineVector.Normalized();
        const auto vPerp = Math::Vec2F(lineDirection.Y, -lineDirection.X);

        const auto p0 = startPoint + vPerp * (thickness * 0.5f);
        const auto p1 = startPoint - vPerp * (thickness * 0.5f);
        const auto p2 = endPoint + vPerp * (thickness * 0.5f);
        const auto p3 = endPoint - vPerp * (thickness * 0.5f);

        addVertex(p0, color);
        addVertex(p1, color);
        addVertex(p2, color);
        addVertex(p3, color);

        // First triangle.
        Indices.push_back(indicesOffset);
        Indices.push_back(indicesOffset + 1);
        Indices.push_back(indicesOffset + 2);

        // Second triangle.
        Indices.push_back(indicesOffset);
        Indices.push_back(indicesOffset + 2);
        Indices.push_back(indicesOffset + 3);
    }
}