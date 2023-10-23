#pragma once

#include "References.h"
#include "Shape.h"

namespace PhysicsEngine
{
    enum class ColliderShape
    {
        Circle,
        Rectangle,
        Polygon,
        NONE
    };

    class Collider
    {
    private:
        ColliderRef _colliderRef{};
        int _shapeIdx{-1}; // index is the shape collider vector. vector<CircleCollider> _circles -> shapeIdx
        BodyRef _bodyRef{};
        float _restitution{-1.f};
        float _friction{-1.f};
        bool _isTrigger{false};
        ColliderShape _shape{ColliderShape::NONE};

    public:
        constexpr Collider() noexcept = default;
        constexpr Collider(ColliderRef colRef,
                           int shapeIdx,
                           BodyRef bodyRef,
                           float restitution,
                           float friction,
                           bool isTrigger) noexcept
        {
            _colliderRef = colRef;
            _shapeIdx = shapeIdx;
            _bodyRef = bodyRef;
            _restitution = restitution;
            _friction = friction;
            _isTrigger = isTrigger;
        };

        [[nodiscard]] constexpr ColliderRef GetColliderRef() const noexcept { return _colliderRef; }
        //constexpr void SetColliderRef(ColliderRef colRef) noexcept { _colliderRef = colRef; }
        [[nodiscard]] constexpr int ShapeIdx() const noexcept { return _shapeIdx; }
        [[nodiscard]] constexpr BodyRef BodyRef() const noexcept { return _bodyRef; }
        [[nodiscard]] constexpr float Restitution() const noexcept { return _restitution; }
        [[nodiscard]] constexpr float Friction() const noexcept { return _friction; }
        [[nodiscard]] constexpr bool IsTrigger() const noexcept { return _isTrigger; }
    };

    struct CircleCollider
    {
        float Radius{-1};
    };

    struct RectangleCollider
    {
        Math::Vec2F HalfSize{-1.f, -1.f};
    };

    struct ColliderPair
    {
        Collider ColliderA;
        Collider ColliderB;
    };
}

