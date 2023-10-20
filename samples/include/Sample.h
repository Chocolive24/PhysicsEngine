#pragma once

/**
 * @headerfile Sample is an abstract class that contains the fundamental elements of a physical engine sample.
 * @author Olivier Pachoud
 */

#include "World.h"
#include "Window.h"
#include "Timer.h"

#include "SDL.h"

class Sample
{
protected:
    PhysicsEngine::World _world;
    Timer _timer;

    static constexpr int _startBodyCount = 100;

public:
    Sample() noexcept = default;

    virtual ~Sample() = default;

    virtual void Init() noexcept;
    virtual void HandleInputs(SDL_Event event) noexcept = 0;
    virtual void Update() noexcept = 0;
    virtual void Deinit() noexcept;
};