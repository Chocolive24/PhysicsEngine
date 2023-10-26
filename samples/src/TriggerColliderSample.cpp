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

    const auto windowSizeInMeters = Metrics::PixelsToMeters(
            Math::Vec2F(Window::WindowWidth, Window::WindowHeight));

    _gameObjects.reserve(_totalObjectCount);

    for (std::size_t i = 0; i < _circleCount; i++)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, windowSizeInMeters.X - 1.f),
                                 Math::Random::Range(-1.f, windowSizeInMeters.Y + 1.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        addCircle(rndScreenPos, rndVelocity);
    }

    for (std::size_t i = 0; i < _rectangleCount; i++)
    {
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, windowSizeInMeters.X - 1.f),
                                 Math::Random::Range(-1.f, windowSizeInMeters.Y + 1.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        const auto rndSize = Math::Vec2F(Math::Random::Range(0.3f, 0.5f),
                                         Math::Random::Range(0.3f, 0.5f));

        addRectangle(rndScreenPos, rndSize, rndVelocity);
    }

    for (std::size_t i = 0; i < _polygonCount; i++)
    {
        std::vector<Math::Vec2F> vertices = {
                Math::Vec2F(0, -0.2), Math::Vec2F(2, -0.2), Math::Vec2F(1.5, -2)
        };

        //addPolygon(vertices, Math::Vec2F(1, -1));
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

    _world.GetBody(_gameObjects[0].BodyRef).SetPosition(mM);

    _world.Update(_timer.DeltaTime());

    for (auto& object : _gameObjects)
    {
        const auto colShape = _world.GetCollider(object.ColRef).Shape();

        switch (colShape.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
                DrawableGeometry::Circle(
                        Metrics::MetersToPixels(_world.GetBody(object.BodyRef).Position()),
                        Metrics::MetersToPixels(std::get<Math::CircleF>(colShape).Radius()),
                        50,
                        object.CollisionNbr > 0 ? _collisionColor : _noCollisionColor);
                break;
            case static_cast<int>(Math::ShapeType::Rectangle):
                DrawableGeometry::Rectangle(
                        Metrics::MetersToPixels(_world.GetBody(object.BodyRef).Position()),
                        Metrics::MetersToPixels(std::get<Math::RectangleF>(colShape).Size()),
                        object.CollisionNbr > 0 ? _collisionColor : _noCollisionColor);
        }
    }

//    for (auto& poly : _polygonObjects)
//    {
//        const auto centerPos = Metrics::MetersToPixels(_world.GetBody(poly.BodyRef).Position());
//
//        std::vector<Math::Vec2F> verticesInPixels;
//
//        for (auto& vertex : poly.Polygon.Vertices())
//        {
//            verticesInPixels.push_back(Metrics::MetersToPixels(vertex));
//        }
//
//        DrawableGeometry::Polygon(centerPos, verticesInPixels, poly.Color);
//    }
}

void TriggerColliderSample::Deinit() noexcept
{
    Sample::Deinit();
}

void TriggerColliderSample::OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                                           PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    for (auto& object : _gameObjects)
    {
        if (object.ColRef == colliderRefA || object.ColRef == colliderRefB)
        {
            object.CollisionNbr++;
        }
    }
}

void TriggerColliderSample::OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA,
                                          PhysicsEngine::ColliderRef colliderRefB) noexcept
{

}

void TriggerColliderSample::OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                                          PhysicsEngine::ColliderRef colliderRefB) noexcept
{
    for (auto& object : _gameObjects)
    {
        if (object.ColRef == colliderRefA || object.ColRef == colliderRefB)
        {
            object.CollisionNbr--;
        }
    }
}

void TriggerColliderSample::addCircle(Math::Vec2F centerPos, Math::Vec2F rndVelocity) noexcept
{
    GameObject circle;

    // Body.
    circle.BodyRef = _world.CreateBody();
    auto& body = _world.GetBody(circle.BodyRef);
    body = PhysicsEngine::Body(centerPos, rndVelocity, 1.f);

    // Collider.
    circle.ColRef = _world.CreateCollider(circle.BodyRef);
    auto& collider = _world.GetCollider(circle.ColRef);
    collider.SetIsTrigger(true);
    collider.SetShape(Math::CircleF(Math::Vec2F::Zero(), Math::Random::Range(0.15f, 0.3f)));

    _gameObjects.push_back(circle);
}

