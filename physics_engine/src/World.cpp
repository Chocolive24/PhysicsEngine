/**
 * @author Olivier
 */

#include "World.h"

namespace PhysicsEngine
{
    void World::Init(int bodyCount) noexcept
    {
        if (bodyCount < 0) bodyCount = 0;

        _bodies.resize(bodyCount, Body());
        _generationIndices.resize(bodyCount, 0);
    }

    [[nodiscard]] BodyRef World::CreateBody() noexcept
    {
        auto it = std::find_if(_bodies.begin(), _bodies.end(),[](const Body& body)
        {
            return !body.IsValid();
        });

        if (it != _bodies.end())
        {
            // Found an invalid body.
            std::size_t index = std::distance(_bodies.begin(), it);

            _bodies[index].SetMass(1.f);

            return BodyRef{index, _generationIndices[index]};
        }

        // No body with negative mass found.
        std::size_t previousSize = _bodies.size();
        std::size_t newSize = previousSize + _bodyResizeAmount;

        _bodies.resize(newSize);
        _generationIndices.resize(newSize);

        std::fill(_bodies.begin() + previousSize, _bodies.end(), Body());
        std::fill(_generationIndices.begin() + previousSize, _generationIndices.end(), 0);

        _bodies[previousSize].SetMass(1.f);

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
            Math::Vec2F acceleration = body.Forces() / body.Mass();

            // Change velocity according to delta time.
            body.SetVelocity(body.Velocity() + acceleration * deltaTime);

            // Change position according to velocity and delta time.
            body.SetPosition(body.Position() + body.Velocity() * deltaTime);

            body.SetForces(Math::Vec2F::Zero());
        }
    }
}