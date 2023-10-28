//
// Created by Olivier on 27.10.2023.
//

#include <iostream>
#include "QuadTree.h"

void PhysicsEngine::QuadTree::Init() noexcept
{
    _nodes.resize(Math::Pow(4, _maxDepth), QuadNode());

    for(auto& node : _nodes)
    {
        node.Colliders.reserve(QuadNode::MaxColliderNbr);
    }
}

void PhysicsEngine::QuadTree::InsertInRoot(Math::RectangleF simplifiedShape, ColliderRef colliderRef) noexcept
{
    InsertInNode(_nodes[0], simplifiedShape, colliderRef, 0);
}

void PhysicsEngine::QuadTree::InsertInNode(PhysicsEngine::QuadNode& node,
                                           Math::RectangleF simplifiedShape,
                                           PhysicsEngine::ColliderRef colliderRef,
                                           int depth) noexcept
{
    if (node.Colliders.size() < QuadNode::MaxColliderNbr || depth == _maxDepth)
    {
        node.Colliders.push_back(colliderRef);
    }
    else
    {
        std::cout << "sub divide 1 \n";
        if (node.Children[0] == nullptr)
        {
            // Subdivide the node rectangle in 4 rectangle.
            std::cout << "sub divide \n";
        }

        for (const auto& child : node.Children)
        {
            if (Math::Intersect(child->Rectangle, simplifiedShape))
            {
                depth++;
                InsertInNode(*child, simplifiedShape, colliderRef, depth);
            }
        }
    }
}
