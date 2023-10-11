#pragma once

#include "Body.h"

class Planet
{
private:
    Body _body{Vec2F(0.f, 0.f), Vec2F(0.f, 0.f)};
    float _radius{0.f};
    float _speed{0.f};

public:
    Planet() noexcept = default;
    Planet(Body body, float r, float speed) noexcept;

    [[nodiscard]] Body& GetBody() noexcept { return _body; }
    [[nodiscard]] float GetRadius() const noexcept { return _radius; }
    [[nodiscard]] float GetSpeed() const noexcept { return _speed; }
};