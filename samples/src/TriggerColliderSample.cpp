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
        Math::Vec2F rndScreenPos(Math::Random::Range(1.f, windowSizeInMeters.X - 1.f),
                                 Math::Random::Range(-1.f, windowSizeInMeters.Y + 1.f));

        Math::Vec2F rndVelocity(Math::Random::Range(-2.f, 2.f),
                                Math::Random::Range(-2.f, 2.f));

        std::vector<Math::Vec2F> vertices = {
                Math::Vec2F(-0.3, -0.3), Math::Vec2F(0, 0.3), Math::Vec2F(0.3, -0.3)
        };

        addPolygon(rndScreenPos, vertices, rndVelocity);
    }
}

void TriggerColliderSample::HandleInputs(SDL_Event event) noexcept
{
    switch (event.type)
    {
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                Math::Vec2I mousePosition;
                SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

                auto mousePosF = static_cast<Math::Vec2F>(mousePosition);
                auto mM = Metrics::PixelsToMeters(mousePosF);

                addCircle(mM, Math::Vec2F::Zero());
            }
            break;
    }
}

void TriggerColliderSample::Update() noexcept
{
    _timer.Tick();

    Math::Vec2I mousePosition;
    SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

    auto mousePosF = static_cast<Math::Vec2F>(mousePosition);
    auto mM = Metrics::PixelsToMeters(mousePosF);

    maintainObjectsInWindow();

    //_world.GetBody(_gameObjects[_circleCount + _rectangleCount].BodyRef).SetPosition(mM);

    _world.Update(_timer.DeltaTime());

    for (auto& object : _gameObjects)
    {
        const auto colShape = _world.GetCollider(object.ColRef).Shape();

        switch (colShape.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                DrawableGeometry::Circle(
                        Metrics::MetersToPixels(_world.GetBody(object.BodyRef).Position()),
                        Metrics::MetersToPixels(std::get<Math::CircleF>(colShape).Radius()),
                        50,
                        object.CollisionNbr > 0 ? _collisionColor : _noCollisionColor);
                break;
            } // Case circle.

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                DrawableGeometry::FilledRectangle(
                        Metrics::MetersToPixels(_world.GetBody(object.BodyRef).Position()),
                        Metrics::MetersToPixels(std::get<Math::RectangleF>(colShape).Size()),
                        object.CollisionNbr > 0 ? _collisionColor : _noCollisionColor);
                break;
            } // Case rectangle.

            case static_cast<int>(Math::ShapeType::Polygon):
            {
                const auto poly = std::get<Math::PolygonF>(colShape);
                const auto verticesInMeters = poly.Vertices();

                // Convert vertices position from meters to pixels.
                std::vector<Math::Vec2F> _verticesInPixels;
                _verticesInPixels.reserve(verticesInMeters.size());

                for (auto& vertex : verticesInMeters)
                {
                    _verticesInPixels.push_back(Metrics::MetersToPixels(vertex));
                }

                DrawableGeometry::Polygon(
                        Metrics::MetersToPixels(_world.GetBody(object.BodyRef).Position()),
                        _verticesInPixels,
                        object.CollisionNbr > 0 ? _collisionColor : _noCollisionColor);

                break;
            } // Case polygon.
        } // Switch case.
    } // For gameObjects range.

    DrawQuadNode(_world.QuadTree().RootNode());
}

void TriggerColliderSample::Deinit() noexcept
{
    Sample::Deinit();
    _gameObjects.clear();
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
    collider.SetShape(Math::CircleF(Math::Vec2F::Zero(), Math::Random::Range(0.1f, 0.15f)));

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

void TriggerColliderSample::addPolygon(Math::Vec2F centerPos,
                                       const std::vector<Math::Vec2F>& vertices,
                                       Math::Vec2F rndVelocity) noexcept
{
    GameObject polygon;

    // Body.
    polygon.BodyRef = _world.CreateBody();
    auto& body = _world.GetBody(polygon.BodyRef);
    body = PhysicsEngine::Body(centerPos,rndVelocity,1.f);

    // Collider.
    polygon.ColRef = _world.CreateCollider(polygon.BodyRef);
    auto& collider = _world.GetCollider(polygon.ColRef);
    collider.SetIsTrigger(true);
    collider.SetShape(Math::PolygonF(vertices));

    _gameObjects.push_back(polygon);
}

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

                if (pos.X + radius >= windowSizeInMeters.X || pos.X - radius <= 0)
                {
                    body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
                }

                if (pos.Y - radius <= windowSizeInMeters.Y || pos.Y + radius >= 0)
                {
                    body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
                }
                break;
            } // Case circle.

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto halfSize = std::get<Math::RectangleF>(colShape).Size() * 0.5f;

                auto &body = _world.GetBody(object.BodyRef);
                const auto pos = body.Position();
                const auto velocity = body.Velocity();

                if (pos.X + halfSize.X >= windowSizeInMeters.X || pos.X - halfSize.X <= 0)
                {
                    body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
                }

                if (pos.Y - halfSize.Y <= windowSizeInMeters.Y || pos.Y + halfSize.Y >= 0)
                {
                    body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
                }
                break;
            } // Case Rectangle.

            case static_cast<int>(Math::ShapeType::Polygon):
            {
                const auto& vertices = std::get<Math::PolygonF>(colShape).Vertices();
                auto& body = _world.GetBody(object.BodyRef);
                const auto pos = body.Position();
                const auto velocity = body.Velocity();

                for (auto& vertex : vertices)
                {
                    if (pos.X + vertex.X >= windowSizeInMeters.X || pos.X - vertex.X  <= 0)
                    {
                        body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
                    }

                    if (pos.Y - vertex.Y <= windowSizeInMeters.Y || pos.Y + vertex.Y >= 0)
                    {
                        body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
                    }
                }
            } // Case polygon.
        } // Switch case.
    } // For range.
}

void TriggerColliderSample::DrawQuadNode(const PhysicsEngine::QuadNode& node) const noexcept
{
    if (node.Children[0] != nullptr)
    {
        for (const auto& child : node.Children)
        {
            DrawQuadNode(*child);
        }
    }

    const auto center = Metrics::MetersToPixels(node.Boundary.Center());
    auto size = Metrics::MetersToPixels(node.Boundary.Size());
    size.Y = -size.Y;
    constexpr SDL_Color boundaryColor{255, 255, 255, 255};
    DrawableGeometry::EmptyRectangle(center, size, boundaryColor);
}
