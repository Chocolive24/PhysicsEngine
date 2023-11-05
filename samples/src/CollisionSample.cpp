#include "CollisionSample.h"
#include "GraphicGeometry.h"
#include "Metrics.h"
#include <iostream>

std::string CollisionSample::Description() const noexcept
{
    std::string_view description = R"(write this in string view please !!)";
    return static_cast<std::string>(description);
}

void CollisionSample::onInit() noexcept
{
    _world.SetContactListener(this);

    for (auto& colRef : _colliderRefs)
    {
        const auto bodyRef = _world.CreateBody();
        auto& body = _world.GetBody(bodyRef);

        colRef = _world.CreateCollider(bodyRef);
        auto& collider = _world.GetCollider(colRef);
        collider.SetShape(Math::CircleF(0.3f));
        collider.SetFriction(1.f);
        collider.SetRestitution(1.f);
    }

    const auto& collider1 = _world.GetCollider(_colliderRefs[0]);
    auto& body1 = _world.GetBody(collider1.GetBodyRef());
    body1.SetPosition(Math::Vec2F(2.f, -3.f));
    body1.SetVelocity(Math::Vec2F(1.f, 0.f));
    body1.SetMass(5.f);

    const auto& collider2 = _world.GetCollider(_colliderRefs[1]);
    auto& body2 = _world.GetBody(collider2.GetBodyRef());
    body2.SetPosition(Math::Vec2F(6.f, -3.f));
    body2.SetVelocity(Math::Vec2F(-1.f, 0.f));
    body2.SetMass(5.f);
}

void CollisionSample::onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept
{
}

void CollisionSample::onUpdate() noexcept
{
    maintainObjectsInWindow();

    float totalVel = 0.f;
    for (const auto& colRef : _colliderRefs)
    {
        const auto& collider = _world.GetCollider(colRef);
        const auto& body = _world.GetBody(collider.GetBodyRef());

        totalVel += body.Velocity().Length();
    }

    std::cout << totalVel << "\n";
}

void CollisionSample::onRender() noexcept
{
    for (const auto& colRef : _colliderRefs)
    {
        const auto& collider = _world.GetCollider(colRef);
        const auto position = _world.GetBody(collider.GetBodyRef()).Position();

        const auto colShape = collider.Shape();

        switch (colShape.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                const auto circle = std::get<Math::CircleF>(colShape) + position;
                GraphicGeometry::Circle(Metrics::MetersToPixels(circle.Center()), 
                                        Metrics::MetersToPixels(circle.Radius()), 
                                        30, 
                                        _noCollisionColor);
                break;
            }
        }
    }
}

void CollisionSample::onDeinit() noexcept
{
}

void CollisionSample::OnTriggerEnter(PhysicsEngine::ColliderRef ColliderRefA, 
                                     PhysicsEngine::ColliderRef ColliderRefB) noexcept
{
}

void CollisionSample::OnTriggerStay(PhysicsEngine::ColliderRef ColliderRefA, 
                                    PhysicsEngine::ColliderRef ColliderRefB) noexcept
{
}

void CollisionSample::OnTriggerExit(PhysicsEngine::ColliderRef ColliderRefA, 
                                    PhysicsEngine::ColliderRef ColliderRefB) noexcept
{
}

void CollisionSample::OnCollisionEnter(PhysicsEngine::ColliderRef ColliderRefA, 
                                       PhysicsEngine::ColliderRef ColliderRefB) noexcept
{
}

void CollisionSample::OnCollisionExit(PhysicsEngine::ColliderRef ColliderRefA, 
                                      PhysicsEngine::ColliderRef ColliderRefB) noexcept
{
}

void CollisionSample::maintainObjectsInWindow() noexcept
{
    const auto windowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(Window::WindowWidth, Window::WindowHeight));

    for (auto& colRef : _colliderRefs)
    {
        const auto colShape = _world.GetCollider(colRef).Shape();

        switch (colShape.index())
        {
        case static_cast<int>(Math::ShapeType::Circle):
        {
            const auto& collider = _world.GetCollider(colRef);
            auto& body = _world.GetBody(collider.GetBodyRef());
            const auto pos = body.Position();
            const auto velocity = body.Velocity();

            const auto radius = std::get<Math::CircleF>(colShape).Radius();

            if (pos.X + radius >= windowSizeInMeters.X)
            {
                body.SetPosition(Math::Vec2F(windowSizeInMeters.X - radius, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.X - radius <= 0)
            {
                body.SetPosition(Math::Vec2F(0 + radius, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.Y - radius <= windowSizeInMeters.Y)
            {
                body.SetPosition(Math::Vec2F(pos.X, windowSizeInMeters.Y + radius));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            if (pos.Y + radius >= 0)
            {
                body.SetPosition(Math::Vec2F(pos.X, 0 - radius));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            break;
        } // Case circle.

        //case static_cast<int>(Math::ShapeType::Rectangle):
        //{
        //    const auto halfSize = std::get<Math::RectangleF>(colShape).Size() * 0.5f;

        //    auto& body = _world.GetBody(colRef.BodyRef);
        //    const auto pos = body.Position();
        //    const auto velocity = body.Velocity();

        //    if (pos.X + halfSize.X >= windowSizeInMeters.X)
        //    {
        //        body.SetPosition(Math::Vec2F(windowSizeInMeters.X - halfSize.X, pos.Y));
        //        body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //    }

        //    if (pos.X - halfSize.X <= 0)
        //    {
        //        body.SetPosition(Math::Vec2F(0 + halfSize.X, pos.Y));
        //        body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //    }

        //    if (pos.Y - halfSize.Y <= windowSizeInMeters.Y)
        //    {
        //        body.SetPosition(Math::Vec2F(pos.X, windowSizeInMeters.Y + halfSize.Y));
        //        body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        //    }

        //    if (pos.Y + halfSize.Y >= 0)
        //    {
        //        body.SetPosition(Math::Vec2F(pos.X, 0 - halfSize.Y));
        //        body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        //    }

        //    break;
        //} // Case Rectangle.

        //case static_cast<int>(Math::ShapeType::Polygon):
        //{
        //    const auto& vertices = std::get<Math::PolygonF>(colShape).Vertices();
        //    auto& body = _world.GetBody(colRef.BodyRef);
        //    const auto pos = body.Position();
        //    const auto velocity = body.Velocity();

        //    for (auto& vertex : vertices)
        //    {
        //        if (pos.X + vertex.X >= windowSizeInMeters.X)
        //        {
        //            body.SetPosition(Math::Vec2F(windowSizeInMeters.X - vertex.X, pos.Y));
        //            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //        }

        //        if (pos.X - vertex.X <= 0)
        //        {
        //            body.SetPosition(Math::Vec2F(0 + vertex.X, pos.Y));
        //            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //        }

        //        if (pos.Y - vertex.Y <= windowSizeInMeters.Y)
        //        {
        //            body.SetPosition(Math::Vec2F(pos.X, windowSizeInMeters.Y + vertex.Y));
        //            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        //        }

        //        if (pos.Y + vertex.Y >= 0)
        //        {
        //            body.SetPosition(Math::Vec2F(pos.X, 0 - vertex.Y));
        //            body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
        //        }
        //    }
        //} // Case polygon.
        } // Switch case.
    } // For range.
}