/**
 * @author Olivier
 */


#include <iostream>
#include "World.h"

namespace PhysicsEngine
{
    void World::Init(int preallocatedBodyCount) noexcept
    {
        if (preallocatedBodyCount < 0) preallocatedBodyCount = 0;

        _bodies.resize(preallocatedBodyCount, Body());
        _bodiesGenIndices.resize(preallocatedBodyCount, 0);

        _colliders.resize(preallocatedBodyCount, Collider());
        _collidersGenIndices.resize(preallocatedBodyCount, 0);

        _quadTree.Init();
    }

    void World::Update(const float deltaTime) noexcept
    {
        for (auto& body : _bodies)
        {
            if (!body.IsValid()) continue;

            // a = F / m
            Math::Vec2F acceleration = body.Forces() / body.Mass();

            // Change velocity according to delta time.
            body.SetVelocity(body.Velocity() + acceleration * deltaTime);

            // Change position according to velocity and delta time.
            body.SetPosition(body.Position() + body.Velocity() * deltaTime);

            body.ResetForces();
        }

        if (_contactListener)
        {
            resolveBroadPhase();
            resolveNarrowPhase();
        }
    }

    void World::resolveBroadPhase() noexcept
    {
        _quadTree.Clear();

        // Sets the minimum and maximum collision zone limits of the world rectangle to floating maximum and
        // lowest values.
        Math::Vec2F worldMinBound(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
        Math::Vec2F worldMaxBound(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

        // Adjust the size of the collision zone in the world rectangle to the most distant bodies.
        for (const auto& collider : _colliders)
        {
            if (!collider.Enabled()) continue;

            const auto colCenter = GetBody(collider.GetBodyRef()).Position();

            if (worldMinBound.X > colCenter.X)
            {
                worldMinBound.X = colCenter.X;
            }

            if (worldMaxBound.X < colCenter.X)
            {
                worldMaxBound.X = colCenter.X;
            }

            if (worldMinBound.Y > colCenter.Y)
            {
                worldMinBound.Y = colCenter.Y;
            }

            if (worldMaxBound.Y < colCenter.Y)
            {
                worldMaxBound.Y = colCenter.Y;
            }
        }

        // Set the first rectangle of the quad-tree to calculated collision area rectangle.
        _quadTree.SetRootNodeBoundary(Math::RectangleF(worldMinBound, worldMaxBound));

        for (std::size_t i = 0; i < _colliders.size(); i++)
        {
            ColliderRef colliderRef = {i, _collidersGenIndices[i]};
            const auto& collider = GetCollider(colliderRef);

            if (!collider.Enabled()) continue;

            const auto colShape = collider.Shape();

            switch (colShape.index())
            {
                case static_cast<int>(Math::ShapeType::Circle):
                {
                    const auto circle = std::get<Math::CircleF>(colShape);
                    const auto radius = circle.Radius();
                    const auto simplifiedCircle = Math::RectangleF::FromCenter(
                            GetBody(collider.GetBodyRef()).Position(),
                            Math::Vec2F(radius, radius));

                    _quadTree.InsertInRoot(simplifiedCircle, colliderRef);
                }
            }
        }
    }

    void World::resolveNarrowPhase() noexcept
    {
        std::unordered_set<ColliderPair, ColliderHash> newColliderPairs;

        for (std::size_t i = 0; i < _colliders.size(); i++)
        {
            const ColliderRef colRefA{i, _collidersGenIndices[i]};
            const Collider colliderA = GetCollider(colRefA);

            if (!colliderA.Enabled()) continue;

            for (std::size_t j = 0; j < _colliders.size(); j++)
            {
                const ColliderRef colRefB{j, _collidersGenIndices[j]};
                const Collider colliderB = GetCollider(colRefB);

                if (!colliderB.Enabled()) continue;
                if (colRefB == colRefA) continue;
                if (colliderB.GetBodyRef() == colliderA.GetBodyRef()) continue;

                if (detectOverlap(colliderA, colliderB))
                {
                    newColliderPairs.insert(ColliderPair{colRefA, colRefB});
                }
            }
        }

        for (auto& colliderPair : newColliderPairs)
        {
            Collider& colliderA = GetCollider(colliderPair.ColliderA);
            Collider& colliderB = GetCollider(colliderPair.ColliderB);

            if (!colliderA.IsTrigger() && !colliderB.IsTrigger())
            {
                continue;
            }

            // If there was no collision in the previous frame -> OnTriggerEnter.
            if (_colliderPairs.find(colliderPair) == _colliderPairs.end())
            {
                _contactListener->OnTriggerEnter(colliderPair.ColliderA,colliderPair.ColliderB);
            }
            // If there was a collision in the previous frame and there is always a collision -> OnTriggerStay.
            else
            {
                _contactListener->OnTriggerStay(colliderPair.ColliderA, colliderPair.ColliderB);
            }
        }

        for (auto& colliderPair : _colliderPairs)
        {
            Collider& colliderA = GetCollider(colliderPair.ColliderA);
            Collider& colliderB = GetCollider(colliderPair.ColliderB);

            if (!colliderA.IsTrigger() && !colliderB.IsTrigger())
            {
                continue;
            }

            // If there is no collision in this frame -> OnTriggerExit.
            if (newColliderPairs.find(colliderPair) == newColliderPairs.end())
            {
                _contactListener->OnTriggerExit(
                        colliderPair.ColliderA,
                        colliderPair.ColliderB);
            }
        }

        _colliderPairs = newColliderPairs;
    }

    bool World::detectOverlap(const Collider& colA, const Collider& colB) noexcept
    {
        const auto& bodyA = GetBody(colA.GetBodyRef());
        const auto& bodyB = GetBody(colB.GetBodyRef());

        const auto colShapeA = colA.Shape();
        const auto colShapeB = colB.Shape();

        switch (colShapeA.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                const auto circleA = std::get<Math::CircleF>(colShapeA) +
                        bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) + bodyB.Position();

                        return Math::Intersect(circleA, circleB);
                    }

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        return Math::Intersect(circleA, rectB);
                    }

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                bodyB.Position();

                        return Math::Intersect(circleA, polygonB);
                    }

