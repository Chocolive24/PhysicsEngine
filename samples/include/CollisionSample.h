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
	static constexpr int ColliderCount = 30;
	static constexpr SDL_Color _noCollisionColor{ 255, 0, 0, 255 };
	static constexpr SDL_Color _collisionColor{ 0, 255, 0, 255 };

	std::array<PhysicsEngine::ColliderRef, ColliderCount> _colliderRefs;
	std::array<int, ColliderCount> _collisionsCount;

	void maintainObjectsInWindow() noexcept;
};