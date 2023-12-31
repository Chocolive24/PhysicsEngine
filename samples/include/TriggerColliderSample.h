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
    static constexpr int _circleCount = 100;
    static constexpr int _rectangleCount = 100;
    static constexpr int _polygonCount = 100;
    static constexpr int _totalObjectCount = _circleCount + _rectangleCount + _polygonCount;

    static constexpr SDL_Color _noCollisionColor = {255, 0, 0, 255};
    static constexpr SDL_Color _collisionColor = {0, 255, 0, 255};

    std::vector<GameObject> _gameObjects;

    void addCircle(Math::Vec2F centerPos, Math::Vec2F rndVelocity) noexcept;
    void addRectangle(Math::Vec2F minBound, Math::Vec2F maxBound, Math::Vec2F rndVelocity) noexcept;
    void addPolygon(Math::Vec2F centerPos, const std::vector<Math::Vec2F>& vertices, Math::Vec2F rndVelocity) noexcept;

    void drawQuadNode(const PhysicsEngine::QuadNode& node) const noexcept;
    void maintainObjectsInWindow() noexcept;

public:
    TriggerColliderSample() noexcept = default;

    std::string Name() const noexcept override { return "Trigger colliders"; }

    std::string Description() const noexcept override;

    void onInit() noexcept override;
    void onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept override;
    void onUpdate() noexcept override;
    void onRender() noexcept override;
    void onDeinit() noexcept override;

    void OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA,
                       PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                       PhysicsEngine::ColliderRef colliderRefB) noexcept override;

   

    // Inherited via ContactListener
    void OnCollisionEnter(PhysicsEngine::ColliderRef colliderRefA, 
                          PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnCollisionExit(PhysicsEngine::ColliderRef colliderRefA, 
                         PhysicsEngine::ColliderRef colliderRefB) noexcept override;


    // Inherited via Sample
    std::string InputText() const noexcept override;

};