#pragma once

#include "Vec2.h"

#include <vector>

namespace PhysicsEngine
{
    class Body
    {
    private:
        Vec2F _position = Vec2F::Zero();
        Vec2F _velocity = Vec2F::Zero();
        // In kilogram
        float _mass = -1.f;
        // Sum of the forces applied to the body
        Vec2F _forces = Vec2F::Zero();

    public:
        constexpr Body() noexcept = default;
        constexpr Body(Vec2F pos, Vec2F vel, float mass) noexcept : _position(pos), _velocity(vel), _mass(mass){}

        void AddForce(Vec2F force) noexcept;

        [[nodiscard]] Vec2F Position() const noexcept { return _position; }
        void SetPosition(Vec2F newPosition) noexcept { _position = newPosition; }

        [[nodiscard]] Vec2F Velocity() const noexcept { return _velocity; }
        void SetVelocity(Vec2F newVelocity) noexcept { _velocity = newVelocity; }

        [[nodiscard]] float Mass() const noexcept { return _mass; }
        void SetMass(float newMass) noexcept { _mass = newMass; }

        [[nodiscard]] Vec2F Forces() const noexcept { return _forces; }
        void SetForces(Vec2F force) noexcept { _forces = force; }

        [[nodiscard]] bool IsValid() const noexcept { return _mass > 0; }
    };
}