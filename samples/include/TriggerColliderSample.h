#pragma once

#include "Sample.h"
#include "ContactListener.h"

struct CircleObject
{
    PhysicsEngine::BodyRef BodyRef{};
    Math::CircleF Circle{Math::Vec2F::Zero(), 0.f};
    SDL_Color Color{};
};

struct RectangleObject
{
    PhysicsEngine::BodyRef BodyRef{};
    Math::RectangleF Rect{Math::Vec2F::Zero(), Math::Vec2F::Zero()};
    SDL_Color Color{};
};

class TriggerColliderSample : public Sample, public PhysicsEngine::ContactListener
{
private:
    CircleObject _staticObj{};
    //RectangleObject _staticObj{{}, {Math::Vec2F::Zero(), Math::Vec2F::Zero()}};
    RectangleObject _movingObj{};

    static constexpr int CircleNbr = 10;
    static constexpr int RectangleNbr = 10;

    std::vector<CircleObject> _circleObjects{};
    std::vector<RectangleObject> _rectangleObjects{};

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