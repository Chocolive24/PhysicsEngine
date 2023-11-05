#include "ContactSolver.h"

float PhysicsEngine::ContactSolver::CalculateSeparatingVelocity() const noexcept
{
    const auto relativeVelocity = bodyA->Velocity() - bodyB->Velocity();
    const auto separatingVelocity = Math::Vec2F::Dot(relativeVelocity, Normal);

    return separatingVelocity;
}

void PhysicsEngine::ContactSolver::ResolvePostCollisionVelocity() noexcept
{
    const auto separatingVelocity = CalculateSeparatingVelocity();

    // If the seperating velocity is positive, we don't need to calculate the delta velocity.
    if (separatingVelocity > 0)
    {
        return;
    }

    const auto mA = bodyA->Mass(), mB = bodyB->Mass();
    const auto eA = colliderA->Restitution(), eB = colliderB->Restitution();

    const auto combinedRestitution = (mA * eA + mB * eB) / (mA + mB);

    const auto finalSepVelocity = -separatingVelocity * combinedRestitution;
    const auto deltaVelocity = finalSepVelocity - separatingVelocity;

    const auto inversMassBodyA = bodyA->InverseMass();
    const auto inversMassBodyB = bodyB->InverseMass();
    const auto totalInverseMass = inversMassBodyA + inversMassBodyB;

    if (bodyA->GetBodyType() == BodyType::Dynamic)
    {
        const auto postCollisionVelocity = bodyA->Velocity() + 
            (-1 * Normal * deltaVelocity * inversMassBodyA / totalInverseMass);

        bodyA->SetVelocity(postCollisionVelocity);
    }

    if (bodyB->GetBodyType() == BodyType::Dynamic)
    {
        const auto postCollisionVelocity = bodyB->Velocity() +
            (-1 * Normal * deltaVelocity * inversMassBodyB / totalInverseMass);

        bodyB->SetVelocity(postCollisionVelocity);
    }
}
