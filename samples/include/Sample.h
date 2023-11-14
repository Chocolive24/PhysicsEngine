#pragma once

/**
 * @headerfile Sample.h
 * This file defines the Sample abstract class that contains the fundamental elements of a physical engine sample.
 * 
 * @author Olivier Pachoud
 */

#include "World.h"
#include "AppWindow.h"
#include "Timer.h"

#include "SDL.h"

/**
 * @class Sample is an abstract class that contains the fundamental elements of a physical engine sample
 */
class Sample
{
public:
    Sample() noexcept = default;

    Sample(const Sample& other)
    {
        
    }

    virtual ~Sample() = default;

    virtual std::string Name() const noexcept = 0;
    virtual std::string Description() const noexcept = 0;
    virtual std::string InputText() const noexcept = 0;

    /**
     * @brief Init is a method that initializes the sample.
     */
    void Init() noexcept;
    void HandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept;
    void Update() noexcept;
    void Render() noexcept;
    void Deinit() noexcept;

protected:
    PhysicsEngine::World _world;
    Math::Vec2F _gravity;
    Timer _timer;

    static constexpr int _startBodyCount = 100;

    /*
    * @brief onInit is an abstract method that initiliaze the sample that overrides it.
    */
    virtual void onInit() noexcept = 0;
    virtual void onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept = 0;
    virtual void onUpdate() noexcept = 0;
    virtual void onRender() noexcept = 0;
    virtual void onDeinit() noexcept = 0;
};