/**
 * @brief A planet system sample using the physics engine.
 * In the future, the main would handle many samples using ImGUI to switch between them.
 * @author Olivier Pachoud
 */

 //TODO: interface allocator
 //TODO: linear, proxy et free line allocator
 // TODO: QUad tree

 // TODO: balancer tout le main dans une classe Application -> SampleManager dans sample directory

 //TODO: CreateBody(Vec2F pos, vel, mass) -> modifie direct dans le fonction le body.
 // pour éviter de chopper la ref puis la modif.

 //TODO: TOUT COMMENTER

#include <iostream>
#include "SampleManager.h"
#include "DrawableGeometry.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* args[])
{
    Window window{};
    window.Init();

    SDL_Event event;
    bool quit = false;

    SampleManager sampleManager;
    sampleManager.Init();

    while (!quit)
    {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }

            sampleManager.HandleInputs(event);
        }

        DrawableGeometry::ClearGeometry();
        SDL_RenderClear(window.Renderer());

        SDL_SetRenderDrawColor(window.Renderer(),
            Window::BackgroundColor.r,
            Window::BackgroundColor.g,
            Window::BackgroundColor.b,
            Window::BackgroundColor.a);

        sampleManager.Update();

        sampleManager.Render();

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