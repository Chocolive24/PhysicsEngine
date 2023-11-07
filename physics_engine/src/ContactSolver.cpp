#include "ContactSolver.h"

void PhysicsEngine::ContactSolver::CalculateContactProperties() noexcept
{
    const auto colShapeA = colliderA->Shape(); 
    const auto colShapeB = colliderB->Shape();

    switch (colShapeA.index())
    {
    case static_cast<int>(Math::ShapeType::Circle):
    {
        const auto circleA = std::get<Math::CircleF>(colShapeA) + bodyA->Position();

        switch (colShapeB.index())
        {
            case static_cast<int>(Math::ShapeType::Circle):
            {
                const auto circleB = std::get<Math::CircleF>(colShapeB) + bodyB->Position();
                const auto cA = circleA.Center(), cB = circleB.Center();
                const auto rA = circleA.Radius(), rB = circleB.Radius();

                const auto delta = cA - cB;
                Normal = delta.Normalized();
                Point = cA + delta * 0.5f;
                Penetration = rA + rB - delta.Length();

                break;
            } // Case circle B.

            case static_cast<int>(Math::ShapeType::Rectangle):
            {
                const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                    bodyB->Position();

                const auto circleCenter = circleA.Center(), rectCenter = rectB.Center();
                const auto rectHalfSize = rectB.HalfSize();

                const auto delta = circleCenter - rectCenter;

                Math::Vec2F closestPoint;

                closestPoint.X = Math::Clamp(delta.X, -rectHalfSize.X, rectHalfSize.X);
                closestPoint.Y = Math::Clamp(delta.Y, -rectHalfSize.Y, rectHalfSize.Y);

                const auto distance = (closestPoint - delta).Length();
                const auto closestPoinOnRect = rectCenter + closestPoint;

                auto circleToRect = (circleCenter - closestPoinOnRect);

                if (circleToRect.Length() <= Math::Epsilon)
                {
                    circleToRect = Math::Vec2F(0.f, 1.f);
                }

                Normal = circleToRect.Normalized();
                Point = closestPoinOnRect;
                Penetration = circleA.Radius() - distance;

                break;
            } // Case rectangle B.

        case static_cast<int>(Math::ShapeType::None):
            break;
        default:
            break;
        } // Switch shape collider B.

        break;
    } // Case circle A.

    case static_cast<int>(Math::ShapeType::Rectangle):
    {
        const auto rectA = std::get<Math::RectangleF>(colShapeA) + bodyA->Position();

        switch (colShapeB.index())
        {
        case static_cast<int>(Math::ShapeType::Circle):
        {
            const auto circleB = std::get<Math::CircleF>(colShapeB) +
                bodyB->Position();
                
            std::swap(bodyA, bodyB);
            std::swap(colliderA, colliderB);
            CalculateContactProperties();

            break;
        } // Case circle B.

        case static_cast<int>(Math::ShapeType::Rectangle):
        {
            const auto rectB = std::get<Math::RectangleF>(colShapeB) +
                bodyB->Position();

            const auto cA = rectA.Center(), cB = rectB.Center();
            const auto halfSizeA = rectA.HalfSize(), halfSizeB = rectB.HalfSize();

            const auto delta = cA - cB;
            Point = cA + delta * 0.5f;

            // Calculate the penetration in x-axis
            const auto penetrationX = halfSizeA.X + halfSizeB.X - Math::Abs(delta.X);
            // Calculate the penetration in y-axis
            const auto penetrationY = halfSizeA.Y + halfSizeB.Y - Math::Abs(delta.Y);

            if (penetrationX < penetrationY)
            {
                Normal = delta.X > 0 ?
                    Math::Vec2F::Right() : Math::Vec2F::Left();

                Penetration = penetrationX;
            }
            else
            {
                Normal = delta.Y > 0 ? Math::Vec2F::Up() : Math::Vec2F::Down();

                Penetration = penetrationY;
            }

            break;
        } // Case rectangle B.

        case static_cast<int>(Math::ShapeType::None):
            break;
        default:
            break;
        } // Switch shape collider B.

        break;
    } // Case rectangle A.

    case static_cast<int>(Math::ShapeType::None):
        break;
    default:
        break;
    } // Switch shape collider A.
}

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

    const auto impusle = deltaVelocity / totalInverseMass;
    const auto impulsePerIMass = Normal * impusle;

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
    if (Penetration <= 0) return;

    const auto inversMassBodyA = bodyA->InverseMass();
    const auto inversMassBodyB = bodyB->InverseMass();
    const auto totalInverseMass = inversMassBodyA + inversMassBodyB;

    if (totalInverseMass <= 0) return;

    const auto movePerIMass = Normal * (Penetration / totalInverseMass);

    if (bodyA->GetBodyType() == BodyType::Dynamic)
    {
        bodyA->SetPosition(bodyA->Position() + movePerIMass * inversMassBodyA);
    }

    if (bodyB->GetBodyType() == BodyType::Dynamic)
    {
        bodyB->SetPosition(bodyB->Position() - movePerIMass * inversMassBodyB);
    }
}

void PhysicsEngine::ContactSolver::ResolveContact() noexcept
{
    CalculateContactProperties();

    if (bodyA->GetBodyType() == BodyType::Static)
    {
        std::swap(bodyA, bodyB);
        Normal = -Normal;
    }

    ResolvePostCollisionVelocity();
    ResolvePostCollisionPosition();
}
