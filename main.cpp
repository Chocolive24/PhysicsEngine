/**
 * @brief A planet system sample using the physics engine.
 * In the future, the main would handle many samples using ImGUI to switch between them.
 * @author Olivier Pachoud
 */

//TODO: Refactor code :
    //TODO: cast operator uniquePtr et sharedPtr
    //TODO: class samples.
    //TODO: linker ImGUI
//TODO: Colliders struct
//TODO: Contact Listener
//TODO: Pres sega saturne.
//TODO: Pres taff perso<3

//TODO: APP_SDL (aka window actuelle)
    //TODO: va faire la loop while(!quit) et les inputs
    // TODO: va recevoir des datas a draw et render

#include "PlanetSystem.h"
#include "DrawableGeometry.h"

int main()
{
    Window window{};
    window.Init();

    PlanetSystem planetSystem;
    planetSystem.Init();

    SDL_Event event;
    bool quit = false;

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};

    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            planetSystem.HandleInputs(event);
        }

        SDL_RenderClear(window.Renderer());

        SDL_SetRenderDrawColor(window.Renderer(),
                               backgroundColor.r,
                               backgroundColor.g,
                               backgroundColor.b,
                               backgroundColor.a);

        planetSystem.Update();

        SDL_RenderGeometry(window.Renderer(),
                           nullptr,
                           DrawableGeometry::Vertices.data(),
                           static_cast<int>(DrawableGeometry::Vertices.size()),
                           DrawableGeometry::Indices.data(),
                           static_cast<int>(DrawableGeometry::Indices.size()));

        SDL_RenderPresent(window.Renderer());
    }

    window.Deinit();

    return 0;
}