#pragma once

#include "Definition.h"
#include "Vec2.h"

#include "SDL.h"

#include <cstddef>

class RenderingManager
{
private:
    SDL_Vertex _vertexBuffer[1000]{};
    int   _vertexBufferUsed = 0;

    int _indexBuffer[1000]{};
    int _indexBufferUsed = 0;

public:
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    SDL_Window* Window{};
    SDL_Renderer* Renderer{};

    void Init() noexcept;

    void UnInit() const noexcept;

    void AddVertex(Vec2F pos, SDL_Color color, float u = 1, float v = 1);
    void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept;
    void DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr, SDL_Color color) noexcept;
};