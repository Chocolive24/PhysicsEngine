#pragma once

#include "Sample.h"
#include "ContactListener.h"

struct CircleObject
{
    PhysicsEngine::BodyRef BodyRef{};
    Math::CircleF Circle;
    SDL_Color Color{};
};

struct RectangleObject
{
    PhysicsEngine::BodyRef BodyRef{};
    Math::RectangleF Rect;
    SDL_Color Color{};
};

class TriggerColliderSample : public Sample, public PhysicsEngine::ContactListener
{
private:
    CircleObject _staticObj{{}, {Math::Vec2F::Zero(), 0.f}};
    //RectangleObject _staticObj{{}, {Math::Vec2F::Zero(), Math::Vec2F::Zero()}};
    RectangleObject _movingObj{{}, {Math::Vec2F::Zero(), Math::Vec2F::Zero()}};

    std::vector<CircleObject*> _circleObjects{};
    std::vector<RectangleObject*> _rectangleObjects{};

    static constexpr SDL_Color _noCollisionColor = {255, 0, 0, 255};
    static constexpr SDL_Color _collisionColor = {0, 255, 0, 255};

public:
    explicit TriggerColliderSample() noexcept = default;

    void Init() noexcept override;
    void HandleInputs(SDL_Event event) noexcept override;
    void Update() noexcept override;
    void Deinit() noexcept override;

    void OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA,
                        PhysicsEngine::ColliderRef colliderRefB) noexcept override;

    void OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA,
                       PhysicsEngine::ColliderRef colliderRefB) noexcept override;
};