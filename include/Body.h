#pragma once

#include "Vec2.h"

class Body
{
public:
    Vec2F Position = Vec2F::Zero;
    Vec2F Velocity = Vec2F::Zero;

    constexpr Body() noexcept = default;
    Body(Vec2F pos, Vec2F vel) noexcept;
};