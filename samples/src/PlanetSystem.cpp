//
// Created by Olivier on 15.10.2023.
//

#include "Random.h"
#include "../include/PlanetSystem.h"

void PlanetSystem::Init(PhysicsEngine::World& world)
{
    const Vec2F rotationCenter(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);

    // Create the sun.
    _sun = {world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& sunBody = world.GetBody(_sun.BodyRef);
    sunBody = PhysicsEngine::Body(rotationCenter, Vec2F::Zero(), 100000.f);

    for (auto& planet : _planets)
    {
        auto theSun = world.GetBody(_sun.BodyRef);
        CelestialBody p = {world.CreateBody(), Random::Range(3.f, 10.f), {0, 0, 255, 255}};
        auto& pBody = world.GetBody(p.BodyRef);

        Vec2F rndPos(Random::Range(300.f, 600.f), Random::Range(100.f, 500.f));

        // Distance between the sun and the planet.
        Vec2F r = theSun.Position() - rndPos;
        float distance = r.Length();

        Vec2F initVel = std::sqrt(G * (theSun.Mass() / distance)) * Vec2F(-r.Y, r.X).Normalized();

        pBody = PhysicsEngine::Body(rndPos, initVel, 100.f);

        planet = p;
    }
}

void PlanetSystem::RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager, PhysicsEngine::World& world,
                                Timer& timer)
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

        planetBody.AddForce(a);
    }

    world.Update(deltaTime);
}

void PlanetSystem::RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world)
{
    constexpr SDL_Color backgroundColor{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderingManager.Renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a);
    SDL_RenderClear(renderingManager.Renderer);

    // Draw the sun.
    SDL_SetRenderDrawColor(renderingManager.Renderer, _sun.Color.r, _sun.Color.g, _sun.Color.b, _sun.Color.a);
    auto sunBodyPos = world.GetBody(_sun.BodyRef).Position();
    renderingManager.DrawFilledCircle(sunBodyPos.X, sunBodyPos.Y, _sun.Radius, 200, _sun.Color);

    // Draw the planets.
    for(auto& p : _planets)
    {
        SDL_SetRenderDrawColor(renderingManager.Renderer, p.Color.r, p.Color.g, p.Color.b, p.Color.a);
        auto planetBodyPos = world.GetBody(p.BodyRef).Position();
        renderingManager.DrawFilledCircle(planetBodyPos.X, planetBodyPos.Y, p.Radius, 200, p.Color);
    }

    SDL_RenderPresent(renderingManager.Renderer);
}
