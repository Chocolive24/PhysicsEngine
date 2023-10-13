//
// Created by Olivier on 10.10.2023.
//

#include <array>
#include <iostream>

#include "Body.h"
#include "Planet.h"
#include "Random.h"
#include "GraphicsManager.h"
#include "InputManager.h"

GraphicsManager graphicsManager;
InputManager inputManager;

unsigned long long Time = 0;

std::array<Planet, 20> planets;

const Vec2F RotationCenter(GraphicsManager::WindowWidth / 2.f, GraphicsManager::WindowHeight / 2.f);

void CalculatePlanetMovements(float deltaTime);
void RunGameLoop();
void RenderScreen();

int main()
{
    graphicsManager.Init();

    for(auto& planet : planets)
    {
        Vec2F rndPos(Random::Range(400.f, 600.f), Random::Range(100.f, 500.f));
        Planet p(PhysicsEngine::Body(rndPos, Vec2F(Random::Range(100.f, 500.f), 0.f)),
                 Random::Range(3.f, 10.f));

        planet = p;
    }

    Time = SDL_GetTicks64();

    RunGameLoop();

    graphicsManager.UnInit();
    return 0;
}

void RunGameLoop()
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        const float deltaTime = (static_cast<float>(SDL_GetTicks64() - Time)) / 1000.f;
        Time = SDL_GetTicks64();

        CalculatePlanetMovements(deltaTime);

        RenderScreen();
    }
}

void CalculatePlanetMovements(float deltaTime)
{
    for (auto& p : planets)
    {
        PhysicsEngine::Body& planetBody = p.GetBody();
        float planetSpeed = planetBody.Velocity.Length();

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
    SDL_RenderClear(graphicsManager.Renderer);

    constexpr SDL_Color sunColor{255, 0, 0, 255};

    SDL_SetRenderDrawColor(graphicsManager.Renderer, sunColor.r, sunColor.g, sunColor.b, sunColor.a);

    graphicsManager.DrawFilledCircle(RotationCenter.X, RotationCenter.Y, 5, 200);

    constexpr SDL_Color planetsColor{0, 0, 255, 255};

    SDL_SetRenderDrawColor(graphicsManager.Renderer, planetsColor.r, planetsColor.g, planetsColor.b, planetsColor.a);

    for(auto& p : planets)
    {
        PhysicsEngine::Body planetBody = p.GetBody();

        graphicsManager.DrawFilledCircle(planetBody.Position.X, planetBody.Position.Y, p.GetRadius(), 200);
    }

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};

    SDL_SetRenderDrawColor(graphicsManager.Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    SDL_RenderPresent(graphicsManager.Renderer);
}