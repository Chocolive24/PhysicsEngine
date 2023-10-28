#pragma once

#include "Collider.h"

#include <vector>

namespace PhysicsEngine
{
    struct QuadNode
    {
        Math::RectangleF Rectangle{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
        std::array<QuadNode*, 4> Children{};
        std::vector<ColliderRef> Colliders{};

        static constexpr int MaxColliderNbr = 16;

        constexpr QuadNode() noexcept = default;
    };

    class QuadTree
    {
    private:
        std::vector<QuadNode> _nodes;
        static constexpr int _maxDepth = 5;

    public:
        QuadTree() noexcept = default;

        void Init() noexcept;
        void InsertInRoot(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept;
        void InsertInNode(QuadNode& node,
                          Math::RectangleF simplifiedShape,
                          ColliderRef colliderRef,
                          int depth) noexcept;

        constexpr void SetRootNodeRectangle(const Math::RectangleF rectangle) noexcept
        {
            _nodes[0].Rectangle = rectangle;
        };
    };
}