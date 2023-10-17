#pragma once

#include "World.h"
#include "RenderingManager.h"
#include "InputsManager.h"
#include "Timer.h"

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
public:
    static constexpr float G = 0.0667f;
    static constexpr std::size_t PlanetToCreate = 200;

private:
    std::array<CelestialBody, PlanetToCreate> _planets{};
    CelestialBody _sun{};

public:
    PlanetSystem() noexcept = default;

    void Init(PhysicsEngine::World& world);

    void CalculatePlanetMovements(PhysicsEngine::World& world, float deltaTime);
    void RunGameLoop(RenderingManager& renderingManager, InputsManager& inputManager, PhysicsEngine::World& world,
                     PhysicsEngine::Timer& timer);
    void RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world);
};