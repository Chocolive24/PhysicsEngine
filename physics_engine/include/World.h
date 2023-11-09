/**
 * @headerfile World.h
 * This header defines the world class which handles the physical state of the bodies.
 * @author Olivier Pachoud
 */

#pragma once

#include "Body.h"
#include "Collider.h"
#include "ContactSolver.h"
#include "ContactListener.h"
#include "QuadTree.h"
#include "WorldRefTypes.h"

#include <vector>
#include <unordered_set>

namespace PhysicsEngine
{
    /**
     * @brief World is a class that contains all the physical bodies in the program and calculates
     * their movements and changes in physical state.
     */
    class World
    {
    private:
        Math::Vec2F _gravity;

        HeapAllocator _heapAllocator;

        AllocVector<Body> _bodies{ StandardAllocator<Body>{_heapAllocator} };
        AllocVector<std::size_t> _bodiesGenIndices{ StandardAllocator<std::size_t>{_heapAllocator} };

        ContactListener* _contactListener = nullptr;

        AllocVector<Collider> _colliders{ StandardAllocator<Collider>{_heapAllocator} };
        AllocVector<std::size_t> _collidersGenIndices{ StandardAllocator<std::size_t>{_heapAllocator} };

        std::unordered_set<ColliderPair, 
            ColliderHash, 
            std::equal_to<ColliderPair>, 
            StandardAllocator<ColliderPair>> _colliderPairs{ StandardAllocator<ColliderPair>{_heapAllocator} };

        QuadTree _quadTree;

        static constexpr float _bodyAllocResizeFactor = 2.f;

        void resolveBroadPhase() noexcept;
        void resolveNarrowPhase() noexcept;
        bool detectContact(const Collider& colA, const Collider& colB) noexcept;

    public:
        World() noexcept = default;

        /**
         * @brief Init is a method that pre-allocates memory for the desired number of bodies by creating invalid
         * bodies (aka bodies with negative mass).
         * @param preAllocatedBodyCount The number of bodies to pre-allocate in memory. Default value is 100.
         */
        void Init(Math::Vec2F gravity = Math::Vec2F::Zero(), int preAllocatedBodyCount = 100) noexcept;

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
        * @brief Gravity is a method that gives the gravity of the world.
        * @return The gravity of the world.
        */
        constexpr Math::Vec2F Gravity() const noexcept { return _gravity; }

        /**
         * @brief SetGravity is a method that replaces the value of the current world gravity by the new one
         * given in parameter
         * @param newGravity The new gravity to apply to the world.
         */
        void SetGravity(Math::Vec2F newGravity) noexcept { _gravity = newGravity; }

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
         * @brief GetBodyCount is a method that gives the number of allocated bodies.
         * @return The number of allocated bodies.
         */
        [[nodiscard]] std::size_t GetBodyCount() const noexcept { return _bodies.size(); }

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
         * @brief CreateCollider is a method that creates a collider in the world and returns a
         * collider reference to this collider.
         * @param bodyRef The body reference to the body on which the collider would be attached.
         * @return A collider reference to the collider in the world (see ColliderRef).
         */
        [[nodiscard]] ColliderRef CreateCollider(BodyRef bodyRef) noexcept;

        /**
         * @brief QuadTree is a method that gives the quad-tree of the world.
         * @return The quad-tree of the world.
         */
        [[nodiscard]] const QuadTree& QuadTree() const noexcept { return _quadTree; };
    };
}

