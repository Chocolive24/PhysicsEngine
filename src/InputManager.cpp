//
// Created by Olivier on 13.10.2023.
//

#include "InputManager.h"

void InputManager::HandleInputs(bool& quit)
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
    }
}
