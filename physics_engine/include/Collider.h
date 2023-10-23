#pragma once

#include "References.h"
#include "Shape.h"

namespace PhysicsEngine
{
    class Collider
    {
    private:
        Math::ShapeType _shape{Math::ShapeType::None};
        ColliderRef _colliderRef{};
        int _shapeIdx{-1}; // index is the shape collider vector. vector<CircleCollider> _circles -> shapeIdx
        BodyRef _bodyRef{};

        float _restitution{-1.f};
        float _friction{-1.f};
        bool _isTrigger{false};

    public:
        constexpr Collider() noexcept = default;
        constexpr Collider(float restitution, float friction, bool isTrigger) noexcept
        {
            _restitution = restitution;
            _friction = friction;
            _isTrigger = isTrigger;
        };

        [[nodiscard]] constexpr Math::ShapeType Shape() const noexcept { return _shape; }
        constexpr void SetShape(Math::ShapeType newShape) noexcept { _shape = newShape; }

        [[nodiscard]] constexpr ColliderRef GetColliderRef() const noexcept { return _colliderRef; }
        constexpr void SetColliderRef(ColliderRef colRef) noexcept { _colliderRef = colRef; }

        [[nodiscard]] constexpr int ShapeIdx() const noexcept { return _shapeIdx; }
        constexpr void SetShapeIdx(int newShapeIdx) noexcept { _shapeIdx = newShapeIdx; }

        [[nodiscard]] constexpr BodyRef GetBodyRef() const noexcept { return _bodyRef; }
        constexpr void SetBodyRef(BodyRef newBodyRef) noexcept { _bodyRef = newBodyRef; }

        [[nodiscard]] constexpr float Restitution() const noexcept { return _restitution; }
        constexpr void SetRestitution(float newRestitution) noexcept { _restitution = newRestitution; }

        [[nodiscard]] constexpr float Friction() const noexcept { return _friction; }
        constexpr void SetFriction(float newFriction) noexcept { _friction = newFriction; }

        [[nodiscard]] constexpr bool IsTrigger() const noexcept { return _isTrigger; }
        constexpr void SetIsTrigger(bool isTrigger) noexcept { _isTrigger = isTrigger; }

        [[nodiscard]] constexpr bool IsValid() const noexcept { return _shape != Math::ShapeType::None; }
    };

    class CircleCollider
    {
    private:
        float _radius{-1};

    public:
        constexpr CircleCollider() noexcept = default;
        explicit constexpr CircleCollider(float radius) noexcept : _radius(radius) {};

        [[nodiscard]] constexpr float Radius() const noexcept { return _radius; }
        constexpr void SetRadius(float newRadius) noexcept { _radius = newRadius; }

        [[nodiscard]] constexpr bool IsValid() const noexcept { return _radius > 0; };
    };

    struct RectangleCollider
    {
        Math::Vec2F HalfSize{-1.f, -1.f};
    };

    struct ColliderPair
    {
        ColliderRef ColliderA;
        ColliderRef ColliderB;

        bool operator==(const ColliderPair& other) const noexcept
        {
            return ColliderA == other.ColliderA && ColliderB == other.ColliderB ||
                   ColliderA == other.ColliderB && ColliderB == other.ColliderA;
        }

        bool operator<(const ColliderPair& other) const noexcept
        {
            return ColliderA < other.ColliderA || (ColliderA == other.ColliderA && ColliderB < other.ColliderB);
        }
    };

    struct ColliderHash
    {
        std::size_t operator()(const ColliderPair& pair) const noexcept
        {
            const std::size_t hash1 = std::hash<int>{}(static_cast<int>(pair.ColliderA.Index));
            const std::size_t hash2 = std::hash<int>{}(static_cast<int>(pair.ColliderB.Index));

            return hash1 + hash2;
        }
    };
}

