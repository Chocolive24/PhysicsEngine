//
// Created by Olivier on 10.10.2023.
//

#include <array>
#include <iostream>

#include "Body.h"
#include "Planet.h"
#include "Random.h"

#include "SDL.h"

constexpr int WindowWidth = 880;
constexpr int WindowHeight = 680;

SDL_Window* window;
SDL_Renderer* renderer;
bool quit = false;
SDL_Event event;

unsigned long long Time = 0;
float deltaTime;

std::array<Planet, 20> planets;

const Vec2F RotationCenter(WindowWidth / 2.f, WindowHeight / 2.f);

void InitSDL();
void CalculatePlanetMovements();
void RenderScreen();
void Update();
void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr);
void DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr);

int main()
{
    InitSDL();

    for(std::size_t i = 0; i < planets.size(); i++)
    {
        Vec2F rndPos(Random::Range(400.f, 600.f), Random::Range(100.f, 500.f));
        Planet p(Body(rndPos, Vec2F::Zero), Random::Range(3.f, 10.f),
                 Random::Range(100.f, 500.f));

        planets[i] = p;
    }

    Time = SDL_GetTicks64();

    Update();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

void InitSDL()
{
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

        deltaTime = (static_cast<float>(SDL_GetTicks64() - Time)) / 1000.f;
        Time = SDL_GetTicks64();

        CalculatePlanetMovements();

        RenderScreen();
    }
}

void CalculatePlanetMovements()
{
    for (auto& p : planets)
    {
        Body& planetBody = p.GetBody();
        float planetSpeed = p.GetSpeed();

        // Radius of circle.
        Vec2F r = RotationCenter - planetBody.Position;

        // v = tangent of radius.
        planetBody.Velocity = Vec2F(-r.Y, r.X).Normalized() * planetSpeed;

        // a = v^2 / r
        Vec2F a = (planetBody.Velocity * planetBody.Velocity) / r.Length();

        planetBody.Velocity += a.Normalized() * planetSpeed * deltaTime;

        planetBody.Position += planetBody.Velocity * deltaTime;
    }
}

void RenderScreen()
{
    // Clear the screen
    SDL_RenderClear(renderer);

    // Set the draw color to red
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

    DrawFilledCircle(RotationCenter.X, RotationCenter.Y, 5, 200);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    for(auto& p : planets)
    {
        Body planetBody = p.GetBody();

        DrawFilledCircle(planetBody.Position.X, planetBody.Position.Y, p.GetRadius(), 200);
    }

    // Set the draw color to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // Update the screen
    SDL_RenderPresent(renderer);
}

void DrawCircle(float centerX, float centerY, float r, std::size_t pointNbr)
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
        SDL_RenderDrawLine(renderer,points[i-1].x, points[i-1].y, points[i].x, points[i].y);
    }

    SDL_RenderDrawLine(renderer, points[0].x, points[0].y,points[pointNbr-1].x, points[pointNbr-1].y);
}

void DrawFilledCircle(float centerX, float centerY, float r, std::size_t pointNbr)
{
    auto angleIncrement = (2.0f * MathUtility::Pi) / static_cast<float>(pointNbr);

    for (std::size_t i = 0; i < pointNbr; i++)
    {
        float angle = static_cast<float>(i) * angleIncrement;
        float x = centerX + (r * MathUtility::Cos(Radian(angle)));
        float y = centerY + (r * MathUtility::Sin(Radian(angle)));

        SDL_RenderDrawLineF(renderer, centerX, centerY, x, y);
    }
}