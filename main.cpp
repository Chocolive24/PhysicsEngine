//
// Created by Olivier on 10.10.2023.
//

#include <iostream>

#include "include/dumb.h"

#include "SDL.h"

constexpr int WindowWidth = 880;
constexpr int WindowHeight = 680;

SDL_Window *window;
SDL_Renderer* renderer;
bool quit = false;
SDL_Event event;

int Time = 0;

void InitSDL()
{
//    planet.Position = Vec2F(400.f, 100.f);
//
//    // Rotation center.
//    Vec2F c(WindowWidth / 2.f, WindowHeight / 2.f);
//
//    radius = c - planet.Position;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    window = SDL_CreateWindow("SDL2 Window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WindowWidth, WindowHeight,
                              SDL_WINDOW_RESIZABLE);

    if (!window)
    {
        std::cout << "Failed to create window. Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created! Error :" << " " << SDL_GetError() << "\n";
        exit(1);
    }

    // Enable VSync
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

    Time = SDL_GetTicks64();
}

void DrawCircle(float centerX, float centerY, float radius, int pointNbr)
{
    auto angleIncrement = static_cast<float>((2.0f * M_PI) / pointNbr);

    SDL_Point points[pointNbr];

    for (int i = 0; i < pointNbr; i++)
    {
        float angle = static_cast<float>(i) * angleIncrement;
        float x = centerX + (radius * cos(angle));
        float y = centerY + (radius * sin(angle));

        points[i] = {static_cast<int>(x), static_cast<int>(y)};
    }

    for (int i = 1; i < pointNbr; i++)
    {
        SDL_RenderDrawLine(renderer,points[i-1].x, points[i-1].y, points[i].x, points[i].y);
    }

    SDL_RenderDrawLine(renderer, points[0].x, points[0].y,points[pointNbr-1].x, points[pointNbr-1].y);
}

void DrawFilledCircle(float centerX, float centerY, float radius, int pointNbr)
{
    auto angleIncrement = static_cast<float>((2.0f * M_PI) / pointNbr);

    for (int i = 0; i < pointNbr; i++)
    {
        float angle = static_cast<float>(i) * angleIncrement;
        float x = centerX + (radius * cos(angle));
        float y = centerY + (radius * sin(angle));

        SDL_RenderDrawLineF(renderer, centerX, centerY, x, y);
    }
}

void Update()
{
    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        const float deltaTime = (SDL_GetTicks64() - Time) / 1000.f;

        Time = SDL_GetTicks64();

        // Clear the screen
        SDL_RenderClear(renderer);

        // Set the draw color to red
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        SDL_Rect rect;

        rect.x = 100;
        rect.y = 100;
        rect.w = 100;
        rect.h = 100;

        SDL_RenderFillRect(renderer, &rect);

//        // Rotation center.
//        Vec2F c(WindowWidth / 2.f, WindowHeight / 2.f);
//
//        DrawFilledCircle(c.X, c.Y, 5, 100);
//
//        // Radius of circle.
//        Vec2F r = c - planet.Position;
//
//        std::cout << r.Length() << std::endl;
//
//        DrawCircle(c.X, c.Y, radius.Length(), 100);
//
//        // v = tangent of radius.
//        planet.Velocity = Vec2F(-r.Y, r.X).Normalized() * 500.f;
//
//        Vec2F a = planet.Velocity * planet.Velocity / r.Length();
//
//        planet.Velocity += a * deltaTime;
//
//        planet.Position += planet.Velocity * deltaTime;
//
//        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
//
//        DrawFilledCircle(planet.Position.X, planet.Position.Y, 10, 200);

        // Set the draw color to black
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        // Update the screen
        SDL_RenderPresent(renderer);
    }
}

int main(int argc, char *argv[])
{
    InitSDL();

    Update();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}