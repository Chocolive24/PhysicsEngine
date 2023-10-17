//
// Created by Olivier on 15.10.2023.
//

#include <iostream>
#include "Metrics.h"
#include "Random.h"
#include "PlanetSystem.h"

void PlanetSystem::Init(PhysicsEngine::World& world)
{
    const Vec2F centerOfScreen(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);
    const Vec2F sunPos = PhysicsEngine::Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    _sun = {world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& body = world.GetBody(_sun.BodyRef);
    body = PhysicsEngine::Body(sunPos, Vec2F::Zero(), 100.f);

    for (auto& planet : _planets)
    {
        auto& sunBody = world.GetBody(_sun.BodyRef);
        CelestialBody p = {world.CreateBody(), Random::Range(3.f, 10.f),
                           {0, 0, static_cast<std::uint8_t>(Random::Range(75, 255)), 255}};
        auto& pBody = world.GetBody(p.BodyRef);

        Vec2F rndScreenPos(Random::Range(300.f, 600.f), Random::Range(100.f, 500.f));
        Vec2F rndPos = PhysicsEngine::Metrics::PixelsToMeters(rndScreenPos);

        // Distance between the sun and the planet.
        Vec2F r = sunBody.Position() - rndPos;
        float distance = r.Length();

        Vec2F initVel = std::sqrt(G * (sunBody.Mass() / distance)) * Vec2F(-r.Y, r.X).Normalized();

        pBody = PhysicsEngine::Body(rndPos, initVel, 10.f);

        planet = p;
    }
}

void PlanetSystem::RunGameLoop(RenderingManager& renderingManager, InputsManager& inputManager,
                               PhysicsEngine::World& world, PhysicsEngine::Timer& timer)
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        timer.Tick();

        this->CalculatePlanetMovements(world,timer.DeltaTime());

        this->RenderScreen(renderingManager, world);
    }
}

void PlanetSystem::CalculatePlanetMovements(PhysicsEngine::World& world, float deltaTime)
{
    for (auto& p : _planets)
    {
        auto& sunBody = world.GetBody(_sun.BodyRef);
        PhysicsEngine::Body& planetBody = world.GetBody(p.BodyRef);

        Vec2F r = sunBody.Position() - planetBody.Position();

        float distance = r.Length();

        float forceMagnitude = G * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Vec2F a = forceMagnitude * r.Normalized();

        planetBody.ApplyForce(a);
    }

    world.Update(deltaTime);
}

void PlanetSystem::RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world)
{
    SDL_RenderClear(renderingManager.Renderer());

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderingManager.Renderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a);

    // Draw the sun.
    auto sunBodyPos = world.GetBody(_sun.BodyRef).Position();
    auto sunScreenPos = PhysicsEngine::Metrics::MetersToPixels(sunBodyPos);
    renderingManager.DrawCircle(sunScreenPos, _sun.Radius, 50, _sun.Color);

    // Draw the planets.
    for(auto& p : _planets)
    {
        auto planetBodyPos = world.GetBody(p.BodyRef).Position();
        auto planetScreenPos = PhysicsEngine::Metrics::MetersToPixels(planetBodyPos);
        renderingManager.DrawCircle(planetScreenPos, p.Radius, 50, p.Color);
    }

    SDL_RenderPresent(renderingManager.Renderer());
}
