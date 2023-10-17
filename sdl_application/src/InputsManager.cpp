//
// Created by Olivier on 13.10.2023.
//

#include "InputsManager.h"

void InputsManager::HandleInputs(bool& quit) noexcept
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                _mouseButtonsDown[event.button.button] = true;
                break;
            case SDL_MOUSEBUTTONUP:
                _mouseButtonsUp[event.button.button] = true;
                _mouseButtonsDown[event.button.button] = false;
                break;
            case SDL_MOUSEMOTION:
                _mousePosition.X = event.motion.x;
                _mousePosition.Y = event.motion.y;
                break;
        }
    }
}
