
// TODO: balancer tout le main dans une classe Application -> SampleManager dans sample directory

#include "SampleManager.h"
#include "GraphicGeometry.h"

#ifdef TRACY_ENABLE
#include <Tracy.hpp>
#endif // TRACY_ENABLE

#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>

#include <iostream>

int main([[maybe_unused]] int argc, [[maybe_unused]] char* args[])
{
    Window window;
    window.Init();

    SampleManager sampleManager;
    sampleManager.Init();

    SDL_Event event;
    bool quit = false;
    bool isMouseOnAnImGuiWindow;

    ImGuiIO* imGuiIO = &ImGui::GetIO();

    constexpr ImVec2 startSampleManagerWindowSize = ImVec2(400, 200);
    constexpr ImVec2 startSampleManagerWindowPos = ImVec2(50, 50);

    ImGui::SetNextWindowSize(startSampleManagerWindowSize);
    ImGui::SetNextWindowPos(startSampleManagerWindowPos);

    while (!quit)
    {
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                quit = true;
                break;
            }

            ImGui_ImplSDL2_ProcessEvent(&event);
            isMouseOnAnImGuiWindow = imGuiIO->WantCaptureMouse;

            sampleManager.HandleCurrentSampleInputs(event, isMouseOnAnImGuiWindow);
        }

        GraphicGeometry::ClearGeometry();
        SDL_RenderClear(window.Renderer());

        SDL_SetRenderDrawColor(window.Renderer(),
            Window::BackgroundColor.r,
            Window::BackgroundColor.g,
            Window::BackgroundColor.b,
            Window::BackgroundColor.a);

        sampleManager.UpdateCurrentSample();

        ImGui::Begin("Sample Manager");

        if (ImGui::BeginCombo("Select a Sample", sampleManager.CurrentSample()->Name().c_str()))
        {
            for (std::size_t index = 0; index < SampleManager::SampleCount; index++)
            {
                const auto currentSampleIdx = sampleManager.CurrentSampleIdx();

                if (ImGui::Selectable(sampleManager.GetSampleAtIndex(index)->Name().c_str(), currentSampleIdx == index))
                {
                    if (currentSampleIdx != index)
                    {
                        sampleManager.ChangeSample(index);
                    }
                }
            }

            ImGui::EndCombo();
        }

        ImGui::Spacing();

        ImGui::TextWrapped(sampleManager.CurrentSample()->Description().c_str());

        ImGui::Spacing();

        if (ImGui::Button("Restart sample"))
        {
            sampleManager.RestartSample();
        }

        ImGui::End();

        sampleManager.RenderCurrentSample();

        ImGui::Render();
        SDL_RenderGeometry(window.Renderer(),
            nullptr,
            GraphicGeometry::Vertices.data(),
            static_cast<int>(GraphicGeometry::Vertices.size()),
            GraphicGeometry::Indices.data(),
            static_cast<int>(GraphicGeometry::Indices.size()));

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(window.Renderer());

    #ifdef TRACY_ENABLE
            FrameMark;
    #endif
    }

    window.Deinit();

    return 0;
}