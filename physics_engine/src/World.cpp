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

        _circleColliders.resize(preallocatedBodyCount, CircleCollider());
        _rectangleColliders.resize(preallocatedBodyCount, RectangleCollider());
        _polygonColliders.resize(preallocatedBodyCount, PolygonCollider());
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
            updateCollisionDetection();
        }
    }

    void World::updateCollisionDetection() noexcept
    {
        std::unordered_set<ColliderPair, ColliderHash> newColliderPairs;

        for (auto& colliderA : _colliders)
        {
            if (!colliderA.IsValid()) continue;

            for (auto& colliderB : _colliders)
            {
                if (!colliderB.IsValid()) continue;
                if (colliderB.GetColliderRef() == colliderA.GetColliderRef()) continue;
                if (colliderB.GetBodyRef() == colliderA.GetBodyRef()) continue;

                if (detectCollision(colliderA, colliderB))
                {
                    newColliderPairs.insert(ColliderPair{colliderA.GetColliderRef(),
                                                         colliderB.GetColliderRef()});
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

    bool World::detectCollision(Collider colA, Collider colB) noexcept
    {
        const auto& bodyA = GetBody(colA.GetBodyRef());
        const auto& bodyB = GetBody(colB.GetBodyRef());

        switch (colA.Shape())
        {
            case Math::ShapeType::Circle:
            {
                const Math::CircleF circleA(bodyA.Position(),
                                            GetCircleCollider(colA.ShapeIdx()).Radius());
                switch (colB.Shape())
                {
                    case Math::ShapeType::Circle:
                    {
                        const Math::CircleF circleB(bodyB.Position(),
                                                    GetCircleCollider(colB.ShapeIdx()).Radius());

                        return Math::Intersect(circleA, circleB);
                    }

                    case Math::ShapeType::Rectangle:
                    {
                        auto bodyBPos = bodyB.Position();
                        auto halfSize = GetRectangleCollider(colB.ShapeIdx()).HalfSize();
                        const Math::RectangleF rectB(bodyBPos - halfSize, bodyBPos + halfSize);

                        return Math::Intersect(circleA, rectB);
                    }

                    case Math::ShapeType::Polygon:
                    {
                        const auto vertices = GetPolygonCollider(
                                colB.ShapeIdx()).Vertices();

                        const Math::PolygonF polygonB(vertices);

                        return Math::Intersect(circleA, polygonB);
                    }

                    case Math::ShapeType::None:
                        return false;
                }
            }

            case Math::ShapeType::Rectangle:
            {
                auto bodyAPos = bodyA.Position();
                auto halfSizeA = GetRectangleCollider(colA.ShapeIdx()).HalfSize();
                const Math::RectangleF rectA(bodyAPos - halfSizeA, bodyAPos + halfSizeA);

                switch (colB.Shape())
                {
                    case Math::ShapeType::Circle:
                    {
                        const Math::CircleF circleB(bodyB.Position(),
                                                    GetCircleCollider(colB.ShapeIdx()).Radius());

                        return Math::Intersect(rectA, circleB);
                    }

                    case Math::ShapeType::Rectangle:
                    {
                        auto bodyBPos = bodyB.Position();
                        auto halfSizeB = GetRectangleCollider(colB.ShapeIdx()).HalfSize();
                        const Math::RectangleF rectB(bodyBPos - halfSizeB, bodyBPos + halfSizeB);

                        return Math::Intersect(rectA, rectB);
                    }

                    case Math::ShapeType::Polygon:
                    {
                        const auto vertices = GetPolygonCollider(
                                colB.ShapeIdx()).Vertices();

                        const Math::PolygonF polygonB(vertices);

                        return Math::Intersect(rectA, polygonB);
                    }
                    case Math::ShapeType::None:
                        return false;
                }
            }

            case Math::ShapeType::Polygon:
            {
                const auto vertices = GetPolygonCollider(
                        colA.ShapeIdx()).Vertices();

                const Math::PolygonF polygonA(vertices);

                switch (colB.Shape())
                {
                    case Math::ShapeType::Circle:
                    {
                        const Math::CircleF circleB(bodyB.Position(),
                                                    GetCircleCollider(colB.ShapeIdx()).Radius());

                        return Math::Intersect(polygonA, circleB);
                    }

                    case Math::ShapeType::Rectangle:
                    {
                        auto bodyBPos = bodyB.Position();
                        auto halfSizeB = GetRectangleCollider(colB.ShapeIdx()).HalfSize();
                        const Math::RectangleF rectB(bodyBPos - halfSizeB, bodyBPos + halfSizeB);

                        return Math::Intersect(polygonA, rectB);
                    }

                    case Math::ShapeType::Polygon:
                    {
                        const auto verticesB = GetPolygonCollider(
                                colB.ShapeIdx()).Vertices();

                        const Math::PolygonF polygonB(verticesB);

                        return Math::Intersect(polygonA, polygonB);
                    }

                    case Math::ShapeType::None:
                        return false;
                }
            }

            case Math::ShapeType::None:
                return false;
        }
    }

    void World::Deinit() noexcept
    {
        _bodies.clear();
        _bodiesGenIndices.clear();
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

    ColliderRef World::CreateCircleCollider(BodyRef bodyRef) noexcept
    {
        std::size_t colliderIdx = -1;

        auto it = std::find_if(
                _colliders.begin(),
                _colliders.end(),
                [](const Collider& collider)
        {
            return !collider.IsValid();
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

        collider.SetShape(Math::ShapeType::Circle);
        collider.SetBodyRef(bodyRef);

        ColliderRef colRef = {colliderIdx, _collidersGenIndices[colliderIdx]};
        collider.SetColliderRef(colRef);

        std::size_t circleColIdx = -1;

        auto circleColIt = std::find_if(
                _circleColliders.begin(),
                _circleColliders.end(),
                [](const CircleCollider& circleCol)
        {
            return !circleCol.IsValid();
        });

        if (circleColIt != _circleColliders.end())
        {
            circleColIdx = std::distance(_circleColliders.begin(), circleColIt);
        }
        else
        {
            // No collider with none shape found.
            std::size_t previousSize = _circleColliders.size();
            auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _bodyAllocResizeFactor);

            _circleColliders.resize(newSize, CircleCollider());

            circleColIdx = previousSize;
        }

         _circleColliders[circleColIdx].SetRadius(1.f);
        collider.SetShapeIdx(static_cast<int>(circleColIdx));

        return colRef;
    }


    ColliderRef World::CreateRectangleCollider(BodyRef bodyRef) noexcept
    {
        std::size_t colliderIdx = -1;

        auto it = std::find_if(
                _colliders.begin(),
                _colliders.end(),
                [](const Collider& collider)
                {
                    return !collider.IsValid();
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

        collider.SetShape(Math::ShapeType::Rectangle);
        collider.SetBodyRef(bodyRef);

        ColliderRef colRef = {colliderIdx, _collidersGenIndices[colliderIdx]};
        collider.SetColliderRef(colRef);

        std::size_t rectColIdx = -1;

        auto rectColIt = std::find_if(
                _rectangleColliders.begin(),
                _rectangleColliders.end(),
                [](const RectangleCollider& rectCol)
                {
                    return !rectCol.IsValid();
                });

        if (rectColIt != _rectangleColliders.end())
        {
            rectColIdx = std::distance(_rectangleColliders.begin(), rectColIt);
        }
        else
        {
            // No collider with none shape found.
            std::size_t previousSize = _rectangleColliders.size();
            auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _bodyAllocResizeFactor);

            _rectangleColliders.resize(newSize, RectangleCollider());

            rectColIdx = previousSize;
        }

        _rectangleColliders[rectColIdx].SetHalfSize(Math::Vec2F::One());
        collider.SetShapeIdx(static_cast<int>(rectColIdx));

        return colRef;
    }

    ColliderRef World::CreatePolygonCollider(BodyRef bodyRef) noexcept
    {
        std::size_t colliderIdx;

        auto it = std::find_if(
                _colliders.begin(),
                _colliders.end(),
                [](const Collider& collider)
                {
                    return !collider.IsValid();
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

        collider.SetShape(Math::ShapeType::Polygon);
        collider.SetBodyRef(bodyRef);

        ColliderRef colRef = {colliderIdx, _collidersGenIndices[colliderIdx]};
        collider.SetColliderRef(colRef);

        std::size_t polygonColIdx;

        auto polygonColIt = std::find_if(
                _polygonColliders.begin(),
                _polygonColliders.end(),
                [](const PolygonCollider& rectCol)
                {
                    return !rectCol.IsValid();
                });

        if (polygonColIt != _polygonColliders.end())
        {
            polygonColIdx = std::distance(_polygonColliders.begin(), polygonColIt);
        }
        else
        {
            // No collider with none shape found.
            std::size_t previousSize = _polygonColliders.size();
            auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _bodyAllocResizeFactor);

            _polygonColliders.resize(newSize, PolygonCollider());

            polygonColIdx = previousSize;
        }

        std::vector<Math::Vec2F> vertices;
        vertices.resize(3, Math::Vec2F());

        _polygonColliders[polygonColIdx].SetVertices(vertices);
        collider.SetShapeIdx(static_cast<int>(polygonColIdx));

        return colRef;
    }

    void World::DestroyCollider(ColliderRef colRef) noexcept
    {
        auto& collider = _colliders[colRef.Index];

        switch(collider.Shape())
        {
            case Math::ShapeType::Circle:
                _circleColliders[collider.ShapeIdx()] = CircleCollider();
                break;
            case Math::ShapeType::Rectangle:
                _rectangleColliders[collider.ShapeIdx()] = RectangleCollider();
                break;
            case Math::ShapeType::Polygon:
                _polygonColliders[collider.ShapeIdx()] = PolygonCollider();
                break;
            case Math::ShapeType::None:
                return;
        }

        collider = Collider();
        _collidersGenIndices[colRef.Index]++;
    }
}