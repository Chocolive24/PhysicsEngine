#pragma once

#include "Collider.h"

#include <vector>

namespace PhysicsEngine
{
    /**
     * @struct SimplifiedCollider is a struct that stores the data of a collider in a simplified way (aka it stores
     * its collider reference in the world and its shape in a rectangle form).
     */
    struct SimplifiedCollider
    {
        ColliderRef ColRef;
        Math::RectangleF Rectangle;
    };

    struct QuadNode
    {
        /**
         * @brief MaxColliderNbr is the maximum number of colliders that can be considered in a quad-tree zone.
         */
        static constexpr int MaxColliderNbr = 10;

        static constexpr int BoundaryDivisionCount = 4;

        Math::RectangleF Boundary{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
        std::array<QuadNode*, BoundaryDivisionCount> Children{};
        std::vector<SimplifiedCollider> Colliders{};

        constexpr QuadNode() noexcept = default;
        explicit QuadNode(Math::RectangleF boundary) noexcept : Boundary(boundary) {};
    };

    class QuadTree
    {
    private:
        std::vector<QuadNode> _nodes;
        std::vector<ColliderPair> _possiblePairs;

        static constexpr int _maxDepth = 5;

        void insertInNode(QuadNode& node,
                          Math::RectangleF simplifiedShape,
                          ColliderRef colliderRef,
                          int depth) noexcept;

        void addNodePossiblePairs(const QuadNode& node) noexcept;

    public:
        QuadTree() noexcept = default;

        void Init() noexcept;
        void Insert(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept;

        void CalculatePossiblePairs() noexcept;
        void Clear() noexcept;

        [[nodiscard]] const QuadNode& RootNode() const noexcept { return _nodes[0]; }

        constexpr void SetRootNodeBoundary(const Math::RectangleF boundary) noexcept
        {
            _nodes[0].Boundary = boundary;
        };

        [[nodiscard]] const std::vector<ColliderPair>& PossiblePairs() const noexcept { return _possiblePairs; }

        [[nodiscard]] constexpr int MaxDepth() noexcept { return _maxDepth; }
    };
}