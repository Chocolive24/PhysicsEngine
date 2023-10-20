//
// Created by Olivier on 18.10.2023.
//

#include "DrawableGeometry.h"

namespace DrawableGeometry
{
    std::vector<SDL_Vertex> Vertices;
    std::vector<int> Indices;

    void AddVertex(Math::Vec2F pos, SDL_Color color, float u, float v) noexcept
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

    void Circle(Math::Vec2F position, float radius, std::size_t segments, SDL_Color color) noexcept
    {
        const int indicesOffset = static_cast<int>(Vertices.size());

        // Calculate vertices for the circle
        for (int i = 0; i < segments; i++)
        {
            float angle = 2.0f * Math::Pi * static_cast<float>(i) / static_cast<float>(segments);
            float x = position.X + radius * cos(angle);
            float y = position.Y + radius * sin(angle);

            AddVertex(Math::Vec2F(x, y), color, 1, 1);

            if (i == segments - 1) break;

            Indices.push_back(indicesOffset); // Center point
            Indices.push_back(indicesOffset + i);
            Indices.push_back(indicesOffset + i + 1);
        }

        Indices.push_back(indicesOffset); // Center point
        Indices.push_back(indicesOffset + static_cast<int>(segments) - 1);
        Indices.push_back(indicesOffset);  // Connect the last vertex to the center
    }
}