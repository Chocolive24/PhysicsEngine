#pragma once

/**
 * @headerfile Sample.h
 * This file defines the Sample abstract class that contains the fundamental elements of a physical engine sample.
 * 
 * @author Olivier Pachoud
 */

#include "World.h"
#include "Window.h"
#include "Timer.h"

#include "SDL.h"

/**
 * @enum SampleType is an enum that enumerates the different sample types.
 */
enum class SampleType
{
    PlanetSystem,
    Trigger,
};

/**
 * @class Sample is an abstract class that contains the fundamental elements of a physical engine sample
 */
class Sample
{
protected:
    PhysicsEngine::World _world;
    Timer _timer;

    static constexpr int _startBodyCount = 2;

public:
    Sample() noexcept = default;

    virtual ~Sample() = default;

    /**
     * @brief Init is a method that initializes the sample.
     */
    virtual void Init() noexcept;
    virtual void HandleInputs(SDL_Event event) noexcept = 0;
    virtual void Update() noexcept = 0;
    virtual void Deinit() noexcept;
};