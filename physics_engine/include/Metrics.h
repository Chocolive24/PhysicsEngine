#pragma once

/**
 * @headerfile A collection of metrics.
 * @author Olivier
 */

#include "Vec2.h"

namespace PhysicsEngine::Metrics
{
    static constexpr float MetersToPixelsRatio = 100.f;
    static constexpr float PixelsToMetersRatio = 0.01f;

    template<typename T>
    [[nodiscard]] constexpr T PixelsToMeters(const T pixels) noexcept
    {
        return pixels * PixelsToMetersRatio;
    }

    template<typename T>
    [[nodiscard]] constexpr Math::Vec2<T> PixelsToMeters(const Math::Vec2<T> pixelPos) noexcept
    {
        return Math::Vec2<T>(pixelPos.X * PixelsToMetersRatio, pixelPos.Y * PixelsToMetersRatio * -1.f);
    }

    template<typename T>
    [[nodiscard]] constexpr T MetersToPixels(const T meters) noexcept
    {
        return meters * MetersToPixelsRatio;
    }

    template<typename T>
    [[nodiscard]] constexpr Math::Vec2<T> MetersToPixels(const Math::Vec2<T> meterPos) noexcept
    {
        return Math::Vec2<T>(meterPos.X * MetersToPixelsRatio, meterPos.Y * MetersToPixelsRatio * -1.f);
    }
}