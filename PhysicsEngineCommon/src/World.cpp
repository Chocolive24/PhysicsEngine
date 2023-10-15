//
// Created by Olivier on 15.10.2023.
//

#include "World.h"

#include <iostream>

void PhysicsEngine::World::AddBody(PhysicsEngine::Body& body) noexcept
{
    Bodies.push_back(body);
}

void PhysicsEngine::World::Update(const float deltaTime) noexcept
{
    for (auto& body : Bodies)
    {
        // a = F / m
        Vec2F acceleration = body.Forces() / body.Mass;

        // Change velocity according to delta time.
        body.Velocity += acceleration * deltaTime;

        // Change position according to velocity and delta time.
        body.Position += body.Velocity * deltaTime;

        std::cout <<  " B: " << body.Position.X << "\n";

        body.SetForces(Vec2F::Zero());
    }
}