                    case static_cast<int>(Math::ShapeType::None):
                        return false;
                }
            }

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto rectA = std::get<Math::RectangleF>(colShapeA) + bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) +
                                             bodyB.Position();

                        return Math::Intersect(rectA, circleB);
                    }

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        return Math::Intersect(rectA, rectB);
                    }

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                              bodyB.Position();

                        return Math::Intersect(rectA, polygonB);
                    }
                    case static_cast<int>(Math::ShapeType::None):
                        return false;
                }
            }

            case static_cast<int>(Math::ShapeType::Polygon):
            {
                const auto polygonA = std::get<Math::PolygonF>(colShapeA) +
                                      bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) + bodyB.Position();

                        return Math::Intersect(polygonA, circleB);
                    }

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                           bodyB.Position();

                        return Math::Intersect(polygonA, rectB);
                    }

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                              bodyB.Position();

                        return Math::Intersect(polygonA, polygonB);
                    }

                    case static_cast<int>(Math::ShapeType::None):
                        return false;
                }
            }

            case static_cast<int>(Math::ShapeType::None):
                return false;
        }

        return false;
    }

    void World::Deinit() noexcept
    {
        _bodies.clear();
        _bodiesGenIndices.clear();
        _colliders.clear();
        _collidersGenIndices.clear();

        _quadTree.Clear();
    }

    [[nodiscard]] BodyRef World::CreateBody() noexcept
    {
        auto it = std::find_if(_bodies.begin(), _bodies.end(),[](const Body& body)
        {
            return !body.IsValid();
        });

        if (it != _bodies.end())
        {
            // Found an invalid body.
            std::size_t index = std::distance(_bodies.begin(), it);

            _bodies[index].SetMass(1.f);

            return BodyRef{index, _bodiesGenIndices[index]};
        }

        // No body with negative mass found.
        std::size_t previousSize = _bodies.size();
        auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _bodyAllocResizeFactor);

        _bodies.resize(newSize, Body());
        _bodiesGenIndices.resize(newSize, 0);

        _bodies[previousSize].SetMass(1.f);

        return {previousSize, _bodiesGenIndices[previousSize] };
    }

    void World::DestroyBody(BodyRef bodyRef) noexcept
    {
        _bodies[bodyRef.Index] = Body();
        _bodiesGenIndices[bodyRef.Index]++;
    }

    Body& World::GetBody(BodyRef bodyRef)
    {
        if (_bodiesGenIndices[bodyRef.Index] != bodyRef.GenerationIdx)
        {
            throw std::runtime_error("Null body reference exception");
        }

        return _bodies[bodyRef.Index];
    }

    Collider& World::GetCollider(ColliderRef colliderRef)
    {
        if (_collidersGenIndices[colliderRef.Index] != colliderRef.GenerationIdx)
        {
            throw std::runtime_error("Null collider reference exception");
        }

        return _colliders[colliderRef.Index];
    }

    ColliderRef World::CreateCollider(BodyRef bodyRef) noexcept
    {
        std::size_t colliderIdx = -1;

        auto it = std::find_if(
                _colliders.begin(),
                _colliders.end(),
                [](const Collider& collider)
        {
            return !collider.Enabled();
        });

        if (it != _colliders.end())
        {
            // Found an invalid collider.
            colliderIdx = std::distance(_colliders.begin(), it);
        }
        else
        {
            // No collider with none shape found.
            std::size_t previousSize = _colliders.size();
            auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _bodyAllocResizeFactor);

            _colliders.resize(newSize, Collider());
            _collidersGenIndices.resize(newSize, 0);

            colliderIdx = previousSize;
        }

        auto& collider = _colliders[colliderIdx];

        collider.SetEnabled(true);
        collider.SetBodyRef(bodyRef);

        ColliderRef colRef = {colliderIdx, _collidersGenIndices[colliderIdx]};

        return colRef;
    }

    void World::DestroyCollider(ColliderRef colRef) noexcept
    {
        _colliders[colRef.Index] = Collider();
        _collidersGenIndices[colRef.Index]++;
    }
}