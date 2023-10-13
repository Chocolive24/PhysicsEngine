//
// Created by Olivier on 10.10.2023.
//

#include "Timer.h"
#include "Planet.h"
#include "Random.h"
#include "RenderingManager.h"
#include "InputManager.h"

#include <array>
#include <iostream>

void CalculatePlanetMovements(std::array<Planet, 20>& planets, Vec2F rotationCenter);
void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager,
                 std::array<Planet, 20>& planets, Vec2F rotationCenter);
void RenderScreen(RenderingManager& renderingManager, std::array<Planet, 20>& planets, Vec2F rotationCenter);

int main()
{
    RenderingManager renderingManager{};
    renderingManager.Init();

    InputManager inputManager{};

    Timer::Init();

    const Vec2F rotationCenter(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);

    std::array<Planet, 20> planets;

    for(auto& planet : planets)
    {
        Vec2F rndPos(Random::Range(400.f, 600.f), Random::Range(100.f, 500.f));
        Planet p(PhysicsEngine::Body(rndPos, Vec2F(Random::Range(100.f, 500.f), 0.f)),
                 Random::Range(3.f, 10.f));

        planet = p;
    }

    RunGameLoop(renderingManager, inputManager, planets, rotationCenter);

    renderingManager.UnInit();
    return 0;
}

void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager,
                 std::array<Planet, 20>& planets, Vec2F rotationCenter)
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        Timer::Tick();

        CalculatePlanetMovements(planets, rotationCenter);

        RenderScreen(renderingManager, planets, rotationCenter);
    }
}

void CalculatePlanetMovements(std::array<Planet, 20>& planets, Vec2F rotationCenter)
{
    for (auto& p : planets)
    {
        PhysicsEngine::Body& planetBody = p.GetBody();
        float planetSpeed = 100.f;

        // Radius of circle.
        Vec2F r = rotationCenter - planetBody.Position;

        // v = tangent of radius.
        planetBody.Velocity = Vec2F(-r.Y, r.X).Normalized() * planetSpeed;

        // a = v^2 / r
        Vec2F a = (planetBody.Velocity * planetBody.Velocity) / r.Length();

        planetBody.Velocity += a.Normalized() * planetSpeed * Timer::DeltaTime();

        planetBody.Position += planetBody.Velocity * Timer::DeltaTime();
    }
}

void RenderScreen(RenderingManager& renderingManager, std::array<Planet, 20>& planets, Vec2F rotationCenter)
{
    SDL_RenderClear(renderingManager.Renderer);

    constexpr SDL_Color sunColor{255, 0, 0, 255};

    SDL_SetRenderDrawColor(renderingManager.Renderer, sunColor.r, sunColor.g, sunColor.b, sunColor.a);

    renderingManager.DrawFilledCircle(rotationCenter.X, rotationCenter.Y, 5, 200);

    constexpr SDL_Color planetsColor{0, 0, 255, 255};

    SDL_SetRenderDrawColor(renderingManager.Renderer, planetsColor.r, planetsColor.g, planetsColor.b, planetsColor.a);

    for(auto& p : planets)
    {
        PhysicsEngine::Body planetBody = p.GetBody();

        renderingManager.DrawFilledCircle(planetBody.Position.X, planetBody.Position.Y, p.GetRadius(), 200);
    }

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};

    SDL_SetRenderDrawColor(renderingManager.Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);

    SDL_RenderPresent(renderingManager.Renderer);
}