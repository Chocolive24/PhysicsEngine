#include "GroundCollision.h"
#include "Metrics.h"
#include "GraphicGeometry.h"
#include <iostream>

std::string GroundCollisionSample::Description() const noexcept
{
    std::string_view description = R"(This sample shows collisions between bouncing shapes and a ground with gravity in the world.)";
    return static_cast<std::string>(description);
}

std::string GroundCollisionSample::InputText() const noexcept
{
    std::string_view description = R"(Inputs :
[Left-click] creates a circle.
[Right-click] creates a rectangle.)";
    return static_cast<std::string>(description);
}

void GroundCollisionSample::onInit() noexcept
{
    _gravity = Math::Vec2F(0.f, -9.f);
    _world.SetGravity(_gravity);

    _world.SetContactListener(this);

    _colliders.reserve(_startBodyCount);

    constexpr auto windowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(AppWindow::WindowWidth, AppWindow::WindowHeight));

    constexpr auto halfWindowSizeInMeters = windowSizeInMeters * 0.5f;

    // Create the static rectangle body.
    const auto bodyRef = _world.CreateBody();
    auto& body = _world.GetBody(bodyRef);
    body.SetPosition(Math::Vec2F(halfWindowSizeInMeters.X, windowSizeInMeters.Y));
    body.SetBodyType(PhysicsEngine::BodyType::Static);

    const auto colRef = _world.CreateCollider(bodyRef);
    auto& collider = _world.GetCollider(colRef);

    const auto size = Math::Vec2F(4, 2);
    const auto halfSize = size * 0.5f;
    collider.SetShape(Math::RectangleF(
        Math::Vec2F::Zero() - halfSize, Math::Vec2F::Zero() + halfSize));

    collider.SetRestitution(0.75f);

    _colliders.push_back(colRef);
}

void GroundCollisionSample::onHandleInputs(SDL_Event event, 
                                        bool isMouseOnAnImGuiWindow) noexcept
{
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            if (!isMouseOnAnImGuiWindow)
            {
                Math::Vec2I mousePosition;
                SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

                createCircle(Metrics::PixelsToMeters(static_cast<Math::Vec2F>(mousePosition)));
            }
        }

        if (event.button.button == SDL_BUTTON_RIGHT)
        {
            if (!isMouseOnAnImGuiWindow)
            {
                Math::Vec2I mousePosition;
                SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

                createRectangle(Metrics::PixelsToMeters(static_cast<Math::Vec2F>(mousePosition)));
            }
        }

        break;
    }
}

void GroundCollisionSample::onUpdate() noexcept
{
    removeCollidersOutOfSBottomScreen();
}

void GroundCollisionSample::onRender() noexcept
{
    for (const auto& colRef : _colliders)
    {
        const auto& collider = _world.GetCollider(colRef);
        const auto colShape = collider.Shape();

        switch (colShape.index())
        {
        case static_cast<int>(Math::ShapeType::Circle):
        {
            GraphicGeometry::Circle(
                Metrics::MetersToPixels(_world.GetBody(collider.GetBodyRef()).Position()),
                Metrics::MetersToPixels(std::get<Math::CircleF>(colShape).Radius()),
                GraphicGeometry::CircleSegmentCount,
                CircleColor);

            break;
        }

        case static_cast<int>(Math::ShapeType::Rectangle):
        {
            const auto color = colRef.Index == 0 ? GroundColor : RectangleColor;

            GraphicGeometry::FilledRectangle(
                Metrics::MetersToPixels(_world.GetBody(collider.GetBodyRef()).Position()),
                Metrics::MetersToPixels(std::get<Math::RectangleF>(colShape).Size()),
                color);

            break;
        }

        case static_cast<int>(Math::ShapeType::None):
            break;
        default:
            break;
        }
    }
}

void GroundCollisionSample::onDeinit() noexcept
{
    _colliders.clear();
}

void GroundCollisionSample::OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void GroundCollisionSample::OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void GroundCollisionSample::OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void GroundCollisionSample::OnCollisionEnter(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void GroundCollisionSample::OnCollisionExit(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void GroundCollisionSample::createCircle(Math::Vec2F position) noexcept
{
    const auto bodyRef = _world.CreateBody();
    auto& body = _world.GetBody(bodyRef);
    body.SetPosition(position);
    body.SetBodyType(PhysicsEngine::BodyType::Dynamic);

    const auto colRef = _world.CreateCollider(bodyRef);
    auto& collider = _world.GetCollider(colRef);

    collider.SetShape(Math::CircleF(0.2f));

    collider.SetRestitution(1.f);

    _colliders.push_back(colRef);
}

void GroundCollisionSample::createRectangle(Math::Vec2F position) noexcept
{
    const auto bodyRef = _world.CreateBody();
    auto& body = _world.GetBody(bodyRef);
    body.SetPosition(position);
    body.SetBodyType(PhysicsEngine::BodyType::Dynamic);

    const auto colRef = _world.CreateCollider(bodyRef);
    auto& collider = _world.GetCollider(colRef);

    const auto size = Math::Vec2F(0.4, 0.4);
    const auto halfSize = size * 0.5f;
    collider.SetShape(Math::RectangleF(
        Math::Vec2F::Zero() - halfSize, Math::Vec2F::Zero() + halfSize));

    collider.SetRestitution(1.f);

    _colliders.push_back(colRef);
}

void GroundCollisionSample::removeCollidersOutOfSBottomScreen() noexcept
{
    constexpr auto windowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(AppWindow::WindowWidth, AppWindow::WindowHeight));

    for (auto& colRef : _colliders)
    {
        auto& collider = _world.GetCollider(colRef);
        auto& body = _world.GetBody(collider.GetBodyRef());

        const auto& colShape = collider.Shape();

        switch (static_cast<Math::ShapeType>(colShape.index()))
        {
            case Math::ShapeType::Circle:
            {
                const auto radius = std::get<Math::CircleF>(colShape).Radius();

                if (body.Position().Y + radius < windowSizeInMeters.Y)
                {
                    _world.DestroyBody(collider.GetBodyRef());
                    _world.DestroyCollider(colRef);
                    
                    auto it = std::find(_colliders.begin(), _colliders.end(), colRef);

                    _colliders.erase(it);
                }

                break;
            }

            case Math::ShapeType::Rectangle:
            {
                const auto halfSize = std::get<Math::RectangleF>(colShape).HalfSize();

                if (body.Position().Y + halfSize.Y < windowSizeInMeters.Y)
                {
                    _world.DestroyBody(collider.GetBodyRef());
                    _world.DestroyCollider(colRef);

                    auto it = std::find(_colliders.begin(), _colliders.end(), colRef);

                    _colliders.erase(it);
                }

                break;
            }
        default:
            break;
        }
    }
}
