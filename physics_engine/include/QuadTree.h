#pragma once

#include "Collider.h"

#include <vector>

namespace PhysicsEngine
{
    /**
     * @struct SimplifiedCollider is a struct that stores the data of a collider in a simplified way (aka it stores
     * is collider reference in the world and its shape in rectangle).
     */
    struct SimplifiedCollider
    {
        ColliderRef ColRef;
        Math::RectangleF Rectangle;
    };

    struct QuadNode
    {
        Math::RectangleF Boundary{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
        std::array<QuadNode*, 4> Children{};
        std::vector<SimplifiedCollider> Colliders{};

        static constexpr int MaxColliderNbr = 1;

        constexpr QuadNode() noexcept = default;
        explicit QuadNode(Math::RectangleF boundary) noexcept : Boundary(boundary) {};
    };

    class QuadTree
    {
    private:
        std::vector<QuadNode> _nodes;
        static constexpr int _maxDepth = 5;

        std::vector<ColliderPair> _possiblePairs;

        void insertInNode(QuadNode& node,
                          Math::RectangleF simplifiedShape,
                          ColliderRef colliderRef,
                          int depth) noexcept;

        void addNodePossiblePairs(const QuadNode& node) noexcept;

    public:
        QuadTree() noexcept = default;

        void Init() noexcept;
        void InsertInRoot(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept;

        void CalculatePossiblePairs() noexcept;
        void Clear() noexcept;

        [[nodiscard]] const QuadNode& RootNode() const noexcept { return _nodes[0]; }

        constexpr void SetRootNodeBoundary(const Math::RectangleF boundary) noexcept
        {
            _nodes[0].Boundary = boundary;
        };

        [[nodiscard]] const std::vector<ColliderPair>& PossiblePairs() const noexcept { return _possiblePairs; }
    };
}