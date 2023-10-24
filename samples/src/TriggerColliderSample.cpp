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

    _circleObjects.resize(CircleNbr, CircleObject());
    _rectangleObjects.resize(RectangleNbr, RectangleObject());

    std::size_t index = 0;

    for (auto& circle : _circleObjects)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(100.f, Window::WindowWidth - 100.f),
                                 Math::Random::Range(100.f, Window::WindowHeight - 100.f));

        // Circle object.
        circle.BodyRef = _world.CreateBody();
        circle.Circle = Math::CircleF(rndScreenPos, Math::Random::Range(15.f, 30.f));
        circle.Color = _noCollisionColor;

        // Body.
        auto& body = _world.GetBody(circle.BodyRef);
        body = PhysicsEngine::Body(
                Metrics::PixelsToMeters(circle.Circle.Center()),
                Math::Vec2F::Zero(),
                1.f);

        // Collider.
        auto colRef = _world.CreateCircleCollider(circle.BodyRef);
        auto& collider = _world.GetCollider(colRef);
        collider.SetIsTrigger(true);
        _world.GetCircleCollider(collider.ShapeIdx()).SetRadius(
                Metrics::PixelsToMeters(circle.Circle.Radius()));

        _circleObjects[index] = circle;
        index++;
    }

//    _movingObj = {_world.CreateBody(), Math::RectangleF(Math::Vec2F::Zero(), Math::Vec2F(50, 50)),_noCollisionColor};
//    auto& body2 = _world.GetBody(_movingObj.BodyRef);
//    body2 = PhysicsEngine::Body(Math::Vec2F::Zero(), Math::Vec2F::Zero(), 100.f);
//
//    auto mColRef = _world.CreateRectangleCollider(_movingObj.BodyRef);
//    auto& mCollider = _world.GetCollider(mColRef);
//    mCollider.SetIsTrigger(true);
//    _world.GetRectangleCollider(mCollider.ShapeIdx()).SetHalfSize(
//            Metrics::PixelsToMeters((_movingObj.Rect.MaxBound() - _movingObj.Rect.MinBound()) / 2.f));

//    auto mColRef = _world.CreateRectangleCollider(_movingObj.BodyRef);
//    auto& mCollider = _world.GetCollider(mColRef);
//    mCollider.SetIsTrigger(true);
//    _world.GetRectangleCollider(mCollider.ShapeIdx()).SetHalfSize(
//            Metrics::PixelsToMeters(_movingObj.Radius));

    //_circleObjects.push_back(&_staticObj);
    //_rectangleObjects.push_back(&_staticObj);
    //_rectangleObjects.push_back(&_movingObj);
}

void TriggerColliderSample::HandleInputs(SDL_Event event) noexcept
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        std::cout << "INPUUUUUUTS" << "\n";
    }
}

void TriggerColliderSample::Update() noexcept
{
    _timer.Tick();

    Math::Vec2I mousePosition;
    SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

    auto mousePosF = static_cast<Math::Vec2F>(mousePosition);

    _world.Update(_timer.DeltaTime());

    for (auto& circle : _circleObjects)
    {
        DrawableGeometry::Circle(
                Metrics::MetersToPixels(_world.GetBody(circle.BodyRef).Position()),
                circle.Circle.Radius(),
                50,
                circle.Color);
    }

//    DrawableGeometry::Rectangle(
//            Metrics::MetersToPixels(sOBody.Position()),
//            50.f,
//            50.f,
//            _staticObj.Color);

//    DrawableGeometry::Circle(
//            Metrics::MetersToPixels(sOBody.Position()),
//            _staticObj.Radius / 2.f,
//            50,
//            {0, 255, 0, 0});

//    auto dimension = _movingObj.Rect.MaxBound() - _movingObj.Rect.MinBound();
//
//    DrawableGeometry::Rectangle(
//            Metrics::MetersToPixels(mOBody.Position()),
//            dimension.X,
//            dimension.Y,
//            _movingObj.Color);

//    DrawableGeometry::Circle(
//            Metrics::MetersToPixels(mOBody.Position()),
//            _movingObj.Radius / 2.f,
//            50,
//            {0, 255, 0, 0});

//    std::vector<Math::Vec2F> vertices = {mousePosF,
//                                         mousePosF + Math::Vec2F(150, 150),
//                                         mousePosF + Math::Vec2F(-100, 250),
//                                         mousePosF + Math::Vec2F(-25, 300),
//                                         mousePosF + Math::Vec2F(75, 467)};
//
//    DrawableGeometry::Polygon(vertices, {255, 0, 0, 255});
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
        if ((circleObj.BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
            circleObj.BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
        {
            circleObj.Color = _collisionColor;
        }
    }

    for (auto& rectObj : _rectangleObjects)
    {
        if ((rectObj.BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
             rectObj.BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
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
        if ((circleObj.BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
            circleObj.BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
        {
            circleObj.Color = _noCollisionColor;
        }
    }

    for (auto& rectObj : _rectangleObjects)
    {
        if ((rectObj.BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
            rectObj.BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
        {
            rectObj.Color = _noCollisionColor;
        }
    }
}