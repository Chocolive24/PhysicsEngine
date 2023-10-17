//
// Created by Olivier on 13.10.2023.
//

#include "InputsManager.h"

void InputsManager::HandleInputs(bool& quit) noexcept
{
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            quit = true;
        }
    }
}
