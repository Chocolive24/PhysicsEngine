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

void CalculatePlanetMovements(std::array<Planet, 20>& planets, PhysicsEngine::Body sun);
void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager,
                 std::array<Planet, 20>& planets, PhysicsEngine::Body sun);
void RenderScreen(RenderingManager& renderingManager, std::array<Planet, 20>& planets, PhysicsEngine::Body sun);

constexpr float G = 100.f;

int main()
{
    RenderingManager renderingManager{};
    renderingManager.Init();

    InputManager inputManager{};

    Timer::Init();

    const Vec2F rotationCenter(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);

    PhysicsEngine::Body sun(rotationCenter, Vec2F::Zero(), 100000.f);

    std::array<Planet, 20> planets;

    for(auto& planet : planets)
    {
        Vec2F rndPos(Random::Range(400.f, 600.f), Random::Range(100.f, 500.f));

        // Vecteur de distance entre la planète et le soleil.
        Vec2F r = sun.Position - rndPos;

        float distance = r.Length();

        Vec2F initVel = std::sqrt(G * (sun.Mass / distance)) * Vec2F(-r.Y, r.X).Normalized();

        Planet p(PhysicsEngine::Body(rndPos, initVel, 100.f),
                 Random::Range(3.f, 10.f));

        planet = p;
    }

    RunGameLoop(renderingManager, inputManager, planets, sun);

    renderingManager.UnInit();
    return 0;
}

void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager,
                 std::array<Planet, 20>& planets, PhysicsEngine::Body sun)
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        Timer::Tick();

        CalculatePlanetMovements(planets, sun);

        RenderScreen(renderingManager, planets, sun);
    }
}

void CalculatePlanetMovements(std::array<Planet, 20>& planets, PhysicsEngine::Body sun)
{
    for (auto& p : planets)
    {
        PhysicsEngine::Body& planetBody = p.GetBody();

        // Vecteur de distance entre la planète et le soleil.
        Vec2F r = sun.Position - planetBody.Position;

        float distance = r.Length();

        float forceMagnitude = G * (sun.Mass / (distance * distance));
        Vec2F a = forceMagnitude * r.Normalized();

        // Mise à jour de la vitesse et de la position de la planète.
        planetBody.Velocity += a * Timer::DeltaTime();
        planetBody.Position += planetBody.Velocity * Timer::DeltaTime();
    }
}

void RenderScreen(RenderingManager& renderingManager, std::array<Planet, 20>& planets, PhysicsEngine::Body sun)
{
    SDL_RenderClear(renderingManager.Renderer);

    constexpr SDL_Color sunColor{255, 0, 0, 255};

    SDL_SetRenderDrawColor(renderingManager.Renderer, sunColor.r, sunColor.g, sunColor.b, sunColor.a);

    renderingManager.DrawFilledCircle(sun.Position.X, sun.Position.Y, 5, 200);

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