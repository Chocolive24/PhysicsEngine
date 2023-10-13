#pragma once

#include <cstddef>
#include "SDL.h"

class GraphicsManager
{
public:
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    SDL_Window* Window;
    SDL_Renderer* Renderer;

    void Init();

    void UnInit();

    void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr);
    void DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr);
};