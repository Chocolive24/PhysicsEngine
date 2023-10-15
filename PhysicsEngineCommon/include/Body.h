#pragma once

#include "Vec2.h"

#include <vector>

namespace PhysicsEngine
{
    class Body
    {
    private:
        Vec2F _forces = Vec2F::Zero();
    public:
        Vec2F Position = Vec2F::Zero();
        Vec2F Velocity = Vec2F::Zero();
        // In kilogram
        float Mass = 0.f;

        constexpr Body() noexcept = default;
        constexpr Body(Vec2F pos, Vec2F vel, float mass) noexcept : Position(pos), Velocity(vel), Mass(mass){}

        void AddForce(Vec2F force) noexcept;

        [[nodiscard]] constexpr Vec2F Forces() const noexcept { return _forces; }
        void SetForces(Vec2F force) noexcept { _forces = force; }
    };
}