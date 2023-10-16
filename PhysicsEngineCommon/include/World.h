#pragma once

#include "Body.h"

namespace PhysicsEngine
{
    struct BodyRef
    {
        std::size_t Index;
        std::size_t GenerationIdx;
    };

    class World
    {
    private:
        std::vector<Body> _bodies;
        std::vector<std::size_t> _generationIndices;
        const std::size_t _bodyResizeAmount = 500;

    public:
        World() noexcept = default;

        void Init(int bodyCount = 100) noexcept;
        BodyRef CreateBody() noexcept;
        void DestroyBody(BodyRef bodyRef) noexcept;
        [[nodiscard]] Body& GetBody(BodyRef bodyRef);
        void Update(float deltaTime) noexcept;

        [[nodiscard]] std::size_t BodyCount() { return _bodies.size(); }
    };
}

