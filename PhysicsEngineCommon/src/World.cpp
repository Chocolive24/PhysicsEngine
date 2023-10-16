//
// Created by Olivier on 15.10.2023.
//

#include <iostream>
#include "World.h"

namespace PhysicsEngine
{
    void World::Init(std::size_t bodyCount) noexcept
    {
        for (int i = 0; i < bodyCount; i++)
        {
            _bodies.emplace_back();
            _generationIndices.emplace_back(0);
        }

//        _bodies.resize(bodyCount, Body());
//        _generationIndices.resize(bodyCount, 0);
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

//        // No body with negative mass found.
//        std::size_t previousSize = _bodies.size();
//
//        _bodies.resize(previousSize + _bodyResizeAmount, Body());
//        _generationIndices.resize(previousSize + _bodyResizeAmount, 0);

        _bodies.emplace_back();
        _generationIndices.emplace_back(0);

        return { _bodies.size() - 1, _generationIndices[_generationIndices.size() - 1] };
    }

    Body& World::GetBody(BodyRef bodyRef)
    {
        if (_generationIndices[bodyRef.Index] != bodyRef.GenerationIdx)
        {
            std::cout << "THROW EXCEPTION" << "\n";
        }

        return _bodies[bodyRef.Index];
    }

    void World::Update(const float deltaTime) noexcept
    {
        int i = 0;
        for (auto& body : _bodies)
        {
            if (!body.IsValid()) continue;

            // a = F / m
            Vec2F acceleration = body.Forces() / body.Mass();

            // Change velocity according to delta time.
            body.SetVelocity(body.Velocity() + acceleration * deltaTime);

            // Change position according to velocity and delta time.
            body.SetPosition(body.Position() + body.Velocity() * deltaTime);

            std::cout << i << " : " << body.Position().X << " " << body.Position().Y << "\n";

            body.SetForces(Vec2F::Zero());

            i++;
        }
    }
}