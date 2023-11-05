#include "CollisionSample.h"
#include "GraphicGeometry.h"
#include "Metrics.h"

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

    const auto& collider2 = _world.GetCollider(_colliderRefs[1]);
    auto& body2 = _world.GetBody(collider2.GetBodyRef());
    body2.SetPosition(Math::Vec2F(2.1f, -3.f));
}

void CollisionSample::onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept
{
}

void CollisionSample::onUpdate() noexcept
{
    
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
