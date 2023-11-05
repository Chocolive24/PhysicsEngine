#include "ContactSolver.h"

float PhysicsEngine::ContactSolver::CalculateSeparatingVelocity() const noexcept
{
    const auto relativeVelocity = bodyA->Velocity() - bodyB->Velocity();
    const auto separatingVelocity = relativeVelocity.Dot(Normal);

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

    const auto impulse = deltaVelocity / totalInverseMass;
    const auto impulsePerIMass = Normal * impulse;

    if (bodyA->GetBodyType() == BodyType::Dynamic)
    {
        bodyA->SetVelocity(bodyA->Velocity() + impulsePerIMass * inversMassBodyA);
    }

    if (bodyB->GetBodyType() == BodyType::Dynamic)
    {
        bodyB->SetVelocity(bodyB->Velocity() - impulsePerIMass * inversMassBodyB);
    }
}

void PhysicsEngine::ContactSolver::ResolvePostCollisionPosition() noexcept
{
    if (Penetration <= 0.001f) return;

    const auto inversMassBodyA = bodyA->InverseMass();
    const auto inversMassBodyB = bodyB->InverseMass();
    const auto totalInverseMass = inversMassBodyA + inversMassBodyB;

    if (totalInverseMass <= 0.001f) return;

    const auto movePerIMass = Normal * (-Penetration / totalInverseMass);

    if (bodyA->GetBodyType() == BodyType::Dynamic)
    {
        bodyA->SetPosition(bodyA->Position() + movePerIMass * inversMassBodyA);
    }

    if (bodyB->GetBodyType() == BodyType::Dynamic)
    {
        bodyB->SetPosition(bodyB->Position() + movePerIMass * inversMassBodyB);
    }
}

void PhysicsEngine::ContactSolver::ResolveContact() noexcept
{
    ResolvePostCollisionVelocity();
    ResolvePostCollisionPosition();
}
