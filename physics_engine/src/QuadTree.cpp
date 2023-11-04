//
// Created by Olivier on 27.10.2023.
//

#include "QuadTree.h"

#ifdef TRACY_ENABLE
#include <Tracy.hpp>
#endif // TRACY_ENABLE

namespace PhysicsEngine
{
    template<typename T>
    constexpr T QuadCount(T depth)
    {
        T result = 0;

        for (T i = 0; i <= depth; i++)
        {
            result += Math::Pow(QuadNode::BoundaryDivisionCount, i);
        }

        return result;
    }

    void QuadTree::Init() noexcept
    {
        _nodes.resize(QuadCount(_maxDepth), QuadNode());

        for (auto& node : _nodes)
        {
            node.Colliders.reserve(QuadNode::MaxColliderNbr + 1);
        }
    }

    void QuadTree::Insert(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept
    {
        insertInNode(_nodes[0], simplifiedShape, colliderRef, 0);
    }

    void QuadTree::insertInNode(QuadNode& node,
        Math::RectangleF simplifiedShape,
        ColliderRef colliderRef,
        int depth) noexcept
    {
    /*#ifdef TRACY_ENABLE
            ZoneScoped;
    #endif*/
        // If the node doesn't have any children.
        if (node.Children[0] == nullptr)
        {
            // Add the simplified collider to the node.
            SimplifiedCollider simplifiedCollider = { colliderRef, simplifiedShape };
            node.Colliders.push_back(simplifiedCollider);

            // If the node has fewer colliders than the max number and the depth is not equal to the max depth.
            if (node.Colliders.size() > QuadNode::MaxColliderNbr && depth != _maxDepth)
            {
                // Subdivide the node rectangle in 4 rectangle.
                const auto center = node.Boundary.Center();
                const auto halfSize = node.Boundary.HalfSize();

                const auto topMiddle = Math::Vec2F(center.X, center.Y + halfSize.Y);
                const auto topRightCorner = center + halfSize;
                const auto rightMiddle = Math::Vec2F(center.X + halfSize.X, center.Y);
                const auto bottomMiddle = Math::Vec2F(center.X, center.Y - halfSize.Y);
                const auto bottomLeftCorner = center - halfSize;
                const auto leftMiddle = Math::Vec2F(center.X - halfSize.X, center.Y);

                _nodes[_nodeIndex].Boundary = Math::RectangleF(leftMiddle, topMiddle);
                _nodes[_nodeIndex + 1].Boundary = Math::RectangleF(center, topRightCorner);
                _nodes[_nodeIndex + 2].Boundary = Math::RectangleF(bottomLeftCorner, center);
                _nodes[_nodeIndex + 3].Boundary = Math::RectangleF(bottomMiddle, rightMiddle);

                node.Children[0] = &_nodes[_nodeIndex];
                node.Children[1] = &_nodes[_nodeIndex + 1];
                node.Children[2] = &_nodes[_nodeIndex + 2];
                node.Children[3] = &_nodes[_nodeIndex + 3];

                _nodeIndex += 4;

                std::vector<SimplifiedCollider> remainingColliders; //TODO: std::array avec max col nbr.

                for (const auto& col : node.Colliders)
                {
                    int boundInterestCount = 0;
                    QuadNode* intersectNode = nullptr;

                    for (const auto& child : node.Children)
                    {
                        if (Math::Intersect(child->Boundary, col.Rectangle))
                        {
                            boundInterestCount++;
                            intersectNode = child;
                        }
                    }

                    if (boundInterestCount == 1)
                    {
                        insertInNode(*intersectNode, col.Rectangle, col.ColRef, depth + 1);
                    }
                    else
                    {
                        remainingColliders.push_back(col);
                    }
                }

                node.Colliders = std::move(remainingColliders);
            }
        }

        // If the node has children.
        else
        {
            int boundInterestCount = 0;
            QuadNode* intersectNode = nullptr;

            for (const auto& child : node.Children)
            {
                if (Math::Intersect(child->Boundary, simplifiedShape))
                {
                    boundInterestCount++;
                    intersectNode = child;
                }
            }

            if (boundInterestCount == 1)
            {
                depth++;
                insertInNode(*intersectNode, simplifiedShape, colliderRef, depth);
            }
            else
            {
                SimplifiedCollider simplifiedCollider = { colliderRef, simplifiedShape };
                node.Colliders.push_back(simplifiedCollider);
            }
        }
    }

    void QuadTree::CalculatePossiblePairs() noexcept
    {
        calculateNodePossiblePairs(_nodes[0]);
    }

    void QuadTree::calculateNodePossiblePairs(const QuadNode& node) noexcept
    {
    /*#ifdef TRACY_ENABLE
            ZoneScoped;
    #endif*/

        for (const auto& simplColA : node.Colliders)
        {
            for (const auto& simplColB : node.Colliders)
            {
                if (simplColA.ColRef == simplColB.ColRef) continue;

                if (Math::Intersect(simplColA.Rectangle, simplColB.Rectangle))
                {
                    _possiblePairs.push_back(ColliderPair{ simplColA.ColRef, simplColB.ColRef });
                }
            }

            // If the node has children, we need to compare the simplified collider with the colliders in the children nodes.
            if (node.Children[0] != nullptr)
            {
                for (const auto& childNode : node.Children)
                {
                    // Check the collision only if the collider touche the children boundary.
                    /*if (Math::Intersect(simplColA.Rectangle, node.Boundary))
                    {
                        calculateChildrenNodePossiblePairs(*childNode, simplColA);
                    }*/

                    calculateChildrenNodePossiblePairs(*childNode, simplColA);
                }
            }
        }

        // If the node has children.
        if (node.Children[0] != nullptr)
        {
            for (const auto& child : node.Children)
            {
                calculateNodePossiblePairs(*child);
            }
        }
    }

    void QuadTree::calculateChildrenNodePossiblePairs(const QuadNode& node, SimplifiedCollider simplCol) noexcept
    {
    /*#ifdef TRACY_ENABLE
            ZoneScoped;
    #endif*/
        //// If the current node has children, we need to compare the simplified collider from its parent node with its children.
        //if (node.Children[0] != nullptr)
        //{
        //    for (const auto& child : node.Children)
        //    {
        //        if (Math::Intersect(simplCol.Rectangle, child->Boundary))
        //        {
        //            calculateChildrenNodePossiblePairs(*child, simplCol);
        //        }
        //    }
        //}

        // For each colliders in the current node, compare it with the simplified collider from its parent node.
        for (const auto& nodeSimplCol : node.Colliders)
        {
            if (Math::Intersect(simplCol.Rectangle, nodeSimplCol.Rectangle))
            {
                _possiblePairs.push_back(ColliderPair{ simplCol.ColRef, nodeSimplCol.ColRef });
            }
        }

        // If the current node has children, we need to compare the simplified collider from its parent node with its children.
        if (node.Children[0] != nullptr)
        {
            for (const auto& child : node.Children)
            {
                calculateChildrenNodePossiblePairs(*child, simplCol);
            }
        }
    }

    void QuadTree::Clear() noexcept
    {
        for (auto& node : _nodes)
        {
            node.Colliders.clear();

            std::fill(node.Children.begin(), node.Children.end(), nullptr);
        }

        _nodeIndex = 1;

        _possiblePairs.clear();
    }

    void QuadTree::Deinit() noexcept
    {
        _nodes.clear();

        _nodeIndex = 1;

        _possiblePairs.clear();
    }
}