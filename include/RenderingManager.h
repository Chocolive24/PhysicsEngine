#pragma once

#include "Definition.h"
#include "Vec2.h"

#include "SDL.h"

#include <cstddef>
#include <vector>

class RenderingManager
{
private:
    std::vector<SDL_Vertex> _vertices;
    std::vector<int> _indices;

public:
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    SDL_Window* Window{};
    SDL_Renderer* Renderer{};

    void Init() noexcept;

    void UnInit() const noexcept;

    void AddVertex(Vec2F pos, SDL_Color color, float u = 1, float v = 1);
    void ClearGeometry()  noexcept;
    //void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept;
    void DrawFilledCircle(Vec2F position, float r, std::size_t segments, SDL_Color color) noexcept;
};