void TriggerColliderSample::addRectangle(Math::Vec2F centerPos, Math::Vec2F size, Math::Vec2F rndVelocity) noexcept
{
    GameObject rect;

    // Body.
    rect.BodyRef = _world.CreateBody();
    auto& body = _world.GetBody(rect.BodyRef);
    body = PhysicsEngine::Body(centerPos, rndVelocity, 1.f);

    // Collider.
    rect.ColRef = _world.CreateCollider(rect.BodyRef);
    auto& collider = _world.GetCollider(rect.ColRef);
    collider.SetIsTrigger(true);

    auto halfSize = size * 0.5f;

    collider.SetShape(Math::RectangleF(
            Math::Vec2F::Zero() - halfSize, Math::Vec2F::Zero() + halfSize));

    _gameObjects.push_back(rect);
}
//
//void TriggerColliderSample::addPolygon(std::vector<Math::Vec2F>& vertices, Math::Vec2F rndVelocity) noexcept
//{
//    auto it = std::find_if(
//            _polygonObjects.begin(),
//            _polygonObjects.end(),
//            [](const PolygonObject& polyObj)
//            {
//                return polyObj.Polygon.VerticesCount() < 3;
//            });
//
//    std::size_t index = -1;
//
//    if (it != _polygonObjects.end())
//    {
//        index = std::distance(_polygonObjects.begin(), it);
//    }
//
//    auto& polygon = _polygonObjects[index];
//
//    // Rectangle object.
//    polygon.BodyRef = _world.CreateBody();
//    polygon.Polygon = Math::PolygonF(vertices);
//    polygon.Color = _noCollisionColor;
//
//    // Body.
//    auto& body = _world.GetBody(polygon.BodyRef);
//    body = PhysicsEngine::Body(Metrics::PixelsToMeters(polygon.Polygon.Center()),
//                               rndVelocity,
//                               1.f);
//
//    // Collider.
//    polygon.ColRef = _world.CreateCollider(polygon.BodyRef);
//    auto& collider = _world.GetCollider(polygon.ColRef);
//    collider.SetIsTrigger(true);
//
//    std::vector<Math::Vec2F> verticesInMeters;
//
//    for (auto& vertex : polygon.Polygon.Vertices())
//    {
//        verticesInMeters.push_back(Metrics::PixelsToMeters(vertex));
//    }
//
//    //_world.GetPolygonCollider(collider.ShapeIdx()).SetVertices(verticesInMeters);
//}

void TriggerColliderSample::maintainObjectsInWindow() noexcept
{
    const auto windowSizeInMeters = Metrics::PixelsToMeters(
            Math::Vec2F(Window::WindowWidth, Window::WindowHeight));

    for (auto &object: _gameObjects)
    {
        const auto colShape = _world.GetCollider(object.ColRef).Shape();

        switch (colShape.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                auto &body = _world.GetBody(object.BodyRef);
                const auto pos = body.Position();
                const auto velocity = body.Velocity();

                const auto radius = std::get<Math::CircleF>(colShape).Radius();

                if (pos.X + radius >= windowSizeInMeters.X || pos.X - radius <= 0) {
                    body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
                }

                if (pos.Y - radius <= windowSizeInMeters.Y || pos.Y + radius >= 0) {
                    body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
                }
                break;
            } // Circle case.

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto halfSize = std::get<Math::RectangleF>(colShape).Size() * 0.5f;

                auto &body = _world.GetBody(object.BodyRef);
                const auto pos = body.Position();
                const auto velocity = body.Velocity();

                if (pos.X + halfSize.X >= windowSizeInMeters.X || pos.X - halfSize.X <= 0) {
                    body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
                }

                if (pos.Y - halfSize.Y <= windowSizeInMeters.Y || pos.Y + halfSize.Y >= 0) {
                    body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
                }
                break;
            } // Rectangle case.
        } // switch case.

//    for (auto& poly : _polygonObjects)
//    {
//        auto& body = _world.GetBody(poly.BodyRef);
//        const auto pos = body.Position();
//        auto velocity = body.Velocity();
//
//        for (auto& vertex : poly.Polygon.Vertices())
//        {
//            Math::Vec2F updatedVertex = pos + vertex;
//
//            auto vertexPosInPixels = Metrics::MetersToPixels(updatedVertex);
//
//            if (vertexPosInPixels.X >= Window::WindowWidth || vertexPosInPixels.X <= 0)
//            {
//                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
//            }
//
//            if (vertexPosInPixels.Y >= Window::WindowHeight || vertexPosInPixels.Y <= 0)
//            {
//                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
//            }
//        }
    } // For range.
}