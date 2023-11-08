/**
 * @author Olivier
 */

#include "World.h"

#ifdef TRACY_ENABLE
#include <Tracy.hpp>
#include <TracyC.h>
#endif // TRACY_ENABLE

#include <iostream>

namespace PhysicsEngine
{
    void World::Init(Math::Vec2F gravity, int preallocatedBodyCount) noexcept
    {
#ifdef TRACY_ENABLE
        ZoneScoped;
#endif // TRACY_ENABLE

        _gravity = gravity;

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

            switch (body.GetBodyType())
            {
                case BodyType::Dynamic:
                {
                    body.ApplyForce(_gravity);

                    // a = F / m
                    // TODO: * inverMass -> pour opti un peu.
                    Math::Vec2F acceleration = body.Forces() / body.Mass();

                    // Change velocity according to delta time.
                    body.SetVelocity(body.Velocity() + acceleration * deltaTime);

                    // Change position according to velocity and delta time.
                    body.SetPosition(body.Position() + body.Velocity() * deltaTime);

                    body.ResetForces();

                    break;
                }

                case BodyType::Kinematic:
                {
                    // Kinematic bodies are not impacted by forces.

                    // Change position according to velocity and delta time.
                    body.SetPosition(body.Position() + body.Velocity() * deltaTime);

                    break;
                }

                case BodyType::Static:
                    break;
                case BodyType::None:
                    break;
            }
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

        // todo: transformer en vector et tester.
        //std::unordered_set<ColliderPair, ColliderHash> newColliderPairs;

        const auto& newPossiblePairs = _quadTree.PossiblePairs();

        for (const auto& possiblePair : newPossiblePairs)
        {
            auto& colliderA = _colliders[possiblePair.ColliderA.Index];
            auto& colliderB = _colliders[possiblePair.ColliderB.Index];

            ContactSolver contactSolver;

            auto& bodyA = GetBody(colliderA.GetBodyRef());
            auto& bodyB = GetBody(colliderB.GetBodyRef());

            contactSolver.bodyA = &bodyA;
            contactSolver.bodyB = &bodyB;
            contactSolver.colliderA = &colliderA;
            contactSolver.colliderB = &colliderB;
            
            const auto doCollidersIntersect = detectContact(colliderA, colliderB);

            auto it = _colliderPairs.find(possiblePair);

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
                    if (colliderA.IsTrigger() || colliderB.IsTrigger())
                    {
                        _contactListener->OnTriggerStay(possiblePair.ColliderA,
                            possiblePair.ColliderB);
                    }
                    else
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

    bool World::detectContact(const Collider& colA, const Collider& colB) noexcept
    {
    #ifdef TRACY_ENABLE
            ZoneScoped;
    #endif
        auto& bodyA = GetBody(colA.GetBodyRef());
        auto& bodyB = GetBody(colB.GetBodyRef());

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

                        break;
                    } // Case circle B.
                    
                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        doCollidersIntersect = Math::Intersect(circleA, rectB);

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

                        break;
                    } // Case circle B.

                    case static_cast<int>(Math::ShapeType::Rectangle):
                    {
                        const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                                bodyB.Position();

                        doCollidersIntersect = Math::Intersect(rectA, rectB);

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