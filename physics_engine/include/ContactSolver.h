#pragma once

#include "Vec2.h"
#include "References.h"
#include "Body.h"
#include "Collider.h"

namespace PhysicsEngine
{
	/**
	* @struct ContactSolver is a struct that contains all the data and methods needed to calculates 
	* all the behaviors of a physical contact.
	*/
	struct ContactSolver
	{
		Body* bodyA = nullptr;
		Body* bodyB = nullptr;
		Collider* colliderA = nullptr;
		Collider* colliderB = nullptr;
		Math::Vec2F Normal;
		Math::Vec2F Point;
		float Penetration;

		float CalculateSeparatingVelocity() const noexcept;
		void ResolvePostCollisionVelocity() noexcept;
	};
}