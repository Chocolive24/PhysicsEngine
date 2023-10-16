#pragma once

#include "World.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "Timer.h"

#include "SDL.h"

#include <array>

struct CelestialBody
{
    PhysicsEngine::BodyRef BodyRef;
    float Radius;
    SDL_Color Color;
};

class PlanetSystem
{
public:
    static constexpr float G = 100.f;
    static constexpr std::size_t PlanetToCreate = 200;

private:
    std::array<CelestialBody, PlanetToCreate> _planets{};
    CelestialBody _sun{};

public:
    PlanetSystem() noexcept = default;

    void Init(PhysicsEngine::World& world);

    void CalculatePlanetMovements(PhysicsEngine::World& world, float deltaTime);
    void RunGameLoop(RenderingManager& renderingManager, InputManager& inputManager, PhysicsEngine::World& world,
                     Timer& timer);
    void RenderScreen(RenderingManager& renderingManager, PhysicsEngine::World& world);
};
