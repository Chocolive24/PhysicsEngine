#pragma once

#include "World.h"
#include "RenderingManager.h"
#include "InputsManager.h"
#include "../../common/include/Timer.h"

#include "SDL.h"

#include <array>

struct CelestialBody
{
    PhysicsEngine::BodyRef BodyRef;
    // In Pixels
    float Radius;
    SDL_Color Color;
};

class PlanetSystem
{
private:
    PhysicsEngine::World _world;

    std::vector<CelestialBody> _planets{};
    CelestialBody _sun{};

    [[nodiscard]] CelestialBody createPlanet(Math::Vec2F pos, float radius, SDL_Color color) noexcept;
    void calculatePlanetMovements() noexcept;
    void renderScreen(RenderingManager& renderingManager) noexcept;

public:
    static constexpr float G = 0.0667f;
    static constexpr std::size_t StartPlanetNbr = 200;

    constexpr PlanetSystem() noexcept = default;

    void Init();
    void RunGameLoop(RenderingManager& renderingManager,
                     InputsManager& inputsManager,
                     PhysicsEngine::Timer& timer);
};