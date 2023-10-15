#pragma once

#include "Body.h"

namespace PhysicsEngine
{
    class World
    {
    public:
        std::vector<Body> Bodies = {};

        World() noexcept = default;
        World(int bodyCount) noexcept
        {
            Bodies.reserve(bodyCount);
        }

        void AddBody(Body& body) noexcept;
        void Update(float deltaTime) noexcept;
    };
}

