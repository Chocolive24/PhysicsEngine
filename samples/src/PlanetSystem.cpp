//
// Created by Olivier on 15.10.2023.
//

#include "Metrics.h"
#include "Random.h"
#include "PlanetSystem.h"

#include <iostream>

void PlanetSystem::Init(PhysicsEngine::World& world)
{
    constexpr Math::Vec2F centerOfScreen(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = PhysicsEngine::Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    _sun = {world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& body = world.GetBody(_sun.BodyRef);
    body = PhysicsEngine::Body(sunPos, Math::Vec2F::Zero(), 100.f);

    _planets.resize(StartPlanetNbr, CelestialBody());

    for (auto& planet : _planets)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(300.f, 600.f), Math::Random::Range(100.f, 500.f));
        Math::Vec2F rndPos = PhysicsEngine::Metrics::PixelsToMeters(rndScreenPos);

        planet = createPlanet(world, rndPos, Math::Random::Range(3.f, 10.f),
                              {0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                               255});
    }
}

void PlanetSystem::RunGameLoop(RenderingManager& renderingManager, InputsManager& inputManager,
                               PhysicsEngine::World& world, PhysicsEngine::Timer& timer)
{
    bool quit = false;

    while (!quit)
    {
        inputManager.HandleInputs(quit);

        if (inputManager.IsMouseButtonDown(SDL_BUTTON_LEFT))
        {
            auto mouseScreenPos = inputManager.MousePositionInPixels();

            constexpr float rangeVariation = 20.f;

            Math::Vec2F rndMousePos(Math::Random::Range(mouseScreenPos.X - rangeVariation,
                                               mouseScreenPos.X + rangeVariation),
                              Math::Random::Range(mouseScreenPos.Y - rangeVariation,
                                               mouseScreenPos.Y + rangeVariation));

            auto planet = createPlanet(world, PhysicsEngine::Metrics::PixelsToMeters(rndMousePos),
                                       Math::Random::Range(3.f, 10.f),
                                       {0, 0,
                                        static_cast<std::uint8_t>(Math::Random::Range(75, 255)),255});

            _planets.push_back(planet);
        }

        timer.Tick();

        CalculatePlanetMovements(world,timer.DeltaTime());

        RenderScreen(renderingManager, world);
    }
}

void PlanetSystem::CalculatePlanetMovements(PhysicsEngine::World& world, float deltaTime)
{
    for (auto& p : _planets)
    {
        auto& sunBody = world.GetBody(_sun.BodyRef);
        PhysicsEngine::Body& planetBody = world.GetBody(p.BodyRef);

        Math::Vec2F r = sunBody.Position() - planetBody.Position();

        float distance = r.Length();

        float forceMagnitude = G * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Math::Vec2F a = forceMagnitude * r.Normalized();

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

[[nodiscard]] CelestialBody PlanetSystem::createPlanet(PhysicsEngine::World& world, Math::Vec2F pos, float radius,
                                                       SDL_Color color) noexcept
{
    auto& sunBody = world.GetBody(_sun.BodyRef);
    CelestialBody p = {world.CreateBody(), radius, color };
    auto& pBody = world.GetBody(p.BodyRef);

    // Distance between the sun and the planet.
    Math::Vec2F r = sunBody.Position() - pos;
    float distance = r.Length();

    Math::Vec2F initVel = std::sqrt(G * (sunBody.Mass() / distance)) * Math::Vec2F(-r.Y, r.X).Normalized();

    pBody = PhysicsEngine::Body(pos, initVel, 10.f);

    _currentPlanetNbr++;

    return p;
}
