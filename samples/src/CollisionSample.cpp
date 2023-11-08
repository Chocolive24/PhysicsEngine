#include "CollisionSample.h"
#include "GraphicGeometry.h"
#include "Metrics.h"
#include "Random.h"

#include <iostream>

std::string CollisionSample::Description() const noexcept
{
    std::string_view description = R"(This sample shows the detection of physical collisions between circles. 
As soon as two circles collide, they are assigned a random color and collision calculations are performed.
All circles have the same mass and restitution. Collisions are therefore completely elastic, with no loss of energy.)";

    return static_cast<std::string>(description);
}

void CollisionSample::onInit() noexcept
{
    _world.SetContactListener(this);

    std::fill(_colors.begin(), _colors.end(), SDL_Color{255, 255, 255, 255});

    const auto AppWindowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(AppWindow::WindowWidth, AppWindow::WindowHeight));

    // Calculate the number of rows and columns in the grid based on the total object count
    int numRows = static_cast<int>(std::sqrt(TotalColliderCount));
    int numCols = TotalColliderCount / numRows;

    // Calculate the size of each grid cell
    Math::Vec2F cellSize(AppWindowSizeInMeters.X / numCols, AppWindowSizeInMeters.Y / numRows);

    for (std::size_t i = 0; i < TotalColliderCount; i++)
    {
        auto& colRef = _colliderRefs[i];

        const auto bodyRef = _world.CreateBody();
        auto& body = _world.GetBody(bodyRef);

        colRef = _world.CreateCollider(bodyRef);
        auto& collider = _world.GetCollider(colRef);

        if (i < CircleColliderCount)
        {
            collider.SetShape(Math::CircleF(0.2f));
            
        }
        else if (i - CircleColliderCount < RectColliderCount)
        {
            const auto size = Math::Vec2F(0.4f, 0.4f);
            const auto halfSize = size * 0.5f;

            collider.SetShape(Math::RectangleF(Math::Vec2F::Zero() - halfSize, 
                Math::Vec2F::Zero() + halfSize));
            
        }

        collider.SetFriction(1.f);
        collider.SetRestitution(1.f);

        // Calculate the position of the shape based on the grid cell
        int row = i / numCols;
        int col = i % numCols;
        Math::Vec2F cellPos(cellSize.X * col + cellSize.X / 2, cellSize.Y * row + cellSize.Y / 2);

        auto rndVel = Math::Vec2F(Math::Random::Range(-2.f, 2.f),
            Math::Random::Range(-2.f, 2.f));

        /*if (i == 0)
        {
            body.SetPosition(Math::Vec2F(2, -2));
            body.SetVelocity(Math::Vec2F(1, 0));
            body.SetBodyType(PhysicsEngine::BodyType::Static);
        }
        else
        {
            body.SetPosition(Math::Vec2F(4, -2));
            body.SetVelocity(Math::Vec2F(-1, 0));
        }*/

        body.SetPosition(cellPos);
        body.SetVelocity(rndVel);
        body.SetMass(5.f);
    }
}

void CollisionSample::onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiAppWindow) noexcept
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

    //std::cout << totalVel << "\n";
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
                    GraphicGeometry::CircleSegmentCount,
                    _colors[colRef.Index]);
                break;
            }
            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto rect = std::get<Math::RectangleF>(colShape) + position;
                GraphicGeometry::FilledRectangle(Metrics::MetersToPixels(rect.Center()),
                    Metrics::MetersToPixels(rect.Size()),
                    _colors[colRef.Index]);
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
    SDL_Color rndColor{ static_cast<Uint8>(Math::Random::Range(50.f, 255.f)),
                        static_cast<Uint8>(Math::Random::Range(50.f, 255.f)),
                        static_cast<Uint8>(Math::Random::Range(50.f, 255.f)),
                        255 };

    _colors[ColliderRefA.Index] = rndColor;
    _colors[ColliderRefB.Index] = rndColor;
}

void CollisionSample::OnCollisionExit(PhysicsEngine::ColliderRef ColliderRefA, 
                                      PhysicsEngine::ColliderRef ColliderRefB) noexcept
{

}

void CollisionSample::maintainObjectsInWindow() noexcept
{
    const auto AppWindowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(AppWindow::WindowWidth, AppWindow::WindowHeight));

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

            if (pos.X + radius >= AppWindowSizeInMeters.X)
            {
                body.SetPosition(Math::Vec2F(AppWindowSizeInMeters.X - radius, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.X - radius <= 0)
            {
                body.SetPosition(Math::Vec2F(0 + radius, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.Y - radius <= AppWindowSizeInMeters.Y)
            {
                body.SetPosition(Math::Vec2F(pos.X, AppWindowSizeInMeters.Y + radius));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            if (pos.Y + radius >= 0)
            {
                body.SetPosition(Math::Vec2F(pos.X, 0 - radius));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            break;
        } // Case circle.

        case static_cast<int>(Math::ShapeType::Rectangle):
        {
            const auto halfSize = std::get<Math::RectangleF>(colShape).Size() * 0.5f;

            const auto& collider = _world.GetCollider(colRef);
            auto& body = _world.GetBody(collider.GetBodyRef());
            const auto pos = body.Position();
            const auto velocity = body.Velocity();

            if (pos.X + halfSize.X >= AppWindowSizeInMeters.X)
            {
                body.SetPosition(Math::Vec2F(AppWindowSizeInMeters.X - halfSize.X, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.X - halfSize.X <= 0)
            {
                body.SetPosition(Math::Vec2F(0 + halfSize.X, pos.Y));
                body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
            }

            if (pos.Y - halfSize.Y <= AppWindowSizeInMeters.Y)
            {
                body.SetPosition(Math::Vec2F(pos.X, AppWindowSizeInMeters.Y + halfSize.Y));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            if (pos.Y + halfSize.Y >= 0)
            {
                body.SetPosition(Math::Vec2F(pos.X, 0 - halfSize.Y));
                body.SetVelocity(Math::Vec2F(velocity.X, -velocity.Y));
            }

            break;
        } // Case Rectangle.

        //case static_cast<int>(Math::ShapeType::Polygon):
        //{
        //    const auto& vertices = std::get<Math::PolygonF>(colShape).Vertices();
        //    auto& body = _world.GetBody(colRef.BodyRef);
        //    const auto pos = body.Position();
        //    const auto velocity = body.Velocity();

        //    for (auto& vertex : vertices)
        //    {
        //        if (pos.X + vertex.X >= AppWindowSizeInMeters.X)
        //        {
        //            body.SetPosition(Math::Vec2F(AppWindowSizeInMeters.X - vertex.X, pos.Y));
        //            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //        }

        //        if (pos.X - vertex.X <= 0)
        //        {
        //            body.SetPosition(Math::Vec2F(0 + vertex.X, pos.Y));
        //            body.SetVelocity(Math::Vec2F(-velocity.X, velocity.Y));
        //        }

        //        if (pos.Y - vertex.Y <= AppWindowSizeInMeters.Y)
        //        {
        //            body.SetPosition(Math::Vec2F(pos.X, AppWindowSizeInMeters.Y + vertex.Y));
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