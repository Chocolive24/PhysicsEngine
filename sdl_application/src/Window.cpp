#include "Window.h"
#include "Utility.h"

#include <iostream>

void Window::Init() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failed to initialize the SDL2 library Error :" <<  " " << SDL_GetError() << "\n";
        Deinit();
    }

    _window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WindowWidth,
                               WindowHeight,
                               SDL_WINDOW_RESIZABLE);

    if (!_window)
    {
        std::cerr << "Failed to create window! Error :" << " " << SDL_GetError() << "\n";
        Deinit();
        exit(1);
    }

   _renderer = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED);

    if (!_renderer)
    {
        std::cerr << "Renderer could not be created! Error :" << " " << SDL_GetError() << "\n";
        Deinit();
        exit(1);
    }
}

void Window::Deinit() const noexcept
{
    if (_renderer) SDL_DestroyRenderer(_renderer);
    if (_window) SDL_DestroyWindow(_window);

    SDL_Quit();
}


