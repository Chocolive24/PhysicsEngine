//
// Created by Olivier on 20.10.2023.
//

#include "TriggerColliderSample.h"

#include <iostream>

void TriggerColliderSample::Init() noexcept
{
    Sample::Init();

    std::cout << "INIT" << "\n";
}

void TriggerColliderSample::HandleInputs(SDL_Event event) noexcept
{
    if(event.type == SDL_MOUSEBUTTONDOWN)
    {
        std::cout << "INPUUUUUUTS" << "\n";
    }
}

void TriggerColliderSample::Update() noexcept
{
}

void TriggerColliderSample::Deinit() noexcept
{
    Sample::Deinit();
}
