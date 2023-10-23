/**
 * @brief A planet system sample using the physics engine.
 * In the future, the main would handle many samples using ImGUI to switch between them.
 * @author Olivier Pachoud
 */

//TODO: Refactor code :
    //TODO: linker ImGUI
//TODO: Colliders struct
//TODO: Contact Listener
//TODO: Pres sega saturne.
//TODO: Pres taff perso<3

// TODO: balancer tout le main dans une classe Application

//TODO: les tests des classes colliders

//TODO: CreateBody(Vec2F pos, vel, mass) -> modifie direct dans le fonction le body.
// pour éviter de chopper la ref puis la modif.

#include "UniquePtr.h"
#include "PlanetSystemSample.h"
#include "TriggerColliderSample.h"
#include "DrawableGeometry.h"

int main()
{
    Window window{};
    window.Init();

    UniquePtr<Sample> currentSample;

    SDL_Event event;
    bool quit = false;

    constexpr SDL_Color backgroundColor{0, 0, 0, 255};

    while(!quit)
    {
        bool isCurrentSampleNull = currentSample.Get() == nullptr;

        while(SDL_PollEvent(&event))
        {
            switch (event.type) 
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.scancode)
                    {
                        case SDL_SCANCODE_1:
                            currentSample = UniquePtr<Sample>(new PlanetSystemSample);
                            currentSample->Init();
                            break;
                        case SDL_SCANCODE_2:
                            currentSample = UniquePtr<Sample>(new TriggerColliderSample);
                            currentSample->Init();
                            break;
                        default:
                            break;
                    }
            }

            if (!isCurrentSampleNull)
            {
                currentSample->HandleInputs(event);
            }
        }

        DrawableGeometry::ClearGeometry();
        SDL_RenderClear(window.Renderer());

        SDL_SetRenderDrawColor(window.Renderer(),
                               backgroundColor.r,
                               backgroundColor.g,
                               backgroundColor.b,
                               backgroundColor.a);

        if(!isCurrentSampleNull)
        {
            currentSample->Update();
        }

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