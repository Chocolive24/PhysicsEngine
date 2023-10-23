#pragma once

#include "Sample.h"
#include "ContactListener.h"

struct GameObject
{
    PhysicsEngine::BodyRef BodyRef;
    // In Pixels
    float Radius;
    SDL_Color Color;
};

class TriggerColliderSample : public Sample, public PhysicsEngine::ContactListener
{
private:
    GameObject _staticObj{};
    GameObject _movingObj{};

    std::vector<GameObject*> _gameObjects{};

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