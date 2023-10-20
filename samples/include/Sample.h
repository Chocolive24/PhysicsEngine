#pragma once

#include "World.h"
#include "Window.h"
#include "Timer.h"

#include "SDL.h"

class Sample
{
public:
    Sample() noexcept = default;

protected:
    PhysicsEngine::World _world;
    Timer _timer;

    static constexpr int _startBodyCount = 100;

    virtual void Init() noexcept;
    virtual void HandleInputs(SDL_Event event) noexcept = 0;
    virtual void Update() noexcept = 0;
};