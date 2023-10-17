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

    InputsManager inputManager{};

    PhysicsEngine::Timer timer;
    timer.Init();

    PhysicsEngine::World world;
    world.Init(PlanetSystem::StartPlanetNbr + 1);

    PlanetSystem planetSystem;
    planetSystem.Init(world);
    planetSystem.RunGameLoop(renderingManager, inputManager, world, timer);

    renderingManager.UnInit();

    return 0;
}