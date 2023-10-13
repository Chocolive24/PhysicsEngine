#pragma once

#include "Body.h"

class Planet
{
private:
    PhysicsEngine::Body _body{Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)};
    float _radius{0.f};

public:
    constexpr Planet() noexcept = default;
    constexpr Planet(PhysicsEngine::Body body, float r) noexcept : _body(body), _radius(r){}

    [[nodiscard]] constexpr PhysicsEngine::Body& GetBody() noexcept { return _body; }
    [[nodiscard]] constexpr float GetRadius() const noexcept { return _radius; }
};
