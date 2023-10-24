//
// Created by Olivier on 20.10.2023.
//

#include "TriggerColliderSample.h"
#include "Metrics.h"
#include "DrawableGeometry.h"
#include "Window.h"
#include "Random.h"

#include <iostream>

void TriggerColliderSample::Init() noexcept
{
    Sample::Init();

    _world.SetContactListener(this);

    _circleObjects.resize(_circleNumber, CircleObject());
    _rectangleObjects.resize(_rectangleNbr, RectangleObject());
    _polygonObjects.resize(_polygonNbr, PolygonObject());

    const auto windowSizeInMeters = Metrics::PixelsToMeters(
            Math::Vec2F(Window::WindowWidth,Window::WindowHeight));

    for (auto& circle : _circleObjects)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, windowSizeInMeters.X - 1.f),
                                 Math::Random::Range(-1.f, windowSizeInMeters.Y + 1.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        addCircle(rndScreenPos, rndVelocity);
    }

    for (auto& rect : _rectangleObjects)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, windowSizeInMeters.X - 1.f),
                                 Math::Random::Range(-1.f, windowSizeInMeters.Y + 1.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        float rndSize = Math::Random::Range(0.3f, 0.5f);

        addRectangle(rndScreenPos, rndScreenPos + Math::Vec2F(rndSize, -rndSize), rndVelocity);
    }

    for (auto& poly : _polygonObjects)
    {
        std::vector<Math::Vec2F> vertices = {
                Math::Vec2F(0, -0.2), Math::Vec2F(2, -0.2), Math::Vec2F(1.5, -2)
        };

        addPolygon(vertices, Math::Vec2F(1, -1));
    }
}

void TriggerColliderSample::HandleInputs(SDL_Event event) noexcept
{

}

void TriggerColliderSample::Update() noexcept
{
    _timer.Tick();

    Math::Vec2I mousePosition;
    SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

    auto mousePosF = static_cast<Math::Vec2F>(mousePosition);

    auto mM = Metrics::PixelsToMeters(mousePosF);

    maintainObjectsInWindow();

    _world.Update(_timer.DeltaTime());

    for (auto& circle : _circleObjects)
    {
        DrawableGeometry::Circle(
                Metrics::MetersToPixels(_world.GetBody(circle.BodyRef).Position()),
                Metrics::MetersToPixels(circle.Circle.Radius()),
                50,
                circle.Color);
    }

    for (auto& rect : _rectangleObjects)
    {
        auto dimension = Metrics::MetersToPixels(rect.Rect.MaxBound() - rect.Rect.MinBound());

        DrawableGeometry::Rectangle(Metrics::MetersToPixels(_world.GetBody(rect.BodyRef).Position()),
                                    dimension.X,
                                    dimension.Y,
                                    rect.Color);
    }

    for (auto& poly : _polygonObjects)
    {
        const auto centerPos = Metrics::MetersToPixels(_world.GetBody(poly.BodyRef).Position());

        std::vector<Math::Vec2F> verticesInPixels;

        for (auto& vertex : poly.Polygon.Vertices())
        {
            verticesInPixels.push_back(Metrics::MetersToPixels(vertex));
        }

        DrawableGeometry::Polygon(centerPos, verticesInPixels, poly.Color);
    }
}

void TriggerColliderSample::Deinit() noexcept
{
    Sample::Deinit();
}

