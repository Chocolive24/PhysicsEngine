#pragma once

/**
 * @headerfile Body class represents a physical body with attributes such as position, velocity, mass, and forces
 * applied to it.
 * @author Olivier
 */

#include "Vec2.h"

namespace PhysicsEngine
{
    class Body
    {
    private:
        Vec2F _position = Vec2F::Zero();

        /**
         * @brief In meters per second.
         */
        Vec2F _velocity = Vec2F::Zero();

        /**
         * @brief In kilogram.
         * @note The body has a -1 mass by default, which means that it is not valid.
         */
        float _mass = -1.f;

        /**
         * @brief Sum of the forces applied to the body.
         */
        Vec2F _forces = Vec2F::Zero();

    public:
        constexpr Body() noexcept = default;
        constexpr Body(Vec2F pos, Vec2F vel, float mass) noexcept : _position(pos), _velocity(vel), _mass(mass){}

        /**
         * @brief ApplyForce is a method that applies a force to the body and adds it to the sum of the body's forces.
         */
        constexpr void ApplyForce(Vec2F force) noexcept { _forces += force; };

        [[nodiscard]] constexpr Vec2F Position() const noexcept { return _position; }
        void constexpr SetPosition(const Vec2F newPosition) noexcept { _position = newPosition; }

        [[nodiscard]] constexpr Vec2F Velocity() const noexcept { return _velocity; }
        void constexpr SetVelocity(const Vec2F newVelocity) noexcept { _velocity = newVelocity; }

        [[nodiscard]] constexpr float Mass() const noexcept { return _mass; }
        void constexpr SetMass(const float newMass) noexcept { _mass = newMass; }

        /**
         * @return Sum of the forces applied to the body.
         */
        [[nodiscard]] constexpr Vec2F Forces() const noexcept { return _forces; }
        void constexpr SetForces(const Vec2F force) noexcept { _forces = force; }

        /**
         * @return If the mass is greater than 0.
         */
        [[nodiscard]] constexpr bool IsValid() const noexcept { return _mass > 0; }
    };
}