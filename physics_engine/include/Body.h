#pragma once

/**
 * @headerfile Body is a class that represents a physical body with attributes such as position, velocity, mass
 * and forces applied to it.
 * @author Olivier Pachoud
 */

#include "Vec2.h"

namespace PhysicsEngine
{
    class Body
    {
    private:
        Math::Vec2F _position = Math::Vec2F::Zero();
        Math::Vec2F _velocity = Math::Vec2F::Zero();
        float _mass = -1.f;
        Math::Vec2F _forces = Math::Vec2F::Zero();

    public:
        constexpr Body() noexcept = default;
        constexpr Body(Math::Vec2F pos, Math::Vec2F vel, float mass) noexcept
        {
            _position = pos;
            _velocity = vel;
            _mass = mass;
        }

        /**
         * @brief Position is a method that gives the position of the body.
         * @return The position of the body.
         */
        [[nodiscard]] constexpr Math::Vec2F Position() const noexcept { return _position; }

        /**
         * @brief SetPosition is a method that replaces the current position of the body with the new position
         * given in parameter.
         * @param newPosition The new position for the body.
         */
        void constexpr SetPosition(const Math::Vec2F newPosition) noexcept { _position = newPosition; }

        /**
         * @brief Velocity is a method that gives the velocity of the body.
         * @return The velocity of the body.
         */
        [[nodiscard]] constexpr Math::Vec2F Velocity() const noexcept { return _velocity; }

        /**
         * @brief SetVelocity is a method that replaces the current velocity of the body with the new velocity
         * given in parameter.
         * @param newVelocity The new velocity for the body.
         */
        void constexpr SetVelocity(const Math::Vec2F newVelocity) noexcept { _velocity = newVelocity; }

        /**
         * @brief Mass is a method that gives the mass of the body.
         * @return The mass of the body.
         */
        [[nodiscard]] constexpr float Mass() const noexcept { return _mass; }

        /**
         * @brief SetMass is a method that replaces the current mass of the body with the new mass given in parameter.
         * @param newMass The new mass for the body.
         */
        void constexpr SetMass(const float newMass) noexcept { _mass = newMass; }

        /**
         * @brief ApplyForce is a method that applies a force to the body and adds it to the sum of the body's forces
         * @param force The force to be applied to the body.
         */
        constexpr void ApplyForce(const Math::Vec2F force) noexcept { _forces += force; };

        /**
         * @brief Forces is a method that gives the sum of the body's forces.
         * @return The sum of the body's forces.
         */
        [[nodiscard]] constexpr Math::Vec2F Forces() const noexcept { return _forces; }

        /**
         * @brief ResetForces is a method that sets the sum of the body's forces to zero.
         */
        constexpr void ResetForces() noexcept { _forces = Math::Vec2F::Zero(); }

        /**
         * @brief IsValid is a method that checks if an object is valid (aka if it has a mass greater than 0).
         * @return True if the body is valid.
         */
        [[nodiscard]] constexpr bool IsValid() const noexcept { return _mass > 0; }
    };
}