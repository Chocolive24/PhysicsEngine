#pragma once

#include "SDL.h"

class InputsManager
{
public:
    SDL_Event event;

    void HandleInputs(bool& quit) noexcept;
};
