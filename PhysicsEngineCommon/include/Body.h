#pragma once

#include "Vec2.h"

namespace PhysicsEngine
{
    class Body
    {
    public:
        Vec2F Position = {0.f, 0.f};
        Vec2F Velocity = {0.f ,0.f};

        constexpr Body() noexcept = default;
        constexpr Body(Vec2F pos, Vec2F vel) noexcept : Position(pos), Velocity(vel){}
    };
}