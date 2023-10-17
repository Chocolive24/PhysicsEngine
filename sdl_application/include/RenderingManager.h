#pragma once

#include "Definition.h"
#include "Vec2.h"

#include "SDL.h"

#include <cstddef>
#include <vector>

class RenderingManager
{
private:
    SDL_Window* _window{};
    SDL_Renderer* _renderer{};

    std::vector<SDL_Vertex> _vertices;
    std::vector<int> _indices;

public:
    static constexpr int WindowWidth = 880;
    static constexpr int WindowHeight = 680;

    void Init() noexcept;

    void UnInit() const noexcept;

    void AddVertex(Math::Vec2F pos, SDL_Color color, float u = 1, float v = 1);
    void ClearGeometry()  noexcept;
    void DrawCircle(Math::Vec2F position, float r, std::size_t segments, SDL_Color color) noexcept;

    [[nodiscard]] constexpr SDL_Window* Window() const noexcept { return _window; }
    [[nodiscard]] constexpr SDL_Renderer* Renderer() const noexcept { return _renderer; }
};