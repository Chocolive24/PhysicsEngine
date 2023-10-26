#pragma once

/**
 * @headerfile Collider.h
 * This file defines the Collider class and related structures for handling colliders in the physics world.
 *
 * @author Olivier Pachoud
 */


#include "References.h"
#include "Shape.h"

#include <variant>
#include <utility>

namespace PhysicsEngine
{
    /**
     * @class Collider is a class that represents a generic collider.
     */
    class Collider
    {
    private:
        std::variant<Math::CircleF, Math::RectangleF, Math::PolygonF> _shape{
            Math::CircleF(Math::Vec2F::Zero(), 0.f)};
        BodyRef _bodyRef{};
        int _shapeIdx{-1};

        float _restitution{-1.f};
        float _friction{-1.f};
        bool _isTrigger{false};
        bool _enabled{false};

    public:
        constexpr Collider() noexcept = default;
        constexpr Collider(float restitution, float friction, bool isTrigger) noexcept
        {
            _restitution = restitution;
            _friction = friction;
            _isTrigger = isTrigger;
        };

        /**
         * @brief Shape is a method that gives the mathematical shape of the collider.
         * @return The mathematical shape of the collider.
         */
        [[nodiscard]] std::variant<Math::CircleF, Math::RectangleF, Math::PolygonF> Shape()
        const noexcept { return _shape; }

        /**
         * @brief SetShape is a method that replaces the current mathematical shape of the collider
         * with a circle shape given in parameter.
         * @param circle The new mathematical shape for the collider.
         */
        constexpr void SetShape(Math::CircleF circle) noexcept { _shape = circle; }

        /**
         * @brief SetShape is a method that replaces the current mathematical shape of the collider
         * with rectangle shape given in parameter.
         * @param rectangle The new mathematical shape for the collider.
         */
        constexpr void SetShape(Math::RectangleF rectangle) noexcept { _shape = rectangle; }

        /**
         * @brief SetShape is a method that replaces the current mathematical shape of the collider
         * with a polygon shape given in parameter.
         * @param polygon The new mathematical shape for the collider.
         */
        void SetShape(Math::PolygonF polygon) noexcept { _shape = polygon; }

        /**
         * @brief ShapeIdx is a method that gives the index of the shape of the collider in the world.
         * @return The index of the shape of the collider in the world.
         */
        [[nodiscard]] constexpr int ShapeIdx() const noexcept { return _shapeIdx; }

        /**
         * @brief SetShapeIdx is a method that replaces the current index of the shape of the collider
         * with the new shape index given in parameter.
         * @param newShapeIdx The new shape index for the collider.
         */
        constexpr void SetShapeIdx(int newShapeIdx) noexcept { _shapeIdx = newShapeIdx; }

        /**
         * @brief GetBodyRef is a method that gives the body reference of the collider in the world.
         * @return The body reference of the collider in the world.
         */
        [[nodiscard]] constexpr BodyRef GetBodyRef() const noexcept { return _bodyRef; }

        /**
        * @brief SetBodyRef is a method that replaces the current body reference of the collider
        * with the new body reference given in parameter.
        * @param newBodyRef The new body reference for the collider.
        */
        constexpr void SetBodyRef(BodyRef newBodyRef) noexcept { _bodyRef = newBodyRef; }

        /**
         * @brief Restitution is a method that gives the restitution of the collider.
         * @return The restitution of the collider.
         */
        [[nodiscard]] constexpr float Restitution() const noexcept { return _restitution; }

        /**
        * @brief SetRestitution is a method that replaces the current restitution of the collider
        * with the new restitution given in parameter.
        * @param newRestitution The new restitution for the collider.
        */
        constexpr void SetRestitution(float newRestitution) noexcept { _restitution = newRestitution; }

        /**
         * @brief Friction is a method that gives the friction of the collider.
         * @return The friction of the collider.
         */
        [[nodiscard]] constexpr float Friction() const noexcept { return _friction; }

        /**
        * @brief SetFriction is a method that replaces the current friction of the collider
        * with the new friction given in parameter.
        * @param newFriction The new friction for the collider.
        */
        constexpr void SetFriction(float newFriction) noexcept { _friction = newFriction; }

        /**
         * @brief IsTrigger is a method that checks if the collider is trigger (aka if it detects collision
         * but don't act physically.
         * @return True if the collider is trigger.
         */
        [[nodiscard]] constexpr bool IsTrigger() const noexcept { return _isTrigger; }

        /**
        * @brief SetIsTrigger is a method that replaces the current trigger state of the collider
        * with the trigger state given in parameter.
        * @param isTrigger The new trigger state for the collider.
        */
        constexpr void SetIsTrigger(const bool isTrigger) noexcept { _isTrigger = isTrigger; }

