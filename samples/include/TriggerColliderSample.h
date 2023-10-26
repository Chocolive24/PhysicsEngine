#pragma once

#include "Sample.h"
#include "ContactListener.h"

struct GameObject
{
    PhysicsEngine::BodyRef BodyRef{};
    PhysicsEngine::ColliderRef ColRef{};
    int CollisionNbr = 0;
};

class TriggerColliderSample : public Sample, public PhysicsEngine::ContactListener
{
private:
    static constexpr int _circleCount = 10;
    static constexpr int _rectangleCount = 10;
    static constexpr int _polygonCount = 0;
    static constexpr int _totalObjectCount = _circleCount + _rectangleCount + _polygonCount;

    static constexpr SDL_Color _noCollisionColor = {255, 0, 0, 255};
    static constexpr SDL_Color _collisionColor = {0, 255, 0, 255};

    std::vector<GameObject> _gameObjects;

    void addCircle(Math::Vec2F centerPos, Math::Vec2F rndVelocity) noexcept;
    void addRectangle(Math::Vec2F minBound, Math::Vec2F maxBound, Math::Vec2F rndVelocity) noexcept;
    //void addPolygon(std::vector<Math::Vec2F>& vertices, Math::Vec2F rndVelocity) noexcept;

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