void TriggerColliderSample::OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                                           PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    auto& colliderA = _world.GetCollider(colliderRefA);
    auto& colliderB = _world.GetCollider(colliderRefB);

    for (auto& circleObj : _circleObjects)
    {
        if ((circleObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
             circleObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            circleObj.Color = _collisionColor;
        }
    }

    for (auto& rectObj : _rectangleObjects)
    {
        if ((rectObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
             rectObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            rectObj.Color = _collisionColor;
        }
    }

    for (auto& polyObj : _polygonObjects)
    {
        if ((polyObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
             polyObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            polyObj.Color = _collisionColor;
        }
    }
}

void TriggerColliderSample::OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA,
                                          PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    auto& colliderA = _world.GetCollider(colliderRefA);
    auto& colliderB = _world.GetCollider(colliderRefB);

    for (auto& circleObj : _circleObjects)
    {
        if ((circleObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
            circleObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            circleObj.Color = _collisionColor;
        }
    }

    for (auto& rectObj : _rectangleObjects)
    {
        if ((rectObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
            rectObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            rectObj.Color = _collisionColor;
        }
    }

    for (auto& polyObj : _polygonObjects)
    {
        if ((polyObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
            polyObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            polyObj.Color = _collisionColor;
        }
    }
}

void TriggerColliderSample::OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                                          PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    auto& colliderA = _world.GetCollider(colliderRefA);
    auto& colliderB = _world.GetCollider(colliderRefB);

    for (auto& circleObj : _circleObjects)
    {
        if ((circleObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
             circleObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            circleObj.Color = _noCollisionColor;
        }
    }

    for (auto& rectObj : _rectangleObjects)
    {
        if ((rectObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
             rectObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            rectObj.Color = _noCollisionColor;
        }
    }

    for (auto& polyObj : _polygonObjects)
    {
        if ((polyObj.ColRef == colliderRefA && colliderA.IsTrigger()) ||
            polyObj.ColRef == colliderRefB && colliderB.IsTrigger())
        {
            polyObj.Color = _collisionColor;
        }
    }
}

void TriggerColliderSample::addCircle(Math::Vec2F centerPos, Math::Vec2F rndVelocity) noexcept
{
    auto it = std::find_if(
            _circleObjects.begin(),
            _circleObjects.end(),
            [](const CircleObject& circleObj)
    {
        return circleObj.Circle.Radius() <= 0;
    });

    std::size_t index = -1;

    if (it != _circleObjects.end())
    {
        index = std::distance(_circleObjects.begin(), it);
    }
    else
    {
        std::size_t previousSize = _circleObjects.size();
        auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _objectAllocResizeFactor);

        _circleObjects.resize(newSize, CircleObject());

        index = previousSize;
    }
    auto& circle = _circleObjects[index];

    // Circle object.
    circle.BodyRef = _world.CreateBody();
    circle.Circle = Math::CircleF(centerPos, Math::Random::Range(0.15f, 0.3f));
    circle.Color = _noCollisionColor;

    // Body.
    auto& body = _world.GetBody(circle.BodyRef);
    body = PhysicsEngine::Body(circle.Circle.Center(),rndVelocity,1.f);

    // Collider.
    circle.ColRef = _world.CreateCircleCollider(circle.BodyRef);
    auto& collider = _world.GetCollider(circle.ColRef);
    collider.SetIsTrigger(true);
    _world.GetCircleCollider(collider.ShapeIdx()).SetRadius(circle.Circle.Radius());
}

void TriggerColliderSample::addRectangle(Math::Vec2F minBound, Math::Vec2F maxBound, Math::Vec2F rndVelocity) noexcept
{
    auto it = std::find_if(
            _rectangleObjects.begin(),
            _rectangleObjects.end(),
            [](const RectangleObject& rectObj)
            {
                return rectObj.Rect.Size().X <= 0;
            });

    std::size_t index = -1;

    if (it != _rectangleObjects.end())
    {
        index = std::distance(_rectangleObjects.begin(), it);
    }
    else
    {
        std::size_t previousSize = _rectangleObjects.size();
        auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _objectAllocResizeFactor);

        _rectangleObjects.resize(newSize, RectangleObject());

        index = previousSize;
    }
    auto& rect = _rectangleObjects[index];

    // Rectangle object.
    rect.BodyRef = _world.CreateBody();
    rect.Rect = Math::RectangleF (minBound, maxBound);
    rect.Color = _noCollisionColor;

    // Body.
    auto& body = _world.GetBody(rect.BodyRef);
    body = PhysicsEngine::Body(rect.Rect.Center(),rndVelocity,1.f);

    // Collider.
    rect.ColRef = _world.CreateRectangleCollider(rect.BodyRef);
    auto& collider = _world.GetCollider(rect.ColRef);
    collider.SetIsTrigger(true);

    auto halfSize = rect.Rect.Size() / 2.f;

    _world.GetRectangleCollider(collider.ShapeIdx()).SetHalfSize(halfSize);
}

void TriggerColliderSample::addPolygon(std::vector<Math::Vec2F>& vertices, Math::Vec2F rndVelocity) noexcept
{
    auto it = std::find_if(
            _polygonObjects.begin(),
            _polygonObjects.end(),
            [](const PolygonObject& polyObj)
            {
                return polyObj.Polygon.VerticesCount() < 3;
            });

    std::size_t index = -1;

    if (it != _polygonObjects.end())
    {
        index = std::distance(_polygonObjects.begin(), it);
    }
    else
    {
        std::size_t previousSize = _polygonObjects.size();
        auto newSize = static_cast<std::size_t>(static_cast<float>(previousSize) * _objectAllocResizeFactor);

        _polygonObjects.resize(newSize, PolygonObject());

        index = previousSize;
    }
    auto& polygon = _polygonObjects[index];

    // Rectangle object.
    polygon.BodyRef = _world.CreateBody();
    polygon.Polygon = Math::PolygonF(vertices);
    polygon.Color = _noCollisionColor;

    // Body.
    auto& body = _world.GetBody(polygon.BodyRef);
    body = PhysicsEngine::Body(Metrics::PixelsToMeters(polygon.Polygon.Center()),
                               rndVelocity,
                               1.f);

    // Collider.
    polygon.ColRef = _world.CreatePolygonCollider(polygon.BodyRef);
    auto& collider = _world.GetCollider(polygon.ColRef);
    collider.SetIsTrigger(true);

    std::vector<Math::Vec2F> verticesInMeters;

    for (auto& vertex : polygon.Polygon.Vertices())
    {
        verticesInMeters.push_back(Metrics::PixelsToMeters(vertex));
    }

    _world.GetPolygonCollider(collider.ShapeIdx()).SetVertices(verticesInMeters);
}

void TriggerColliderSample::maintainObjectsInWindow() noexcept
{
    const auto windowSizeInMeters = Metrics::PixelsToMeters(
            Math::Vec2F(Window::WindowWidth,Window::WindowHeight));

    for (auto& circle : _circleObjects)
    {
        auto radius = circle.Circle.Radius();

        auto& body = _world.GetBody(circle.BodyRef);
        auto pos = body.Position();
        auto velocity = body.Velocity();

        if (pos.X + radius >= windowSizeInMeters.X || pos.X - radius <= 0)
        {
            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (pos.Y - radius <= windowSizeInMeters.Y || pos.Y + radius >= 0)
        {
            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }
    }

    for (auto& rect : _rectangleObjects)
    {
        const auto halfSize = rect.Rect.Size() / 2.f;

        auto& body = _world.GetBody(rect.BodyRef);
        const auto pos = body.Position();
        auto velocity = body.Velocity();

        if (pos.X + halfSize.X >= windowSizeInMeters.X || pos.X - halfSize.X <= 0)
        {
            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (pos.Y + halfSize.Y <= windowSizeInMeters.Y || pos.Y - halfSize.Y >= 0)
        {
            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }
    }

    for (auto& poly : _polygonObjects)
    {
        auto& body = _world.GetBody(poly.BodyRef);
        const auto pos = body.Position();
        auto velocity = body.Velocity();

        for (auto& vertex : poly.Polygon.Vertices())
        {
            Math::Vec2F updatedVertex = pos + vertex;

            auto vertexPosInPixels = Metrics::MetersToPixels(updatedVertex);

            if (vertexPosInPixels.X >= Window::WindowWidth || vertexPosInPixels.X <= 0)
            {
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (vertexPosInPixels.Y >= Window::WindowHeight || vertexPosInPixels.Y <= 0)
            {
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }
        }
    }
}