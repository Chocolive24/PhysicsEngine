#include "Body.h"

void PhysicsEngine::Body::AddForce(Vec2F force) noexcept
{
    _forces += force;
}
