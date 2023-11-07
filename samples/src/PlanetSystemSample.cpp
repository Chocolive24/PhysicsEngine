//
// Created by Olivier on 15.10.2023.
//

#include "GraphicGeometry.h"
#include "Metrics.h"
#include "Random.h"
#include "PlanetSystemSample.h"

#include <iostream>

std::string PlanetSystemSample::Description() const noexcept
{
    std::string_view description = R"(This sample uses Newton's gravitational law to create a simplified simulation of planets (blue circles) orbiting a sun (red circle). 
Initially, the planets have a pre-calculated orbital velocity.
Then, the force of gravity constantly pulls the planets towards the sun. 
The sum of these forces creates the orbital motion.)";
    return static_cast<std::string>(description);
}

void PlanetSystemSample::onInit() noexcept
{
    constexpr Math::Vec2F centerOfScreen(Window::WindowWidth / 2.f, Window::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    _sun = { _world.CreateBody(), 5.f, {255, 0, 0, 255} };
    auto& body = _world.GetBody(_sun.BodyRef);
    body = PhysicsEngine::Body(sunPos, Math::Vec2F::Zero(), 100.f);

    _planets.resize(StartPlanetNbr, CelestialBody());

    for (auto& planet : _planets)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(300.f, 600.f), Math::Random::Range(100.f, 500.f));
        Math::Vec2F rndPos = Metrics::PixelsToMeters(rndScreenPos);

        planet = createPlanet(rndPos, Math::Random::Range(3.f, 10.f),
            { 0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
             255 });
    }
}

void PlanetSystemSample::onHandleInputs(const SDL_Event event, const bool isMouseOnAnImGuiWindow) noexcept
{
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            _mustCreatePlanet = !isMouseOnAnImGuiWindow;
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

void PlanetSystemSample::onUpdate() noexcept
{
    if (_mustCreatePlanet)
    {
        Math::Vec2I mousePosition;
        SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

        constexpr int rangeVariation = 20;

        if ((Metrics::PixelsToMeters(static_cast<Math::Vec2F>(mousePosition)) -
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
                { 0,
                 0,
                 static_cast<std::uint8_t>(Math::Random::Range(75, 255)),
                 255 });

            _planets.push_back(planet);
        }
    }

    calculatePlanetMovements();
}

void PlanetSystemSample::onRender() noexcept
{
    // Draw the sun.
    auto sunBodyPos = _world.GetBody(_sun.BodyRef).Position();
    auto sunScreenPos = Metrics::MetersToPixels(sunBodyPos);
    GraphicGeometry::Circle(sunScreenPos, _sun.Radius, 15, _sun.Color);

    // Draw the planets.
    for (auto& p : _planets)
    {
        auto planetBodyPos = _world.GetBody(p.BodyRef).Position();
        auto planetScreenPos = Metrics::MetersToPixels(planetBodyPos);
        GraphicGeometry::Circle(planetScreenPos, p.Radius, GraphicGeometry::CircleSegmentCount, p.Color);
    }
}

void PlanetSystemSample::onDeinit() noexcept
{
    _planets.clear();
}

[[nodiscard]] CelestialBody PlanetSystemSample::createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept
{
    const auto sunBody = _world.GetBody(_sun.BodyRef);
    CelestialBody p = { _world.CreateBody(), radius, color };
    auto& pBody = _world.GetBody(p.BodyRef);

    // Distance between the sun and the planet.
    Math::Vec2F r = sunBody.Position() - pos;
    float distance = r.Length();

    auto correctedPos = pos;

    if (distance < 0.01f) 
    {
        correctedPos = sunBody.Position() + Math::Vec2F::One();
        r = sunBody.Position() - correctedPos;
        distance = r.Length();
    }

    Math::Vec2F initVel = std::sqrt(G * (sunBody.Mass() / distance)) * Math::Vec2F(-r.Y, r.X).Normalized();

    pBody = PhysicsEngine::Body(correctedPos, initVel, 10.f);

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

        if (distance <= 0.01) continue;

        float forceMagnitude = G * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Math::Vec2F a = forceMagnitude * r.Normalized();

        planetBody.ApplyForce(a);
    }
}