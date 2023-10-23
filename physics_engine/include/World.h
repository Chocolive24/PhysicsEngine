#pragma once

/**
 * @headerfile World is a class that contains all the physical bodies in the program and calculates
 * their movements and changes in physical state.
 * @author Olivier
 */

#include "Body.h"
#include "Collider.h"
#include "References.h"

#include <vector>

namespace PhysicsEngine
{
    class World
    {
    private:
        std::vector<Body> _bodies{};
        std::vector<std::size_t> _generationIndices{};

        static constexpr float _bodyAllocationResizeFactor = 2.f;

    public:
        constexpr World() noexcept = default;

        /**
         * @brief Init is a method that pre-allocates memory for the desired number of bodies by creating invalid
         * bodies (aka bodies with negative mass).
         * @param preAllocatedBodyCount The number of bodies to pre-allocate in memory. Default value is 100.
         */
        void Init(int preAllocatedBodyCount = 100) noexcept;

        /**
         * @brief Update is a method that calculates the new velocities of all the world's valid bodies
         * according to their acceleration (calculated with 'F / m = a'), and their new positions according
         * to their new velocities.
         * @param deltaTime The time elapsed between two consecutive frames.
         */
        void Update(float deltaTime) noexcept;

        void Deinit() noexcept;

        /**
         * @brief CreateBody is a method that creates a body in the world and returns a BodyRef to this body.
         * @note Body position, velocity and forces are set to (0, 0) by default and mass is set to 1 by default.
         * @return A BodyRef to the body in the world (see BodyRef).
         */
        [[nodiscard]] BodyRef CreateBody() noexcept;

        /**
         * @brief DestroyBody is a method that destroys the body corresponding to the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to destroy.
         */
        void DestroyBody(BodyRef bodyRef) noexcept;

        /**
         * @brief GetBody is a method that gives the body corresponding to the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to get.
         */
        [[nodiscard]] Body& GetBody(BodyRef bodyRef);

        /**
         * @brief AllocatedBodies is a method that gives the number of allocated bodies.
         * @return The number of allocated bodies.
         */
        [[nodiscard]] std::size_t AllocatedBodies() const noexcept { return _bodies.size(); }

        [[nodiscard]] ColliderRef CreateCollider(BodyRef bodyRef) noexcept;

        void DestroyCollider(ColliderRef colRef) noexcept;

        [[nodiscard]] Collider& GetCollider(ColliderRef colRef);


    };
}

