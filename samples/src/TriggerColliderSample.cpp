//
// Created by Olivier on 20.10.2023.
//

#include "TriggerColliderSample.h"
#include "Metrics.h"
#include "DrawableGeometry.h"

#include <iostream>

void TriggerColliderSample::Init() noexcept
{
    Sample::Init();

    _world.SetContactListener(this);

    constexpr Math::Vec2F centerOfScreen(Window::WindowWidth / 2.f, Window::WindowHeight / 2.f);
    constexpr Math::Vec2F sunPos = Metrics::PixelsToMeters(centerOfScreen);

    _staticObj = {_world.CreateBody(), Math::CircleF(sunPos, 30.f), _noCollisionColor};
    auto& body = _world.GetBody(_staticObj.BodyRef);
    body = PhysicsEngine::Body(sunPos, Math::Vec2F::Zero(), 100.f);

    auto sColRef = _world.CreateCircleCollider(_staticObj.BodyRef);
    auto& sCollider = _world.GetCollider(sColRef);
    sCollider.SetIsTrigger(true);
    _world.GetCircleCollider(sCollider.ShapeIdx()).SetRadius(
            Metrics::PixelsToMeters(_staticObj.Circle.Radius()));

    _movingObj = {_world.CreateBody(), Math::CircleF(Math::Vec2F::Zero(), 20.f),_noCollisionColor};
    auto& body2 = _world.GetBody(_movingObj.BodyRef);
    body2 = PhysicsEngine::Body(Math::Vec2F::Zero(), Math::Vec2F::Zero(), 100.f);

    auto mColRef = _world.CreateCircleCollider(_movingObj.BodyRef);
    auto& mCollider = _world.GetCollider(mColRef);
    mCollider.SetIsTrigger(true);
    _world.GetCircleCollider(mCollider.ShapeIdx()).SetRadius(
            Metrics::PixelsToMeters(_movingObj.Circle.Radius()));

//    auto mColRef = _world.CreateRectangleCollider(_movingObj.BodyRef);
//    auto& mCollider = _world.GetCollider(mColRef);
//    mCollider.SetIsTrigger(true);
//    _world.GetRectangleCollider(mCollider.ShapeIdx()).SetHalfSize(
//            Metrics::PixelsToMeters(_movingObj.Radius));

    _circleObjects.push_back(&_staticObj);
    _circleObjects.push_back(&_movingObj);
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

    auto& sOBody = _world.GetBody(_staticObj.BodyRef);
    auto& mOBody = _world.GetBody(_movingObj.BodyRef);

    Math::Vec2I mousePosition;
    SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

    auto mousePosF = static_cast<Math::Vec2F>(mousePosition);

    mOBody.SetPosition(Metrics::PixelsToMeters(mousePosF));

    _world.Update(_timer.DeltaTime());

    DrawableGeometry::Circle(
            Metrics::MetersToPixels(sOBody.Position()),
            _staticObj.Circle.Radius(),
            50,
            _staticObj.Color);

//    DrawableGeometry::Circle(
//            Metrics::MetersToPixels(sOBody.Position()),
//            _staticObj.Radius / 2.f,
//            50,
//            {0, 255, 0, 0});

    DrawableGeometry::Circle(
            Metrics::MetersToPixels(mOBody.Position()),
            _movingObj.Circle.Radius(),
            50,
            _movingObj.Color);

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
        if ((circleObj->BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
             circleObj->BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
        {
            circleObj->Color = _collisionColor;
        }
    }

    //TODO: For auto rect in rectobjects
}

void TriggerColliderSample::OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                                          PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    auto& colliderA = _world.GetCollider(colliderRefA);
    auto& colliderB = _world.GetCollider(colliderRefB);

    for (auto& circleObj : _circleObjects)
    {
        if ((circleObj->BodyRef == colliderA.GetBodyRef() && colliderA.IsTrigger()) ||
             circleObj->BodyRef == colliderB.GetBodyRef() && colliderB.IsTrigger())
        {
            circleObj->Color = _noCollisionColor;
        }
    }
}
