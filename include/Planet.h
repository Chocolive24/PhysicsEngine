#pragma once

#include "Body.h"

class Planet
{
private:
    Body _body{Vec2F::Zero, Vec2F::Zero};
    float _radius{0.f};
    float _speed{0.f};

public:
    Planet() noexcept = default;
    Planet(Body body, float r, float speed) noexcept;

    [[nodiscard]] Body& GetBody() noexcept { return _body; }
    [[nodiscard]] float GetRadius() const noexcept { return _radius; }
    [[nodiscard]] float GetSpeed() const noexcept { return _speed; }
};