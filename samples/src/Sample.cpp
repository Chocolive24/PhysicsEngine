//
// Created by Olivier on 19.10.2023.
//

#include <iostream>
#include "Sample.h"

void Sample::Init() noexcept
{
    _timer.Init();
    std::cout << _timer.TotalTime() << "\n";
    _world.Init(_startBodyCount);

    onInit();
}

void Sample::Deinit() noexcept
{
    std::cout << _timer.TotalTime() << "\n";
    _world.Deinit();

    onDeinit();
}

void Sample::HandleInputs(SDL_Event event) noexcept
{
    onHandleInputs(event);
}

void Sample::Update() noexcept
{
    _timer.Tick();

    onUpdate();

    _world.Update(_timer.DeltaTime());
}

void Sample::Render() noexcept
{
    onRender();
}
