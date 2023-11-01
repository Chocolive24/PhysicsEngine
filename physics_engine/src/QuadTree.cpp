//
// Created by Olivier on 27.10.2023.
//

#include "QuadTree.h"

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
            node.Colliders.reserve(QuadNode::MaxColliderNbr);
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

                //TODO: utiliser _nodes au leiu de new Quad.
                node.Children[0] = new QuadNode(Math::RectangleF(leftMiddle, topMiddle));
                node.Children[1] = new QuadNode(Math::RectangleF(center, topRightCorner));
                node.Children[2] = new QuadNode(Math::RectangleF(bottomLeftCorner, center));
                node.Children[3] = new QuadNode(Math::RectangleF(bottomMiddle, rightMiddle));

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

    void QuadTree::Clear() noexcept
    {
        for (auto& node : _nodes)
        {
            node.Colliders.clear();

            std::fill(node.Children.begin(), node.Children.end(), nullptr);
        }

        _possiblePairs.clear();
    }

    void QuadTree::Deinit() noexcept
    {
        for (auto& node : _nodes)
        {
            node.Colliders.clear();

            for (auto& child : node.Children)
            {
                delete child;
            }
        }

        _possiblePairs.clear();
    }
}