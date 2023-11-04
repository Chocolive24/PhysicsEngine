#pragma once

#include "Vec2.h"
#include "References.h"

namespace PhysicsEngine
{
	struct Contact
	{
		ColliderRef colliderRefA, colliderRefB;
		Math::Vec2F Normal;
		Math::Vec2F Point;
		float Penetration;

		float CalculateSeperatingVelocity() const noexcept;
	};
}