        /**
         * @brief Enabled is a method that checks if the collider is valid (aka if it has a mathematical shape).
         * @return True if the collider is valid.
         */
        [[nodiscard]] constexpr bool Enabled() const noexcept { return _enabled; }

        /**
        * @brief SetEnabled is a method that replaces the current enabled state of the collider with the new enabled
        * state given in parameter.
        * @param enabled Whether the collider is enabled or not.
        */
        constexpr void SetEnabled(const bool enabled) noexcept { _enabled = enabled; }
    };

    /**
     * @class CircleCollider is a class that represents a circle-shaped collider.
     */
    class CircleCollider
    {
    private:
        float _radius{-1};

    public:
        constexpr CircleCollider() noexcept = default;
        explicit constexpr CircleCollider(float radius) noexcept : _radius(radius) {};

        /**
         * @brief Radius is a method that gives the radius of the circle collider.
         * @return The radius of the circle collider.
         */
        [[nodiscard]] constexpr float Radius() const noexcept { return _radius; }

        /**
        * @brief SetRadius is a method that replaces the current radius of the circle collider
        * with the new radius given in parameter.
        * @param newRadius The new radius for the circle collider.
        */
        constexpr void SetRadius(float newRadius) noexcept { _radius = newRadius; }

        /**
         * @brief Enabled is a method that checks if the circle collider is valid
         * (aka if it has a radius greater than 0).
         * @return True if the circle collider is valid.
         */
        [[nodiscard]] constexpr bool IsValid() const noexcept { return _radius > 0; };
    };

    /**
    * @class RectangleCollider is a class that represents a rectangle-shaped collider.
    */
    class RectangleCollider
    {
    private:
        Math::Vec2F _halfSize{-1.f, -1.f};

    public:
        constexpr RectangleCollider() noexcept = default;
        explicit constexpr RectangleCollider(Math::Vec2F halfSize) noexcept : _halfSize(halfSize) {};

        /**
         * @brief HalfSize is a method that gives the half-size of the rectangle collider.
         * @return The half-size of the rectangle collider.
         */
        [[nodiscard]] constexpr Math::Vec2F HalfSize() const noexcept { return _halfSize; }

        /**
        * @brief SetRadius is a method that replaces the current half-size of the rectangle collider
        * with the new half-size given in parameter.
        * @param newHalfSize The new half-Size for the rectangle collider.
        */
        constexpr void SetHalfSize(Math::Vec2F newHalfSize) noexcept { _halfSize = newHalfSize; }


        /**
         * @brief Enabled is a method that checks if the rectangle collider is valid
         * (aka if it has a half-width and a half-height greater than 0).
         * @return True if the rectangle collider is valid.
         */
        [[nodiscard]] constexpr bool IsValid() const noexcept
        {
            return _halfSize.X > 0 && _halfSize.Y > 0;
        };
    };

    /**
    * @class PolygonCollider is a class that represents a polygon-shaped collider.
    */
    class PolygonCollider
    {
    private:
        std::vector<Math::Vec2F> _vertices{};

    public:
        PolygonCollider() noexcept = default;
        explicit PolygonCollider(std::vector<Math::Vec2F>& vertices) noexcept : _vertices(std::move(vertices)) {};

        /**
         * @brief Vertices is a method that gives the vertices of the polygon collider.
         * @return The vertices of the polygon collider.
         */
        [[nodiscard]] std::vector<Math::Vec2F> Vertices() const noexcept { return _vertices; }

        /**
         * @brief VerticesCount is a method that gives the number of vertices of the polygon collider.
         * @return The number of vertices of the polygon collider.
         */
        [[nodiscard]] constexpr std::size_t VerticesCount() const noexcept { return _vertices.size(); }

        /**
        * @brief SetVertices is a method that replaces the current vertices of the polygon collider
        * with the new vertices given in parameter.
        * @param newVertices The new vertices for the polygon collider.
        */
        void SetVertices(std::vector<Math::Vec2F> newVertices) noexcept { _vertices = std::move(newVertices); }

        /**
         * @brief Enabled is a method that checks if the polygon collider is valid
         * (aka if it has a at least 3 vertices).
         * @return True if the polygon collider is valid.
         */
        [[nodiscard]] constexpr bool IsValid() const noexcept
        {
            return _vertices.size() > 2;
        };
    };

    /**
     * @struct ColliderPair
     * Represents a pair of colliders for collision detection.
     */
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

    /**
    * @struct ColliderHash
    * Provides a custom hash function for ColliderPair objects.
    */
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

