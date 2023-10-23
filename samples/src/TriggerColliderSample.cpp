//
// Created by Olivier on 20.10.2023.
//

#include "TriggerColliderSample.h"
#include "DrawableGeometry.h"

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
    Math::Vec2I mousePosition;
    SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);

    auto mousePosF = static_cast<Math::Vec2F>(mousePosition);

    std::vector<Math::Vec2F> vertices = {mousePosF,
                                         mousePosF + Math::Vec2F(150, 150),
                                         mousePosF + Math::Vec2F(-100, 250),
                                         mousePosF + Math::Vec2F(-25, 300),
                                         mousePosF + Math::Vec2F(75, 467)};

    DrawableGeometry::Polygon(vertices, {255, 0, 0, 255});
}

void TriggerColliderSample::Deinit() noexcept
{
    Sample::Deinit();
}
