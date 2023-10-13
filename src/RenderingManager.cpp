#include "RenderingManager.h"
#include "MathUtility.h"

#include <iostream>

void RenderingManager::Init() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    Window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              RenderingManager::WindowWidth, RenderingManager::WindowHeight,
                              SDL_WINDOW_RESIZABLE);

    if (!Window)
    {
        std::cout << "Failed to create  Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    Renderer = SDL_CreateRenderer(Window, 0, SDL_RENDERER_ACCELERATED);

    if (Renderer == nullptr)
    {
        std::cout << "Renderer could not be created! Error :" << " " << SDL_GetError() << "\n";
        exit(1);
    }

    // Enable VSync
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
}

void RenderingManager::UnInit() const noexcept
{
    SDL_DestroyRenderer(Renderer);
    SDL_DestroyWindow(Window);
    SDL_Quit();
}

void RenderingManager::DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept
{
    auto angleIncrement = (2.0f * MathUtility::Pi) / static_cast<float>(pointNbr);

    SDL_Point points[pointNbr];

    for (std::size_t i = 0; i < pointNbr; i++)
    {
        float angle = static_cast<float>(i) * angleIncrement;
        float x = centerX + (r * MathUtility::Cos(Radian(angle)));
        float y = centerY + (r * MathUtility::Sin(Radian(angle)));

        points[i] = {static_cast<int>(x), static_cast<int>(y)};
    }

    for (int i = 1; i < pointNbr; i++)
    {
        SDL_RenderDrawLine(Renderer, points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
    }

    SDL_RenderDrawLine(Renderer, points[0].x, points[0].y, points[pointNbr - 1].x, points[pointNbr - 1].y);
}

void RenderingManager::DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr) const noexcept
{
    auto angleIncrement = (2.0f * MathUtility::Pi) / static_cast<float>(pointNbr);

    for (std::size_t i = 0; i < pointNbr; i++)
    {
        float angle = static_cast<float>(i) * angleIncrement;
        float x = centerX + (r * MathUtility::Cos(Radian(angle)));
        float y = centerY + (r * MathUtility::Sin(Radian(angle)));

        SDL_RenderDrawLineF(Renderer, centerX, centerY, x, y);
    }
}