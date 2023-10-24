#pragma once

#include "Sample.h"
#include "ContactListener.h"

struct GameObject
{
    PhysicsEngine::BodyRef BodyRef{};
    PhysicsEngine::ColliderRef ColRef{};
    SDL_Color Color{};
};

struct CircleObject : public GameObject
{
    Math::CircleF Circle{Math::Vec2F::Zero(), 0.f};
};

struct RectangleObject : GameObject
{
    Math::RectangleF Rect{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
};

struct PolygonObject : GameObject
{
    Math::PolygonF Polygon{{Math::Vec2F::Zero()}};
};

class TriggerColliderSample : public Sample, public PhysicsEngine::ContactListener
{
private:
    static constexpr int _circleNumber = 10;
    static constexpr int _rectangleNbr = 10;
    static constexpr int _polygonNbr = 0;

    static constexpr SDL_Color _noCollisionColor = {255, 0, 0, 255};
    static constexpr SDL_Color _collisionColor = {0, 255, 0, 255};

    static constexpr float _objectAllocResizeFactor = 2.f;

    std::vector<CircleObject> _circleObjects{};
    std::vector<RectangleObject> _rectangleObjects{};
    std::vector<PolygonObject> _polygonObjects{};

    void addCircle(Math::Vec2F centerPos, Math::Vec2F rndVelocity) noexcept;
    void addRectangle(Math::Vec2F minBound, Math::Vec2F maxBound, Math::Vec2F rndVelocity) noexcept;
    void addPolygon(std::vector<Math::Vec2F>& vertices, Math::Vec2F rndVelocity) noexcept;

    void maintainObjectsInWindow() noexcept;

public:
    explicit TriggerColliderSample() noexcept = default;

    void Init() noexcept override;
    void HandleInputs(SDL_Event event) noexcept override;
    void Update() noexcept override;
    void Deinit() noexcept override;

    void OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA,
                       PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                       PhysicsEngine::ColliderRef colliderRefB) noexcept override;
};