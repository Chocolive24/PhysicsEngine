//
// Created by Olivier on 15.10.2023.
//

#include "../../common/include/Metrics.h"
#include "Random.h"
#include "PlanetSystem.h"

#include <iostream>

void PlanetSystem::Init()
{
    _world.Init(PlanetSystem::StartPlanetNbr + 1);

    constexpr Math::Vec2F centerOfScreen(RenderingManager::WindowWidth / 2.f, RenderingManager::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = PhysicsEngine::Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    _sun = {_world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& body = _world.GetBody(_sun.BodyRef);
    body = PhysicsEngine::Body(sunPos, Math::Vec2F::Zero(), 100.f);

    _planets.resize(StartPlanetNbr, CelestialBody());

    for (auto& planet : _planets)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(300.f, 600.f), Math::Random::Range(100.f, 500.f));
        Math::Vec2F rndPos = PhysicsEngine::Metrics::PixelsToMeters(rndScreenPos);

        planet = createPlanet(rndPos, Math::Random::Range(3.f, 10.f),
                              {0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                               255});
    }
}

void PlanetSystem::RunGameLoop(RenderingManager& renderingManager,
                               InputsManager& inputsManager,
                               PhysicsEngine::Timer& timer)
{
    SDL_Event event;
    bool quit = false;
    bool mouseDown = false;

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseDown = true;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        mouseDown = false;
                    }
                    break;
            }
        }

        if (mouseDown)
        {
            Math::Vec2I mousePosition;
            SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

            constexpr int rangeVariation = 20;

            Math::Vec2I rndMousePos(Math::Random::Range(mousePosition.X - rangeVariation,
                                                        mousePosition.X + rangeVariation),
                                    Math::Random::Range(mousePosition.Y - rangeVariation,
                                                        mousePosition.Y + rangeVariation));

            auto rndMousePosInMeters = PhysicsEngine::Metrics::PixelsToMeters(
                    static_cast<Math::Vec2F>(rndMousePos));

            auto planet = createPlanet(rndMousePosInMeters,
                                       Math::Random::Range(3.f, 10.f),
                                       {0,
                                        0,
                                        static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                                        255});

            _planets.push_back(planet);
        }

        timer.Tick();
        const auto deltaTime = timer.DeltaTime();

        calculatePlanetMovements();

        _world.Update(deltaTime);

        renderScreen(renderingManager);
    }
}

void PlanetSystem::calculatePlanetMovements() noexcept
{
    for (auto& p : _planets)
    {
        auto& sunBody = _world.GetBody(_sun.BodyRef);
        PhysicsEngine::Body& planetBody = _world.GetBody(p.BodyRef);

        Math::Vec2F r = sunBody.Position() - planetBody.Position();

        float distance = r.Length();

        float forceMagnitude = G * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Math::Vec2F a = forceMagnitude * r.Normalized();

        planetBody.ApplyForce(a);
    }
}

void PlanetSystem::renderScreen(RenderingManager& renderingManager) noexcept
{
    SDL_RenderClear(renderingManager.Renderer());
    renderingManager.ClearGeometry();

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};
    SDL_SetRenderDrawColor(renderingManager.Renderer(), backgroundColor.r, backgroundColor.g, backgroundColor.b,
                           backgroundColor.a);

    // Draw the sun.
    auto sunBodyPos = _world.GetBody(_sun.BodyRef).Position();
    auto sunScreenPos = PhysicsEngine::Metrics::MetersToPixels(sunBodyPos);
    renderingManager.DrawCircle(sunScreenPos, _sun.Radius, 40, _sun.Color);

    // Draw the planets.
    for(auto& p : _planets)
    {
        auto planetBodyPos = _world.GetBody(p.BodyRef).Position();
        auto planetScreenPos = PhysicsEngine::Metrics::MetersToPixels(planetBodyPos);
        renderingManager.DrawCircle(planetScreenPos, p.Radius, 40, p.Color);
    }

    SDL_RenderGeometry(renderingManager.Renderer(), nullptr, renderingManager._vertices.data(),
                       static_cast<int>(renderingManager._vertices.size()),renderingManager._indices.data(),
                       static_cast<int>(renderingManager._indices.size()));

    SDL_RenderPresent(renderingManager.Renderer());
}

[[nodiscard]] CelestialBody PlanetSystem::createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept
{
    auto& sunBody = _world.GetBody(_sun.BodyRef);
    CelestialBody p = {_world.CreateBody(), radius, color };
    auto& pBody = _world.GetBody(p.BodyRef);

    // Distance between the sun and the planet.
    Math::Vec2F r = sunBody.Position() - pos;
    float distance = r.Length();

    Math::Vec2F initVel = std::sqrt(G * (sunBody.Mass() / distance)) * Math::Vec2F(-r.Y, r.X).Normalized();

    pBody = PhysicsEngine::Body(pos, initVel, 10.f);

    return p;
}