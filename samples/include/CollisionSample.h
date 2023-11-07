#pragma once

#include "ContactListener.h"
#include "Sample.h"

#include "SDL.h"

class CollisionSample final : public Sample, public PhysicsEngine::ContactListener
{
public:
	// Inherited via Sample
	std::string Name() const noexcept override { return "Collision"; }
	std::string Description() const noexcept override;

	void onInit() noexcept override;
	void onHandleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) noexcept override;
	void onUpdate() noexcept override;
	void onRender() noexcept override;
	void onDeinit() noexcept override;

	// Inherited via ContactListener
	void OnTriggerEnter(PhysicsEngine::ColliderRef colliderRefA, 
						PhysicsEngine::ColliderRef colliderRefB) noexcept override;

	void OnTriggerStay(PhysicsEngine::ColliderRef colliderRefA, 
					   PhysicsEngine::ColliderRef colliderRefB) noexcept override;

	void OnTriggerExit(PhysicsEngine::ColliderRef colliderRefA, 
					   PhysicsEngine::ColliderRef colliderRefB) noexcept override;

	void OnCollisionEnter(PhysicsEngine::ColliderRef colliderRefA, 
						  PhysicsEngine::ColliderRef colliderRefB) noexcept override;

	void OnCollisionExit(PhysicsEngine::ColliderRef colliderRefA, 
						 PhysicsEngine::ColliderRef colliderRefB) noexcept override;

private:
	static constexpr int CircleColliderCount = 10;
	static constexpr int RectColliderCount = 10;
	static constexpr int TotalColliderCount = CircleColliderCount + RectColliderCount;

	std::array<PhysicsEngine::ColliderRef, TotalColliderCount> _colliderRefs;
	std::array<SDL_Color, TotalColliderCount> _colors;

	void maintainObjectsInWindow() noexcept;
};