#pragma once

/**
 * \brief A collection of classes and functions for working with angles.
 * \author Alexis Haldy
 */

#include <stdexcept>
#include "Exception.h"

class Radian;

class Degree
{
public:
    Degree() = default;
    constexpr explicit Degree(float value) noexcept
    {
        _value = value;
    }

private:
    float _value { 0 };

public:
    constexpr explicit operator float() const noexcept
    {
        return _value;
    }

    constexpr operator Radian() const noexcept;

    [[nodiscard]] constexpr Degree(Radian radian) noexcept;

    constexpr Degree operator+(const Degree degree) const noexcept
    {
        return Degree(_value + degree._value);
    }

    constexpr Degree operator-(const Degree degree) const noexcept
    {
        return Degree(_value - degree._value);
    }

    constexpr Degree operator-() const noexcept
    {
        return Degree(-_value);
    }

    constexpr Degree operator+=(const Degree degree) noexcept
    {
        _value += degree._value;

        return *this;
    }

    constexpr Degree operator-=(const Degree degree) noexcept
    {
        _value -= degree._value;

        return *this;
    }

    constexpr Degree operator*(const float scalar) const noexcept
    {
        return Degree(_value * scalar);
    }

    constexpr Degree operator/(const float scalar) const
    {
        if (scalar == 0)
        {
            throw DivisionByZeroException();
        }

        return Degree(_value / scalar);
    }

    constexpr Degree operator*=(const float scalar) noexcept
    {
        _value *= scalar;

        return *this;
    }

    constexpr Degree operator/=(const float scalar)
    {
        if (scalar == 0)
        {
            throw DivisionByZeroException();
        }

        _value /= scalar;

        return *this;
    }

    constexpr bool operator==(const Degree degree) const noexcept
    {
        return _value == degree._value;
    }

    constexpr bool operator!=(const Degree degree) const noexcept
    {
        return !operator==(degree);
    }

    constexpr bool operator<(const Degree degree) const noexcept
    {
        return _value < degree._value;
    }

    constexpr bool operator>(const Degree degree) const noexcept
    {
        return _value > degree._value;
    }

    constexpr bool operator<=(const Degree degree) const noexcept
    {
        return !operator>(degree);
    }

    constexpr bool operator>=(const Degree degree) const noexcept
    {
        return !operator<(degree);
    }
};

class Radian
{
public:
    Radian() = default;
    constexpr explicit Radian(float value) noexcept
    {
        _value = value;
    }

private:
    float _value { 0 };
    
public:
    [[nodiscard]] constexpr Radian(Degree degree) noexcept
    {
	    _value = static_cast<float>(degree) * 3.14159265358979323846f / 180.0f;
    }

    constexpr explicit operator float() const noexcept
    {
        return _value;
    }

    constexpr Radian operator+(const Radian radian) const noexcept
    {
        return Radian(_value + radian._value);
    }

    constexpr Radian operator-(const Radian radian) const noexcept
    {
        return Radian(_value - radian._value);
    }

    constexpr Radian operator-() const noexcept
    {
        return Radian(-_value);
    }

    constexpr Radian operator+=(const Radian radian) noexcept
    {
        _value += radian._value;

        return *this;
    }

    constexpr Radian operator-=(const Radian radian) noexcept
    {
        _value -= radian._value;

        return *this;
    }

    constexpr Radian operator*(const float scalar) const noexcept
    {
        return Radian(_value * scalar);
    }

	friend Radian operator*(const float scalar, const Radian radian) noexcept
	{
		return radian * scalar;
	}

    constexpr Radian operator/(const float scalar) const
    {
        if (scalar == 0)
        {
            throw DivisionByZeroException();
        }

        return Radian(_value / scalar);
    }

    constexpr Radian operator*=(const float scalar) noexcept
    {
        _value *= scalar;

        return *this;
    }

    constexpr Radian operator/=(const float scalar)
    {
        if (scalar == 0)
        {
            throw DivisionByZeroException();
        }

        _value /= scalar;

        return *this;
    }

    constexpr bool operator==(const Radian radian) const noexcept
    {
        return _value == radian._value;
    }

    constexpr bool operator!=(const Radian radian) const noexcept
    {
        return !operator==(radian);
    }

    constexpr bool operator<(const Radian radian) const noexcept
    {
        return _value < radian._value;
    }

    constexpr bool operator>(const Radian radian) const noexcept
    {
        return _value > radian._value;
    }

    constexpr bool operator<=(const Radian radian) const noexcept
    {
        return !operator>(radian);
    }

    constexpr bool operator>=(const Radian radian) const noexcept
    {
        return !operator<(radian);
    }
};

constexpr Degree::operator Radian() const noexcept
{
	return Radian(_value);
}

constexpr Degree::Degree(Radian radian) noexcept
{
	_value = static_cast<float>(radian) * 180.0f / 3.14159265358979323846f;
}