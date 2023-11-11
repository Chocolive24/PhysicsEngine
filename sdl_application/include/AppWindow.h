/**
 * @headerfile AppWindow.h
 * This file defines the Window class that creates a graphical window for the program using SDL2.
 *
 * @author Oliver Pachoud
 */

#pragma once

#include "Definition.h"
#include "Vec2.h"

#include "SDL.h"

#include <cstddef>
#include <vector>

/*
* @brief AppWindow is the application window using SDL2.
*/
class AppWindow
{
private:
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};

public:
    /**
     * @brief BackgroundColor is color the color of the background of the window, which is black.
     */
    static constexpr SDL_Color BackgroundColor{0, 0, 0, 255};

    /**
     * @brief WindowWidth is the size of the window's width in pixels.
     */
    static constexpr int WindowWidth = 880;

    /**
     * @brief WindowHeight is the size of the window's height in pixels.
     */
    static constexpr int WindowHeight = 680;

    /**
     * @brief Init is a method that initialize the application window.
     * More precisely, the method initiates SDL and ImGui, creates the window and creates the renderer. 
     */
    void Init() noexcept;

    /**
     * @brief Deinit is a method that deinitialize the application window.
     * More precisely, the method deinitiates SDL and ImGui, destroy the window and destroy the renderer.
     */
    void Deinit() const noexcept;

    /**
     * @brief Renderer is a method that gives the renderer of the application window.
     * @return The renderer of the application window.
     */
    [[nodiscard]] constexpr SDL_Renderer* Renderer() const noexcept { return _renderer; }
};