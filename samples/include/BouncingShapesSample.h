#pragma once

#include "Sample.h"
#include "ContactListener.h"

class BouncingShapesSample final : public Sample, public PhysicsEngine::ContactListener
{
public:
	// Inherited via Sample
	std::string BouncingShapesSample::Name() const noexcept override
	{
		return "Bouncing shapes";
	}

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
	static constexpr SDL_Color GroundColor = { 255, 255, 255, 255 };
	static constexpr SDL_Color CircleColor = { 0, 0, 255, 255 };
	static constexpr SDL_Color RectangleColor = { 255, 0, 0, 255 };

	std::vector<PhysicsEngine::ColliderRef> _colliders;

	void createCircle(Math::Vec2F position) noexcept;
	void createRectangle(Math::Vec2F position) noexcept;

	void removeCollidersOutOfSBottomScreen() noexcept;

	// Inherited via Sample
	std::string InputText() const noexcept override;
};