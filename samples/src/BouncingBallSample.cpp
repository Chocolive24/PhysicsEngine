#include "BouncingBallSample.h"
#include "Metrics.h"
#include "GraphicGeometry.h"
#include <iostream>

std::string BouncingBallSample::Description() const noexcept
{
    return std::string();
}

void BouncingBallSample::onInit() noexcept
{
    _gravity = Math::Vec2F(0.f, -9.f);
    _world.SetGravity(_gravity);

    _world.SetContactListener(this);

    _colliders.reserve(_startBodyCount);

    constexpr auto windowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(Window::WindowWidth, Window::WindowHeight));

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

    collider.SetRestitution(0.f);

    _colliders.push_back(colRef);
}

void BouncingBallSample::onHandleInputs(SDL_Event event, 
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

void BouncingBallSample::onUpdate() noexcept
{
    removeCollidersOutOfSBottomScreen();

  /*  const auto& collider = _world.GetCollider(_colliders.back());
    const auto& body = _world.GetBody(collider.GetBodyRef());


    std::cout << body.Velocity().X << " " << body.Velocity().Y << "\n";*/
}

void BouncingBallSample::onRender() noexcept
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

void BouncingBallSample::onDeinit() noexcept
{
    _colliders.clear();
}

void BouncingBallSample::OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void BouncingBallSample::OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void BouncingBallSample::OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void BouncingBallSample::OnCollisionEnter(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void BouncingBallSample::OnCollisionExit(PhysicsEngine::ColliderRef colliderRefA, 
    PhysicsEngine::ColliderRef colliderRefB) noexcept
{
}

void BouncingBallSample::createCircle(Math::Vec2F position) noexcept
{
    const auto bodyRef = _world.CreateBody();
    auto& body = _world.GetBody(bodyRef);
    body.SetPosition(position);
    body.SetBodyType(PhysicsEngine::BodyType::Dynamic);

    const auto colRef = _world.CreateCollider(bodyRef);
    auto& collider = _world.GetCollider(colRef);

    collider.SetShape(Math::CircleF(0.2f));

    collider.SetRestitution(1.f);
    collider.SetFriction(1.f);

    _colliders.push_back(colRef);
}

void BouncingBallSample::createRectangle(Math::Vec2F position) noexcept
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
    collider.SetFriction(1.f);

    _colliders.push_back(colRef);
}

void BouncingBallSample::removeCollidersOutOfSBottomScreen() noexcept
{
    constexpr auto windowSizeInMeters = Metrics::PixelsToMeters(
        Math::Vec2F(Window::WindowWidth, Window::WindowHeight));

    for (auto& colRef : _colliders)
    {
        auto& collider = _world.GetCollider(colRef);
        auto& body = _world.GetBody(collider.GetBodyRef());

        const auto& colShape = collider.Shape();

        switch (colShape.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
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

            case static_cast<int>(Math::ShapeType::Rectangle):
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
