//
// Created by Olivier on 15.10.2023.
//

#include "DrawableGeometry.h"
#include "Metrics.h"
#include "Random.h"
#include "PlanetSystemSample.h"

#include <iostream>

void PlanetSystemSample::Init() noexcept
{
    Sample::Init();

    constexpr Math::Vec2F centerOfScreen(Window::WindowWidth / 2.f, Window::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    _sun = {_world.CreateBody(), 5.f, {255, 0, 0, 255}};
    auto& body = _world.GetBody(_sun.BodyRef);
    body = PhysicsEngine::Body(sunPos, Math::Vec2F::Zero(), 100.f);

    _planets.resize(StartPlanetNbr, CelestialBody());

    for (auto& planet : _planets)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(300.f, 600.f), Math::Random::Range(100.f, 500.f));
        Math::Vec2F rndPos = Metrics::PixelsToMeters(rndScreenPos);

        planet = createPlanet(rndPos, Math::Random::Range(3.f, 10.f),
                              {0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                               255});
    }
}

void PlanetSystemSample::HandleInputs(const SDL_Event event) noexcept
{
    switch (event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                _mustCreatePlanet = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                _mustCreatePlanet = false;
            }
            break;
    }
}


void PlanetSystemSample::Update() noexcept
{
    if (_mustCreatePlanet)
    {
        Math::Vec2I mousePosition;
        SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

        constexpr int rangeVariation = 20;

        if((Metrics::PixelsToMeters(static_cast<Math::Vec2F>(mousePosition)) -
        _world.GetBody(_sun.BodyRef).Position()).Length() > Metrics::PixelsToMeters(rangeVariation))
        {
            Math::Vec2I rndMousePos(Math::Random::Range(mousePosition.X - rangeVariation,
                                                        mousePosition.X + rangeVariation),
                                    Math::Random::Range(mousePosition.Y - rangeVariation,
                                                        mousePosition.Y + rangeVariation));

            auto rndMousePosInMeters = Metrics::PixelsToMeters(
                    static_cast<Math::Vec2F>(rndMousePos));

            auto planet = createPlanet(rndMousePosInMeters,
                                       Math::Random::Range(3.f, 10.f),
                                       {0,
                                        0,
                                        static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                                        255});

            _planets.push_back(planet);
        }
    }

    _timer.Tick();
    const auto deltaTime = _timer.DeltaTime();

    calculatePlanetMovements();

    _world.Update(deltaTime);

    drawCelestialBodies();
}

[[nodiscard]] CelestialBody PlanetSystemSample::createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept
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

void PlanetSystemSample::calculatePlanetMovements() noexcept
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

void PlanetSystemSample::drawCelestialBodies() noexcept
{
    // Draw the sun.
    auto sunBodyPos = _world.GetBody(_sun.BodyRef).Position();
    auto sunScreenPos = Metrics::MetersToPixels(sunBodyPos);
    DrawableGeometry::Circle(sunScreenPos, _sun.Radius, 15, _sun.Color);

    // Draw the planets.
    for(auto& p : _planets)
    {
        auto planetBodyPos = _world.GetBody(p.BodyRef).Position();
        auto planetScreenPos = Metrics::MetersToPixels(planetBodyPos);
        DrawableGeometry::Circle(planetScreenPos, p.Radius, 15, p.Color);
    }
}

void PlanetSystemSample::Deinit() noexcept
{
    Sample::Deinit();

    _planets.clear();
}
