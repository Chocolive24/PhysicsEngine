/**
 * @author Olivier
 */

#ifdef TRACY_ENABLE
#include <Tracy.hpp>
#include <TracyC.h>
#endif // TRACY_ENABLE

#include "World.h"

namespace PhysicsEngine
{
    void World::Init(int preallocatedBodyCount) noexcept
    {
#ifdef TRACY_ENABLE
        ZoneScoped;
#endif // TRACY_ENABLE
        if (preallocatedBodyCount < 0) preallocatedBodyCount = 0;

        _bodies.resize(preallocatedBodyCount, Body());
        _bodiesGenIndices.resize(preallocatedBodyCount, 0);

        _colliders.resize(preallocatedBodyCount, Collider());
        _collidersGenIndices.resize(preallocatedBodyCount, 0);

        _quadTree.Init();
    }

    void World::Update(const float deltaTime) noexcept
    {
    #ifdef TRACY_ENABLE
            ZoneScoped;
    #endif
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
    #ifdef TRACY_ENABLE
            ZoneScoped;
    #endif

        _quadTree.Clear();

        // Sets the minimum and maximum collision zone limits of the world rectangle to floating maximum and
        // lowest values.
        Math::Vec2F worldMinBound(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
        Math::Vec2F worldMaxBound(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest());

    #ifdef TRACY_ENABLE
        ZoneNamedN(SetRoodNodeBoundary, "SetRootNodeBoundary", true);
    #endif

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

    #ifdef TRACY_ENABLE
            ZoneNamedN(InsertCollidersInQuadTree, "InsertCollidersInQuadTree", true);
    #endif
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

                    _quadTree.Insert(simplifiedCircle, colliderRef);
                    break;
                } // Case circle.

                case static_cast<int>(Math::ShapeType::Rectangle):
                {
                    const auto rect = std::get<Math::RectangleF>(colShape) +
                            GetBody(collider.GetBodyRef()).Position();

                    _quadTree.Insert(rect, colliderRef);
                    break;
                } // Case rectangle.

                case static_cast<int>(Math::ShapeType::Polygon):
                {
                    Math::Vec2F minVertex(std::numeric_limits<float>::max(), 
                                          std::numeric_limits<float>::max());

                    Math::Vec2F maxVertex(std::numeric_limits<float>::lowest(),
                                          std::numeric_limits<float>::lowest());

                    const auto poly = std::get<Math::PolygonF>(colShape) +
                            GetBody(collider.GetBodyRef()).Position();

                    for (const auto& vertex : poly.Vertices())
                    {
                        if (minVertex.X > vertex.X)
                        {
                            minVertex.X = vertex.X;
                        }

                        if (maxVertex.X < vertex.X)
                        {
                            maxVertex.X = vertex.X;
                        }

                        if (minVertex.Y > vertex.Y)
                        {
                            minVertex.Y = vertex.Y;
                        }

                        if (maxVertex.Y < vertex.Y)
                        {
                            maxVertex.Y = vertex.Y;
                        }
                    } // For range vertex.

                    Math::RectangleF simplifiedPoly(minVertex, maxVertex);

                    _quadTree.Insert(simplifiedPoly, colliderRef);
                    break;
                } // Case polygon.
            } // Switch collider shape index.
        } // For int i < colliders.size().

        _quadTree.CalculatePossiblePairs();
    }

    void World::resolveNarrowPhase() noexcept
    {
    #ifdef TRACY_ENABLE
            ZoneScoped;
    #endif

    #ifdef TRACY_ENABLE
            ZoneNamedN(DetectOverlap, "Detect Overlap", true);
    #endif
        std::unordered_set<ColliderPair, ColliderHash> newColliderPairs;

        const auto& newPossiblePairs = _quadTree.PossiblePairs();

        for (const auto& possiblePair : newPossiblePairs)
        {
            ContactSolver contactSolver;

            auto& colliderA = _colliders[possiblePair.ColliderA.Index];
            auto& colliderB = _colliders[possiblePair.ColliderB.Index];

            auto it = _colliderPairs.find(possiblePair);

            const auto doCollidersIntersect = detectContact(colliderA, colliderB, contactSolver);

            if (it != _colliderPairs.end())
            {
                if (!doCollidersIntersect)
                {
                    if (colliderA.IsTrigger() || colliderB.IsTrigger())
                    {
                        _contactListener->OnTriggerExit(possiblePair.ColliderA,
                            possiblePair.ColliderB);
                        
                    }
                    else
                    {
                        _contactListener->OnCollisionExit(possiblePair.ColliderA,
                                                          possiblePair.ColliderB);
                    }

                    _colliderPairs.erase(it);
                }
                else
                {
                    if (!colliderA.IsTrigger() && !colliderB.IsTrigger())
                    {
                        contactSolver.ResolveContact();
                    }
                    
                }
            }
            else
            {
                if (doCollidersIntersect)
                {
                    if (colliderA.IsTrigger() || colliderB.IsTrigger())
                    {
                        _contactListener->OnTriggerEnter(possiblePair.ColliderA,
                            possiblePair.ColliderB);
                    }
                    else
                    {
                        contactSolver.ResolveContact();
                        _contactListener->OnCollisionEnter(possiblePair.ColliderA,
                            possiblePair.ColliderB);
                    }

                    _colliderPairs.insert(possiblePair);
                }
            }
        }
    }

    bool World::detectContact(Collider& colA, Collider& colB, ContactSolver& contactSolver) noexcept
    {
    #ifdef TRACY_ENABLE
            ZoneScoped;
    #endif
        auto& bodyA = GetBody(colA.GetBodyRef());
        auto& bodyB = GetBody(colB.GetBodyRef());

        const auto mustCalculateContact = !colA.IsTrigger() && !colB.IsTrigger();

        if (mustCalculateContact)
        {
            contactSolver.bodyA = &bodyA;
            contactSolver.bodyB = &bodyB;

            contactSolver.colliderA = &colA;
            contactSolver.colliderB = &colB;
        }

        const auto colShapeA = colA.Shape();
        const auto colShapeB = colB.Shape();

        bool doCollidersIntersect = false;

        switch (colShapeA.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                const auto circleA = std::get<Math::CircleF>(colShapeA) + bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) + bodyB.Position();

                        doCollidersIntersect = Math::Intersect(circleA, circleB);

                        // Create the circle-circle Contact if needed.
                        if (mustCalculateContact && doCollidersIntersect)
                        {
                            const auto cA = circleA.Center(), cB = circleB.Center();
                            const auto rA = circleA.Radius(), rB = circleB.Radius();

                            const auto delta = cA - cB;
                            contactSolver.Normal = delta.Normalized();
                            contactSolver.Point = cA + delta * 0.5f;
                            contactSolver.Penetration = rA + rB - delta.Length();
                        }

                        break;
                    } // Case circle B.
                    
                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        doCollidersIntersect = Math::Intersect(circleA, rectB);

                        if (mustCalculateContact && doCollidersIntersect)
                        {
                            const auto circleCenter = circleA.Center(), rectCenter = rectB.Center();
                            const auto rectHalfSize = rectB.HalfSize();

                            const auto delta = circleCenter - rectCenter;

                            Math::Vec2F closestPoint;

                            closestPoint.X = Math::Clamp(delta.X, -rectHalfSize.X, rectHalfSize.X);
                            closestPoint.Y = Math::Clamp(delta.Y, -rectHalfSize.Y, rectHalfSize.Y);

                            const auto distance = (closestPoint - delta).Length();
                            const auto closestPoinOnRect = rectCenter + closestPoint;

                            auto circleToRect = (circleCenter - closestPoinOnRect);

                            if (circleToRect.Length() <= Math::Epsilon)
                            {
                                const auto closestPointOnRectToCenter = rectCenter - closestPoinOnRect;
                                const auto direction = closestPointOnRectToCenter.Normalized();
                                constexpr float adjustmentFactor = 0.2f;

                                const auto adjustment = adjustmentFactor * -direction;

                                // Adjust the position of bodyA
                                bodyA.SetPosition(bodyA.Position() + adjustment);
                                const auto correctedCircle = std::get<Math::CircleF>(colShapeA) + bodyA.Position();

                                // Recalculate the circleToRect vector after the adjustment
                                circleToRect = (correctedCircle.Center() - closestPoinOnRect);
                            }

                            contactSolver.Normal = circleToRect.Normalized();
                            contactSolver.Point = closestPoinOnRect;
                            contactSolver.Penetration = circleA.Radius() - distance;
                        }

                        break;
                    } // Case rectangle B.

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                bodyB.Position();

                        doCollidersIntersect = Math::Intersect(circleA, polygonB);
                        break;
                    } // Case polygon B.

                    case static_cast<int>(Math::ShapeType::None):
                        break;
                    default:
                        break;
                } // Switch shape collider B.

                break;
            } // Case circle A.

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto rectA = std::get<Math::RectangleF>(colShapeA) + bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) +
                                             bodyB.Position();

                        doCollidersIntersect = Math::Intersect(rectA, circleB);

                        if (mustCalculateContact && doCollidersIntersect)
                        {
                            detectContact(colB, colA, contactSolver);
                        }

                        break;
                    } // Case circle B.

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        doCollidersIntersect = Math::Intersect(rectA, rectB);

                        // Create the rectangle-rectangle Contact if needed.
                        if (mustCalculateContact && doCollidersIntersect)
                        {
                            const auto cA = rectA.Center(), cB = rectB.Center();
                            const auto halfSizeA = rectA.HalfSize(), halfSizeB = rectB.HalfSize();

                            const auto delta = cA - cB;
                            contactSolver.Point = cA + delta * 0.5f;

                            // Calculate the penetration in x-axis
                            const auto penetrationX = halfSizeA.X + halfSizeB.X - Math::Abs(delta.X);
                            // Calculate the penetration in y-axis
                            const auto penetrationY = halfSizeA.Y + halfSizeB.Y - Math::Abs(delta.Y);

                            if (penetrationX < penetrationY)
                            {
                                contactSolver.Normal = delta.X > 0 ? 
                                    Math::Vec2F::Right() : Math::Vec2F::Left();

                                contactSolver.Penetration = penetrationX;
                            }
                            else
                            {
                                contactSolver.Normal = delta.Y > 0 ?
                                    Math::Vec2F::Up() : Math::Vec2F::Down();

                                contactSolver.Penetration = penetrationY;
                            }
                        }

                        break;
                    } // Case rectangle B.

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                              bodyB.Position();

                        doCollidersIntersect = Math::Intersect(rectA, polygonB);
                        break;
                    } // Case polygon B.

                    case static_cast<int>(Math::ShapeType::None):
                        break;
                    default:
                        break;
                } // Switch shape collider B.

                break;
            } // Case rectangle A.

            case static_cast<int>(Math::ShapeType::Polygon):
            {
                const auto polygonA = std::get<Math::PolygonF>(colShapeA) +
                                      bodyA.Position();

                switch (colShapeB.index())
                {
                    case static_cast<int>(Math::ShapeType::Circle):
                    {
                        const auto circleB = std::get<Math::CircleF>(colShapeB) + bodyB.Position();

                        doCollidersIntersect = Math::Intersect(polygonA, circleB);
                        break;
                    } // Case circle B.

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                           bodyB.Position();

                        doCollidersIntersect = Math::Intersect(polygonA, rectB);
                        break;
                    } // Case rectangle B.

                    case static_cast<int>(Math::ShapeType::Polygon):
                    {
                        const auto polygonB = std::get<Math::PolygonF>(colShapeB) +
                                              bodyB.Position();

                        doCollidersIntersect = Math::Intersect(polygonA, polygonB);
                        break;
                    } // Case polygon B.

                    case static_cast<int>(Math::ShapeType::None):
                        break;
                    default:
                        break;
                } // Switch shape collider B.

                break;
            } // Case Polygon A.

            case static_cast<int>(Math::ShapeType::None):
                break;
            default:
                break;
        } // Switch shape collider A.

        return doCollidersIntersect;
    }

    void World::Deinit() noexcept
    {
#ifdef TRACY_ENABLE
        ZoneScoped;
#endif // TRACY_ENABLE
        _bodies.clear();
        _bodiesGenIndices.clear();

        _colliders.clear();
        _collidersGenIndices.clear();
        _colliderPairs.clear();

        _contactListener = nullptr;

        _quadTree.Deinit();
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