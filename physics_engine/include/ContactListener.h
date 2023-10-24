#pragma once

#include "Collider.h"

namespace PhysicsEngine
{
    class ContactListener
    {
    public:
        virtual void OnTriggerEnter(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;
        virtual void OnTriggerStay(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;
        virtual void OnTriggerExit(ColliderRef colliderRefA, ColliderRef colliderRefB) noexcept = 0;
    };
}

