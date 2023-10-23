#pragma once

#include <cstddef>

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

    /**
     * @brief ColliderRef is a struct used to reference a specific collider.
     * @attributes
     * Index : The index of the collider inside the world body vector.\n\n
     * GenerationIdx : The index inside the world generation number vector.
     */
    struct ColliderRef
    {
        std::size_t Index;
        std::size_t GenerationIdx;

        constexpr ColliderRef& operator=(const ColliderRef& colRef) noexcept = default;
    };
}