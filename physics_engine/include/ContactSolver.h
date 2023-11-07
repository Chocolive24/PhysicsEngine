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

		/**
		* @brief CalculateContactProperties is a method that calculates the normal, the point and the 
		* penetration of the contact.
		*/ 
		void CalculateContactProperties() noexcept;

		/**
		* @brief CalculateSeparatingVelocity is a method that calculates the separating velocity between two 
		* bodies in contact.
		* @return The separating velocity between two bodies in contact.
		*/
		float CalculateSeparatingVelocity() const noexcept;

		/**
		* @brief ResolvePostCollisionVelocity is a method that calculates the velocity to be applied 
		* to the two colliding bodies  after their collision and applies these velocities to the 
		* corresponding body.
		*/
		void ResolvePostCollisionVelocity() noexcept;

		/**
		* @brief ResolvePostCollisionPosition is a method that calculates the position to be applied
		* to the two colliding bodies after their collision and applies these positions to the
		* corresponding body.
		*/
		void ResolvePostCollisionPosition() noexcept;

		/*
		* @brief ResolveContact is a method that calculates the velocity and the position to be applied
		* to the two colliding bodies after their collision and applied these values to the 
		* corresponding body.
		*/
		void ResolveContact() noexcept;
	};
}