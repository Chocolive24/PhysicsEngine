//
// Created by Olivier on 10.10.2023.
//

#include "Timer.h"
#include "Planet.h"
#include "Random.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "World.h"

#include <array>
#include <iostream>

constexpr float G = 100.f;
constexpr std::size_t planetToCreate = 10;

struct CelestialBody
{
    PhysicsEngine::BodyRef BodyRef;
    float Radius;
    SDL_Color Color;
};

void CalculatePlanetMovements(PhysicsEngine::World& world, std::array<CelestialBody, planetToCreate>& planets,
                              CelestialBody sun);
void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager, PhysicsEngine::World& world,
                 std::array<CelestialBody, planetToCreate>& planets, CelestialBody sun);
void RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world,
                  std::array<CelestialBody, planetToCreate>& planets, CelestialBody sun);

int main()
{
    RenderingManager renderingManager{};
    renderingManager.Init();

    InputManager inputManager{};

    Timer::Init();

    PhysicsEngine::World world;
    world.Init(5);

    const Vec2F rotationCenter(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);

    // Create the sun once outside the loop.
    CelestialBody sun = {world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& sunBody = world.GetBody(sun.BodyRef);
    sunBody = PhysicsEngine::Body(rotationCenter, Vec2F::Zero(), 100000.f);

    std::array<CelestialBody, planetToCreate> planets{};

    for (auto& planet : planets)
    {
        CelestialBody p = {world.CreateBody(), Random::Range(3.f, 10.f), {0, 0, 255, 255}};
        auto& pBody = world.GetBody(p.BodyRef);

        Vec2F rndPos(Random::Range(300.f, 600.f), Random::Range(100.f, 500.f));

        // Distance between the sun and the planet.
        Vec2F r = sunBody.Position() - rndPos;

        std::cout << sunBody.Position().X << "\n";

        float distance = r.Length();
        Vec2F initVel = std::sqrt(G * (sunBody.Mass() / distance)) * Vec2F(-r.Y, r.X).Normalized();

        pBody = PhysicsEngine::Body(rndPos, initVel, 100.f);

        planet = p;
    }


    RunGameLoop(renderingManager, inputManager, world, planets, sun);

    renderingManager.UnInit();
    return 0;
}

void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager, PhysicsEngine::World& world,
                 std::array<CelestialBody, planetToCreate>& planets, CelestialBody sun)
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        Timer::Tick();

        CalculatePlanetMovements(world,planets, sun);

        RenderScreen(renderingManager, world, planets, sun);
    }
}

void CalculatePlanetMovements(PhysicsEngine::World& world,std::array<CelestialBody, planetToCreate>& planets,
                              CelestialBody sun)
{
    for (auto& p : planets)
    {
        auto& sunBody = world.GetBody(sun.BodyRef);
        PhysicsEngine::Body& planetBody = world.GetBody(p.BodyRef);

        // Vecteur de distance entre la planète et le soleil.
        Vec2F r = sunBody.Position() - planetBody.Position();

        float distance = r.Length();

        float forceMagnitude = G * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Vec2F a = forceMagnitude * r.Normalized();

        planetBody.AddForce(a);
    }

    world.Update(Timer::DeltaTime());
}

void RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world,
                  std::array<CelestialBody, planetToCreate>& planets, CelestialBody sun)
{
    SDL_RenderClear(renderingManager.Renderer);

    // Draw the sun.
    SDL_SetRenderDrawColor(renderingManager.Renderer, sun.Color.r, sun.Color.g, sun.Color.b, sun.Color.a);
    auto sunBodyPos = world.GetBody(sun.BodyRef).Position();
    renderingManager.DrawFilledCircle(sunBodyPos.X, sunBodyPos.Y, sun.Radius, 200);

    // Draw the planets.
    for(auto& p : planets)
    {
        SDL_SetRenderDrawColor(renderingManager.Renderer, p.Color.r, p.Color.g, p.Color.b, p.Color.a);
        auto planetBodyPos = world.GetBody(p.BodyRef).Position();
        renderingManager.DrawFilledCircle(planetBodyPos.X, planetBodyPos.Y, p.Radius, 200);
    }

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderingManager.Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a);

    SDL_RenderPresent(renderingManager.Renderer);
}