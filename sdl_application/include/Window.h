#pragma once

/**
 * @headerfile Window is a class that creates a graphical window for the program.
 * @author Oliver Pachoud
 */

#include "Definition.h"
#include "Vec2.h"

#include "SDL.h"

#include <cstddef>
#include <vector>

class Window
{
private:
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};

public:
    /**
     * @brief WindowWidth is the size of the window's width in pixels.
     */
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    void Init() noexcept;
    void Deinit() const noexcept;

    [[nodiscard]] constexpr SDL_Renderer* Renderer() const noexcept { return _renderer; }
};