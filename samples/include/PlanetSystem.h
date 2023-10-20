#pragma once

#include "Sample.h"

#include "SDL.h"

#include <array>

struct CelestialBody
{
    PhysicsEngine::BodyRef BodyRef;
    // In Pixels
    float Radius;
    SDL_Color Color;
};

class PlanetSystem : public Sample
{
private:
    std::vector<CelestialBody> _planets{};
    CelestialBody _sun{};

    bool _mustCreatePlanet = false;

    [[nodiscard]] CelestialBody createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept;
    void calculatePlanetMovements() noexcept;
    void drawCelestialBodies() noexcept;

public:
    static constexpr float G = 0.0667f;
    static constexpr std::size_t StartPlanetNbr = 200;

    explicit PlanetSystem() noexcept = default;

    void Init() noexcept override;
    void HandleInputs(SDL_Event event) noexcept override;
    void Update() noexcept override;
};