#pragma once

#include "Metrics.h"
#include "Vec2.h"

#include "SDL.h"

#include <array>

class InputsManager
{
private:
    std::array<bool, 512> _keysUp{};
    std::array<bool, 512> _keysDown{};
    std::array<bool, 512> _keysPressed{};

    std::array<bool, 5> _mouseButtonsUp{};
    std::array<bool, 5> _mouseButtonsDown{};
    std::array<bool, 5> _mouseButtonsPressed{};

    Vec2F _mousePosition = Vec2F::Zero();

public:
    SDL_Event event{};

    void HandleInputs(bool& quit) noexcept;

    [[nodiscard]] constexpr bool IsMouseButtonDown(int mouseButton) const noexcept
    {
        return _mouseButtonsDown[mouseButton];
    }

    [[nodiscard]] constexpr Vec2F MousePositionInPixels() const noexcept { return _mousePosition; }
    [[nodiscard]] constexpr Vec2F MousePositionInMeters() const noexcept
    {
        return PhysicsEngine::Metrics::PixelsToMeters(_mousePosition);
    }
};
