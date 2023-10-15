#pragma once

#include "Body.h"

struct CelestialBody
{
    PhysicsEngine::Body Body;
    float Radius;
};

class PlanetSystem
{
public:
    int PlanetCount = { 0 };
    std::vector<CelestialBody> Planets = {};
    CelestialBody Sun;

    PlanetSystem() noexcept = default;
};
