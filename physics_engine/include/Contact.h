#pragma once

#include "Vec2.h"
#include "References.h"

struct Contact
{
	ColliderRef colliderRefA, colliderRefB;
	Math::Vec2F Normal;
	Math::Vec2F Point;
	Math::Vec2F Penetration;

	float CalculateSeperatingVelocity() const noexcept;
};

