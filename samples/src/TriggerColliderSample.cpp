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

    for (auto& circle : _circleObjects)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(100.f, Window::WindowWidth - 100.f),
                                 Math::Random::Range(100.f, Window::WindowHeight - 100.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        addCircle(rndScreenPos, rndVelocity);
    }

    for (auto& rect : _rectangleObjects)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(100.f, Window::WindowWidth - 100.f),
                                 Math::Random::Range(100.f, Window::WindowHeight - 100.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        float rndSize = Math::Random::Range(30.f, 50.f);

        addRectangle(rndScreenPos, rndScreenPos + Math::Vec2F(rndSize, -rndSize), rndVelocity);
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

    maintainObjectsInWindow();

    _world.Update(_timer.DeltaTime());

    for (auto& circle : _circleObjects)
    {
        DrawableGeometry::Circle(
                Metrics::MetersToPixels(_world.GetBody(circle.BodyRef).Position()),
                circle.Circle.Radius(),
                50,
                circle.Color);
    }

    for (auto& rect : _rectangleObjects)
    {
        auto dimension = rect.Rect.MaxBound() - rect.Rect.MinBound();

        DrawableGeometry::Rectangle(Metrics::MetersToPixels(_world.GetBody(rect.BodyRef).Position()),
                                    dimension.X,
                                    dimension.Y,
                                    rect.Color);
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
    circle.Circle = Math::CircleF(centerPos, Math::Random::Range(15.f, 30.f));
    circle.Color = _noCollisionColor;

    // Body.
    auto& body = _world.GetBody(circle.BodyRef);
    body = PhysicsEngine::Body(
            Metrics::PixelsToMeters(circle.Circle.Center()),
            rndVelocity,
            1.f);

    // Collider.
    circle.ColRef = _world.CreateCircleCollider(circle.BodyRef);
    auto& collider = _world.GetCollider(circle.ColRef);
    collider.SetIsTrigger(true);
    _world.GetCircleCollider(collider.ShapeIdx()).SetRadius(
            Metrics::PixelsToMeters(circle.Circle.Radius()));
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
    body = PhysicsEngine::Body(Metrics::PixelsToMeters(rect.Rect.Center()),
                               rndVelocity,
                               1.f);

    // Collider.
    rect.ColRef = _world.CreateRectangleCollider(rect.BodyRef);
    auto& collider = _world.GetCollider(rect.ColRef);
    collider.SetIsTrigger(true);

    auto halfSize = rect.Rect.Size() / 2.f;

    _world.GetRectangleCollider(collider.ShapeIdx()).SetHalfSize(
            Metrics::PixelsToMeters(halfSize));
}

void TriggerColliderSample::maintainObjectsInWindow() noexcept
{
    for (auto& circle : _circleObjects)
    {
        auto radius = circle.Circle.Radius();

        auto& body = _world.GetBody(circle.BodyRef);
        auto posInPixels = Metrics::MetersToPixels(body.Position());
        auto velocity = body.Velocity();

        if (posInPixels.X + radius >= Window::WindowWidth || posInPixels.X - radius <= 0)
        {
            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (posInPixels.Y + radius >= Window::WindowHeight || posInPixels.Y - radius <= 0)
        {
            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }
    }

    for (auto& rect : _rectangleObjects)
    {
        const auto halfSize = rect.Rect.Size() / 2.f;

        auto& body = _world.GetBody(rect.BodyRef);
        auto posInPixels = Metrics::MetersToPixels(body.Position());
        auto velocity = body.Velocity();

        if (posInPixels.X + halfSize.X >= Window::WindowWidth || posInPixels.X - halfSize.X <= 0)
        {
            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        }

        if (posInPixels.Y - halfSize.Y >= Window::WindowHeight || posInPixels.Y + halfSize.Y <= 0)
        {
            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        }
    }
}
