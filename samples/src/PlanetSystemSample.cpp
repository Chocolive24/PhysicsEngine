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

std::string PlanetSystemSample::InputText() const noexcept
{
    std::string_view description = R"(Inputs :
[Left-click] create planets)";
    return static_cast<std::string>(description);
}

void PlanetSystemSample::onInit() noexcept
{
    _bodyRefs.reserve(_startBodyNbr);
    _graphicCircles.reserve(_startBodyNbr);

    constexpr Math::Vec2F centerOfScreen(AppWindow::WindowWidth / 2.f, AppWindow::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = Metrics::PixelsToMeters(centerOfScreen);

    // Create the sun.
    const auto sunBodyRef = _world.CreateBody();
    auto& sunBody = _world.GetBody(sunBodyRef);
    sunBody.SetPosition(sunPos);
    sunBody.SetMass(100.f);

    _bodyRefs.push_back(sunBodyRef);
    _graphicCircles.push_back(_sunGraphicCircle);

    for (int i = 0; i < _startPlanetNbr; i++)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(300.f, 600.f), Math::Random::Range(100.f, 500.f));
        Math::Vec2F rndPos = Metrics::PixelsToMeters(rndScreenPos);

        createPlanet(rndPos,
            Math::Random::Range(3.f, 10.f),
            { 0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)), 255 });
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
            _world.GetBody(_bodyRefs[0]).Position()).Length() > Metrics::PixelsToMeters(rangeVariation))
        {
            Math::Vec2I rndMousePos(Math::Random::Range(mousePosition.X - rangeVariation,
                mousePosition.X + rangeVariation),
                Math::Random::Range(mousePosition.Y - rangeVariation,
                    mousePosition.Y + rangeVariation));

            auto rndMousePosInMeters = Metrics::PixelsToMeters(
                static_cast<Math::Vec2F>(rndMousePos));

            createPlanet(rndMousePosInMeters,
                Math::Random::Range(3.f, 10.f),
                { 0, 0, static_cast<std::uint8_t>(Math::Random::Range(75, 255)), 255 });
        }
    }

    calculatePlanetMovements();
}

void PlanetSystemSample::onRender() noexcept
{
    for (const auto& bodyRef : _bodyRefs)
    {
        const auto pos = _world.GetBody(bodyRef).Position();
        const auto screenPos = Metrics::MetersToPixels(pos);

        const auto& graphicCircle = _graphicCircles[bodyRef.Index];

        GraphicGeometry::Circle(screenPos,
            graphicCircle.first,
            GraphicGeometry::CircleSegmentCount,
            graphicCircle.second);
    }
}

void PlanetSystemSample::onDeinit() noexcept
{
    _graphicCircles.clear();
}

[[nodiscard]] void PlanetSystemSample::createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept
{
    const auto planetRef = _world.CreateBody();
    auto& planetBody = _world.GetBody(planetRef);

    // The sun is always at index 0 in the world.
    const auto sunBody = _world.GetBody(PhysicsEngine::BodyRef{ 0, 0 });

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

    Math::Vec2F orbitalVelocity = std::sqrt(_g * (sunBody.Mass() / distance)) * Math::Vec2F(-r.Y, r.X).Normalized();

    planetBody.SetPosition(correctedPos);
    planetBody.SetVelocity(orbitalVelocity);
    planetBody.SetMass(_planetMass);

    _bodyRefs.push_back(planetRef);
    _graphicCircles.push_back(std::make_pair(radius, color));
}

void PlanetSystemSample::calculatePlanetMovements() noexcept
{
    const auto& sunBody = _world.GetBody(_bodyRefs[0]);

    for (std::size_t i = 1; i < _bodyRefs.size(); i++)
    {
       auto& planetBody = _world.GetBody(_bodyRefs[i]);

        Math::Vec2F r = sunBody.Position() - planetBody.Position();

        float distance = r.Length();

        if (distance <= 0.01) continue;

        float forceMagnitude = _g * (planetBody.Mass() * sunBody.Mass() / (distance * distance));
        Math::Vec2F a = forceMagnitude * r.Normalized();

        planetBody.ApplyForce(a);
    }
}