//
// Created by Olivier on 10.10.2023.
//

#include "Timer.h"
#include "PlanetSystem.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "World.h"

int main()
{
    RenderingManager renderingManager{};
    renderingManager.Init();

    InputManager inputManager{};

    Timer timer;
    timer.Init();

    PhysicsEngine::World world;
    world.Init(1);

    PlanetSystem planetSystem;
    planetSystem.Init(world);
    planetSystem.RunGameLoop(renderingManager, inputManager, world, timer);

    renderingManager.UnInit();

    return 0;
}