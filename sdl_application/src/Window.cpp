#include "Window.h"
#include "Utility.h"

#include <iostream>

void Window::Init() noexcept
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("Failed to initialize the SDL2 library Error  :%s", SDL_GetError());
        return;
    }

    _window = SDL_CreateWindow("SDL2 Window",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               WindowWidth,
                               WindowHeight,
                               SDL_WINDOW_SHOWN);

    if (_window == nullptr)
    {
        SDL_Log("Failed to create window! Error : %s", SDL_GetError());
        return;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);

    if (_renderer == nullptr)
    {
        SDL_Log("Renderer could not be created! Error : %s", SDL_GetError());
        return;
    }
}

void Window::RunAppLoop()
{
   
}

void Window::Deinit() const noexcept
{
    if (_renderer != nullptr)
    {
        SDL_DestroyRenderer(_renderer);
    }

    if (_window != nullptr)
    {
        SDL_DestroyWindow(_window);
    }

    SDL_Quit();
}