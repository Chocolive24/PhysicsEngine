#include "RenderingManager.h"
#include "Utility.h"

#include <iostream>

void RenderingManager::Init() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    _window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               RenderingManager::WindowWidth, RenderingManager::WindowHeight,
                               SDL_WINDOW_RESIZABLE);

    if (!_window)
    {
        std::cout << "Failed to create  Error :" <<  " " << SDL_GetError() << "\n";
        exit(-1);
    }

    _renderer = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED);

    if (_renderer == nullptr)
    {
        std::cout << "Renderer could not be created! Error :" << " " << SDL_GetError() << "\n";
        exit(1);
    }

    // Initialize the vectors for geometry
    _vertices.clear();
    _indices.clear();
}

void RenderingManager::UnInit() const noexcept
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void RenderingManager::AddVertex(Math::Vec2F pos, SDL_Color color, float u, float v)
{
    //Vector2F vertexPos = PosToVertex(scaledVec);

    SDL_Vertex vertex;
    vertex.position.x = pos.X;
    vertex.position.y = pos.Y;
    vertex.color.r = color.r;
    vertex.color.g = color.g;
    vertex.color.b = color.b;
    vertex.color.a = color.a;
    vertex.tex_coord.x = u;
    vertex.tex_coord.y = v;

    _vertices.push_back(vertex);
}

void RenderingManager::ClearGeometry() noexcept
{
    _vertices.clear();
    _indices.clear();
}

void RenderingManager::DrawCircle(Math::Vec2F position, float r, std::size_t segments, SDL_Color color) noexcept
{
   ClearGeometry();

    // Calculate vertices for the circle
    for (int i = 0; i < segments; i++)
    {
        float angle = 2 * Math::Utility::Pi * static_cast<float>(i) / static_cast<float>(segments);
        float x = position.X + r * cos(angle);
        float y = position.Y + r * sin(angle);
        AddVertex(Math::Vec2F(x, y), color, 1, 1);

        if (i == segments -1) break;

        _indices.push_back(0); // Center point
        _indices.push_back(i);
        _indices.push_back(i + 1);
    }

    _indices.push_back(0); // Center point
    _indices.push_back(static_cast<int>(segments) - 1);
    _indices.push_back(0);  // Connect the last vertex to the center

    SDL_RenderGeometry(_renderer, nullptr, _vertices.data(),
                       static_cast<int>(_vertices.size()),_indices.data(),
                       static_cast<int>(_indices.size()));
}
