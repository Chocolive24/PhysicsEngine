//
// Created by Olivier on 19.10.2023.
//

#include "Sample.h"

void Sample::Init() noexcept
{
    _timer.Init();

    _world.Init(_startBodyCount);

    onInit();
}

void Sample::HandleInputs(const SDL_Event event, const bool isMouseOnAnImGuiWindow) noexcept
{
    onHandleInputs(event, isMouseOnAnImGuiWindow);
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

void Sample::Deinit() noexcept
{
    _world.Deinit();

    onDeinit();
}
