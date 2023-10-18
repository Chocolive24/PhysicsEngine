/**
 * @brief A planet system sample using the physics engine.
 * In the future, the main would handle many samples using ImGUI to switch between them.
 * @author Olivier Pachoud
 */

#include "PlanetSystem.h"

int main()
{
    RenderingManager renderingManager{};
    renderingManager.Init();

    InputsManager inputsManager{};

    PhysicsEngine::Timer timer;
    timer.Init();

    PlanetSystem planetSystem;
    planetSystem.Init();
    planetSystem.RunGameLoop(renderingManager, inputsManager, timer);

    renderingManager.Deinit();

    return 0;
}