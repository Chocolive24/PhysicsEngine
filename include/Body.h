#pragma once

#include "Vec2.h"

class Body
{
public:
    Vec2F Position = {0.f, 0.f};
    Vec2F Velocity = {0.f ,0.f};

    constexpr Body() noexcept = default;
    Body(Vec2F pos, Vec2F vel) noexcept;
};