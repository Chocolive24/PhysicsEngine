#pragma once

/**
 * @headerfile The world is a class that contains all the physical bodies in the program and calculates
 * their movements and changes in physical state.
 * @author Olivier
 */

#include "Body.h"

#include <vector>

namespace PhysicsEngine
{
    /**
     * @brief BodyRef is a struct used to reference a specific body.
     * @attributes
     * Index : The index of the body inside the world body vector.\n\n
     * GenerationIdx : The index inside the world generation number vector.
     */
    struct BodyRef
    {
        std::size_t Index;
        std::size_t GenerationIdx;
    };

    class World
    {
    private:
        std::vector<Body> _bodies{};
        std::vector<std::size_t> _generationIndices{};

        constexpr static std::size_t _bodyResizeAmount = 500;

    public:
        constexpr World() noexcept = default;

        /**
         * @brief Init is a method that allocates memory for the desired number of bodies at the start of the program,
         * and instantiates invalid bodies for this number.
         * @param preallocatedBodyCount Number of bodies to allocate in memory. Default value is 100.
         */
        void Init(int preallocatedBodyCount = 100) noexcept;

        /**
         * @brief CreateBody is a method that creates a body in the world and returns a BodyRef to this body.
         * Body position, velocity and forces are set to (0, 0) by default and mass is set to 1 by default.
         * @return A BodyRef to the body in the world.
         */
        [[nodiscard]] BodyRef CreateBody() noexcept;

        /**
         * @brief DestroyBody is a method that destroys the body corresponding to the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to destroy.
         */
        void DestroyBody(BodyRef bodyRef) noexcept;

        /**
         * @brief GetBody is a method that returns the body corresponding the the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to get.
         */
        [[nodiscard]] Body& GetBody(BodyRef bodyRef);

        /**
         * @brief Update is a method that calculates the new velocities of all the world's valid body
         * according to their acceleration calculated with 'F / m = a', and their new positions in relation
         * to their new velocities.
         * @param deltaTime The time between frames.
         */
        void Update(float deltaTime) noexcept;

        [[nodiscard]] std::size_t BodyCount() const noexcept { return _bodies.size(); }
    };
}

