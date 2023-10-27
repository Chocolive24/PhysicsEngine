#pragma once

/**
 * @headerfile ContactListener.h
 * This header file defines the ContactListener class in which is an interface for handling collider collision events.
 *
 * @author Olivier Pachoud
 */

#include "Collider.h"

namespace PhysicsEngine
{
    /**
     * @class ContactListener is an abstract base class for handling collider collision events.
     */
    class ContactListener
    {
    public:
       /**
       * @brief OnTriggerEnter is an abstract method that is called when two colliders begin intersecting and
       * at least one of them is in trigger state.
       * @param colliderRefA The collider reference of the first collider in the world.
       * @param colliderRefB The collider reference of the second collider in the world.
       */
       virtual void OnTriggerEnter(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;

      /**
      * @brief OnTriggerStay is an abstract method that is called when two colliders are currently intersecting and
      * at least one of them is in trigger state.
      * @param colliderRefA The collider reference of the first collider in the world.
      * @param colliderRefB The collider reference of the second collider in the world.
      */
       virtual void OnTriggerStay(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;

       /**
       * @brief OnTriggerExit is an abstract method that is called when two colliders stop intersecting and
       * at least one of them is in trigger state.
       * @param colliderRefA The collider reference of the first collider in the world.
       * @param colliderRefB The collider reference of the second collider in the world.
       */
       virtual void OnTriggerExit(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;
    };
}

