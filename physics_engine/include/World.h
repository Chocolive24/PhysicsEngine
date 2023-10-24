#pragma once

/**
 * @headerfile World.h
 * This header defines the world class which handles the physical state of the bodies.
 * @author Olivier Pachoud
 */

#include "Body.h"
#include "Collider.h"
#include "ContactListener.h"
#include "References.h"

#include <vector>
#include <unordered_set>

namespace PhysicsEngine
{
    /**
     * @class World is a class that contains all the physical bodies in the program and calculates
     * their movements and changes in physical state.
     */
    class World
    {
    private:
        std::vector<Body> _bodies{};
        std::vector<std::size_t> _bodiesGenIndices{};

        ContactListener* _contactListener = nullptr;

        std::vector<Collider> _colliders{};
        std::vector<std::size_t> _collidersGenIndices{};

        std::vector<CircleCollider> _circleColliders{};
        std::vector<RectangleCollider> _rectangleColliders{};
        std::vector<PolygonCollider> _polygonColliders{};

        std::unordered_set<ColliderPair, ColliderHash> _colliderPairs{};

        static constexpr float _bodyAllocResizeFactor = 2.f;

        void updateCollisionDetection() noexcept;
        [[nodiscard]] bool detectCollision(Collider colA, Collider colB) noexcept;

    public:
        constexpr World() noexcept = default;

        /**
         * @brief Init is a method that pre-allocates memory for the desired number of bodies by creating invalid
         * bodies (aka bodies with negative mass).
         * @param preAllocatedBodyCount The number of bodies to pre-allocate in memory. Default value is 100.
         */
        void Init(int preAllocatedBodyCount = 100) noexcept;

        /**
         * @brief Update is a method that calculates the new velocities of all the world's valid bodies
         * according to their acceleration (calculated with 'F / m = a'), and their new positions according
         * to their new velocities.
         * @param deltaTime The time elapsed between two consecutive frames.
         */
        void Update(float deltaTime) noexcept;

        /**
         * @brief Deinit is a method that clears all bodies and colliders.
         */
        void Deinit() noexcept;

        /**
         * @brief SetContactListener is a method that sets the value of the world contact-listener with the
         * contact-listener given in parameter
         * @param contactListener The contact listener for the world.
         */
        void SetContactListener(ContactListener* contactListener) noexcept { _contactListener = contactListener; }

        /**
         * @brief CreateBody is a method that creates a body in the world and returns a BodyRef to this body.
         * @note Body position, velocity and forces are set to (0, 0) by default and mass is set to 1 by default.
         * @return A BodyRef to the body in the world (see BodyRef).
         */
        [[nodiscard]] BodyRef CreateBody() noexcept;

        /**
         * @brief DestroyBody is a method that destroys the body corresponding to the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to destroy.
         */
        void DestroyBody(BodyRef bodyRef) noexcept;

        /**
         * @brief GetBody is a method that gives the body corresponding to the BodyRef given as a parameter.
         * @param bodyRef The BodyRef to the body to get.
         * @return The Body corresponding to the body reference.
         */
        [[nodiscard]] Body& GetBody(BodyRef bodyRef);

        /**
         * @brief AllocatedBodies is a method that gives the number of allocated bodies.
         * @return The number of allocated bodies.
         */
        [[nodiscard]] std::size_t AllocatedBodies() const noexcept { return _bodies.size(); }

        /**
         * @brief GetCollider is a method that gives the collider corresponding to the collider reference
         * given in parameter.
         * @param colliderRef The collider reference to the collider to get.
         * @return The collider corresponding to the collider reference.
         */
        [[nodiscard]] Collider& GetCollider(ColliderRef colliderRef);

        /**
        * @brief DestroyCollider is a method that destroys the collider corresponding to the collider reference
         * given in parameter.
        * @param colRef The collider reference to the collider to destroy.
        */
        void DestroyCollider(ColliderRef colRef) noexcept;

        /**
         * @brief CreateCircleCollider is a method that creates a circle collider in the world and returns a
         * collider reference to this collider.
         * @note The radius of the circle collider is set to -1 by default.
         * @return A collider reference to the collider in the world (see ColliderRef).
         */
        [[nodiscard]] ColliderRef CreateCircleCollider(BodyRef bodyRef) noexcept;

        /**
         * @brief GetCircleCollider is a method that gives the circle collider corresponding to the shape index
         * given in parameter.
         * @param shapeIdx The shape index to the circle collider to get.
         * @return The circle collider corresponding to the shape index.
         */
        [[nodiscard]] CircleCollider& GetCircleCollider(int shapeIdx) noexcept { return _circleColliders[shapeIdx]; }

        /**
         * @brief CreateRectangleCollider is a method that creates a rectangle collider in the world and returns a
         * collider reference to this collider.
         * @note The half-size of the rectangle collider is set to (-1, -1) by default.
         * @return A collider reference to the collider in the world (see ColliderRef).
         */
        [[nodiscard]] ColliderRef CreateRectangleCollider(BodyRef bodyRef) noexcept;

        /**
         * @brief GetRectangleCollider is a method that gives the rectangle collider corresponding to the shape index
         * given in parameter.
         * @param shapeIdx The shape index to the rectangle collider to get.
         * @return The rectangle collider corresponding to the shape index.
         */
        [[nodiscard]] RectangleCollider& GetRectangleCollider(int shapeIdx) noexcept
        {
            return _rectangleColliders[shapeIdx];
        }

        /**
         * @brief CreatePolygonCollider is a method that creates a polygon collider in the world and returns a
         * collider reference to this collider.
         * @note There is no vertices by default.
         * @return A collider reference to the collider in the world (see ColliderRef).
         */
        [[nodiscard]] ColliderRef CreatePolygonCollider(BodyRef bodyRef) noexcept;

        /**
         * @brief GetPolygonCollider is a method that gives the polygon collider corresponding to the shape index
         * given in parameter.
         * @param shapeIdx The shape index to the polygon collider to get.
         * @return The polygon collider corresponding to the shape index.
         */
        [[nodiscard]] PolygonCollider& GetPolygonCollider(int shapeIdx) noexcept
        {
            return _polygonColliders[shapeIdx];
        }
    };
}

