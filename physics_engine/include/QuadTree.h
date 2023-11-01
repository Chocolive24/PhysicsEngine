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

    /**
     * @struct QuadNode is a struct representing a node in a quad-tree data structure used for spatial partitioning
     * in a 2D space.
     */
    struct QuadNode
    {
        /**
         * @brief MaxColliderNbr is the maximum number of colliders that can be considered in a quad-tree zone.
         */
        static constexpr int MaxColliderNbr = 6;

        /**
         * @brief BoundaryDivisionCount is the number of space boundary subdivision.
         */
        static constexpr int BoundaryDivisionCount = 4;

        Math::RectangleF Boundary{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
        std::array<QuadNode*, BoundaryDivisionCount> Children{};
        std::vector<SimplifiedCollider> Colliders{};

        constexpr QuadNode() noexcept = default;
        explicit QuadNode(Math::RectangleF boundary) noexcept : Boundary(boundary) {};
    };

    /**
     * @class QuadTree is a class
     */
    class QuadTree
    {
    private:
        std::vector<QuadNode> _nodes;
        std::vector<ColliderPair> _possiblePairs;

        /**
         * @brief MaxDepth is the maximum depth of the quad-tree recursive space subdivision.
         */
        static constexpr int _maxDepth = 5;

        void insertInNode(QuadNode& node,
                          Math::RectangleF simplifiedShape,
                          ColliderRef colliderRef,
                          int depth) noexcept;

        void addNodePossiblePairs(const QuadNode& node) noexcept;

    public:
        QuadTree() noexcept = default;

        /**
         * @brief Init is a method that initialize the quad-tree by allocating the needed amount of memory to
         * store the quad-nodes.
         */
        void Init() noexcept;

        /**
         * @brief Insert is a method that insert a collider (in its simplified shape) in the quad-tree from its
         * root node.
         * @param simplifiedShape The simplified shape of the collider (aka its shape in rectangle).
         * @param colliderRef The collider reference in the world.
         */
        void Insert(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept;

        /**
         * @brief CalculatePossiblePairs is a method which calculates the potential pairs of colliders in each
         * tree node that could touch each other by comparing their simplified shapes.
         */
        void CalculatePossiblePairs() noexcept;

        /**
         * @brief Clear is a method that removes all colliders from each node and removes possible pairs.
         */
        void Clear() noexcept;

        /**
         * @brief Deinit is a method that deinitialize the quad-tree by removing all data from it.
         */
        void Deinit() noexcept;

        /**
         * @brief RootNode is a method that gives the root node of the quad-tree (aka its first node).
         * @return The root node of the quad-tree (aka its first node).
         */
        [[nodiscard]] const QuadNode& RootNode() const noexcept { return _nodes[0]; }

        /**
         * @brief SetRoodNodeBoundary is a method that sets the boundary of the root node (aka the first space
         * subdivision) to the new one given in parameter.
         * @param boundary The boundary of the first space subdivision.
         */
        constexpr void SetRootNodeBoundary(const Math::RectangleF boundary) noexcept
        {
            _nodes[0].Boundary = boundary;
        };

        /**
         * @brief PossiblePairs is a method that gives the possible pairs of collider whose simplified shapes
         * touch each other.
         * @return The possible pairs of collider whose simplified shapes touch each other.
         */
        [[nodiscard]] const std::vector<ColliderPair>& PossiblePairs() const noexcept { return _possiblePairs; }

        /**
         * @brief MaxDepth is a method that gives the maximum depth of the quad-tree recursive space subdivision.
         * @return The maximum depth of the quad-tree recursive space subdivision.
         */
        [[nodiscard]] static constexpr int MaxDepth() noexcept { return _maxDepth; }
    };
}