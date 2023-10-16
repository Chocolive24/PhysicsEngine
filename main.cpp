//
// Created by Olivier on 10.10.2023.
//

#include "Timer.h"
#include "PlanetSystem.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "World.h"

// TODO: clean le code qui dessine cercle
// TODO: sharedPtr avec tests
// TODO: Clean la hierarchy fichier avec cmakelists
    //TODO: lib grpahic
    //TODO: rename tests
//TODO: pixels to meters

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