/**
 * @brief A planet system sample using the physics engine.
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
    world.Init(PlanetSystem::PlanetToCreate + 1);

    PlanetSystem planetSystem;
    planetSystem.Init(world);
    planetSystem.RunGameLoop(renderingManager, inputManager, world, timer);

    renderingManager.UnInit();

    return 0;
}