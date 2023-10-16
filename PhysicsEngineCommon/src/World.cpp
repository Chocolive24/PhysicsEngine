//
// Created by Olivier on 15.10.2023.
//

#include <iostream>
#include "World.h"

namespace PhysicsEngine
{
    void World::Init(int bodyCount) noexcept
    {
        if (bodyCount < 0) bodyCount = 0;

        _bodies.resize(bodyCount, Body());
        _generationIndices.resize(bodyCount, 0);
    }

    BodyRef World::CreateBody() noexcept
    {
        auto it = std::find_if(_bodies.begin(), _bodies.end(),[](const Body& body)
        {
            return !body.IsValid();
        });

        if (it != _bodies.end())
        {
            // Found an invalid body.
            std::size_t index = std::distance(_bodies.begin(), it);

            return BodyRef{index, _generationIndices[index]};
        }

        // No body with negative mass found.
        std::size_t previousSize = _bodies.size();

        _bodies.resize(previousSize + _bodyResizeAmount, Body());
        _generationIndices.resize(previousSize + _bodyResizeAmount, 0);

        return { previousSize, _generationIndices[previousSize] };
    }

    void World::DestroyBody(BodyRef bodyRef) noexcept
    {
        _bodies[bodyRef.Index] = Body();
        _generationIndices[bodyRef.Index]++;
    }

    Body& World::GetBody(BodyRef bodyRef)
    {
        if (_generationIndices[bodyRef.Index] != bodyRef.GenerationIdx)
        {
            throw std::runtime_error("Null body reference exception");
        }

        return _bodies[bodyRef.Index];
    }

    void World::Update(const float deltaTime) noexcept
    {
        for (auto& body : _bodies)
        {
            if (!body.IsValid()) continue;

            // a = F / m
            Vec2F acceleration = body.Forces() / body.Mass();

            // Change velocity according to delta time.
            body.SetVelocity(body.Velocity() + acceleration * deltaTime);

            // Change position according to velocity and delta time.
            body.SetPosition(body.Position() + body.Velocity() * deltaTime);

            body.SetForces(Vec2F::Zero());
        }
    }
}