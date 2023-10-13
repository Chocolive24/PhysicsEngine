#pragma once

#include "Definition.h"

#include "SDL.h"

#include <cstddef>

class RenderingManager
{
public:
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    SDL_Window* Window;
    SDL_Renderer* Renderer;

    void Init() noexcept;

    void UnInit() const noexcept;

    void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept;
    void DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept;
};