#pragma once

#include "SDL.h"

class InputManager
{
public:
    SDL_Event event;

    void HandleInputs(bool& quit);
};
