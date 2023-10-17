//
// Created by Coch on 08.10.2023.
//

#pragma once

#include <array>

#include "Intrinsics.h"
#include "Vec3.h"

template<typename T, int N>
class NVec3
{
private:
    std::array<T, N> _x = std::array<T, N>();
    std::array<T, N> _y = std::array<T, N>();
    std::array<T, N> _z = std::array<T, N>();

public:
    [[nodiscard]] const auto &X() const noexcept
    { return _x; }

    [[nodiscard]] const auto &Y() const noexcept
    { return _y; }

    [[nodiscard]] const auto &Z() const noexcept
    { return _z; }

    NVec3() = default;

    NVec3(const NVec3<T, N> &vec) = default;

    constexpr explicit NVec3(const std::array<Vec3<T>, N> vecs) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] = vecs[i].X;
            _y[i] = vecs[i].Y;
            _z[i] = vecs[i].Z;
        }
    }

    constexpr explicit NVec3(const Vec3<T> vec) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] = vec.X;
            _y[i] = vec.Y;
            _z[i] = vec.Z;
        }
    }

    NVec3<T, N> operator+(const NVec3<T, N> &nVec3) const noexcept
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._x[i] = _x[i] + nVec3._x[i];
            result._y[i] = _y[i] + nVec3._y[i];
            result._z[i] = _z[i] + nVec3._z[i];
        }

        return result;
    }

    NVec3<T, N> &operator+=(const NVec3<T, N> &nVec3) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] += nVec3._x[i];
            _y[i] += nVec3._y[i];
            _z[i] += nVec3._z[i];
        }

        return *this;
    }

    NVec3<T, N> operator-() const noexcept
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._x[i] = -_x[i];
            result._y[i] = -_y[i];
            result._z[i] = -_z[i];
        }

        return result;
    }

    NVec3<T, N> operator-(const NVec3<T, N> &nVec3) const noexcept
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._x[i] = _x[i] - nVec3._x[i];
            result._y[i] = _y[i] - nVec3._y[i];
            result._z[i] = _z[i] - nVec3._z[i];
        }

        return result;
    }

    NVec3<T, N> &operator-=(const NVec3<T, N> &nVec3) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] -= nVec3._x[i];
            _y[i] -= nVec3._y[i];
            _z[i] -= nVec3._z[i];
        }

        return *this;
    }

    NVec3<T, N> operator*(const NVec3<T, N> &nVec3) const noexcept
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._x[i] = _x[i] * nVec3._x[i];
            result._y[i] = _y[i] * nVec3._y[i];
            result._z[i] = _z[i] * nVec3._z[i];
        }

        return result;
    }

    NVec3<T, N> &operator*=(const NVec3<T, N> &nVec3) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] *= nVec3._x[i];
            _y[i] *= nVec3._y[i];
            _z[i] *= nVec3._z[i];
        }

        return *this;
    }

    NVec3<T, N> operator/(const NVec3<T, N> &nVec3) const
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            if (nVec3._x[i] == 0 || nVec3._y[i] == 0 || nVec3._z[i] == 0)
            {
                throw DivisionByZeroException();
            }

            result._x[i] = _x[i] / nVec3._x[i];
            result._y[i] = _y[i] / nVec3._y[i];
            result._z[i] = _z[i] / nVec3._z[i];
        }

        return result;
    }

    NVec3<T, N> &operator/=(const NVec3<T, N> &nVec3)
    {
        for (int i = 0; i < N; i++)
        {
            if (nVec3._x[i] == 0 || nVec3._y[i] == 0 || nVec3._z[i] == 0)
            {
                throw DivisionByZeroException();
            }

            _x[i] /= nVec3._x[i];
            _y[i] /= nVec3._y[i];
            _z[i] /= nVec3._z[i];
        }

        return *this;
    }

    NVec3<T, N> operator*(const T *array1N) const noexcept
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._x[i] = _x[i] * array1N[i];
            result._y[i] = _y[i] * array1N[i];
            result._z[i] = _z[i] * array1N[i];
        }

        return result;
    }

    NVec3<T, N> &operator*=(const T *array1N) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _x[i] *= array1N[i];
            _y[i] *= array1N[i];
            _z[i] *= array1N[i];
        }

        return *this;
    }

    NVec3<T, N> operator/(const T *array1N) const
    {
        NVec3<T, N> result = NVec3<T, N>();

        for (int i = 0; i < N; i++)
        {
            if (array1N[i] == 0)
            {
                throw DivisionByZeroException();
            }

            result._x[i] = _x[i] / array1N[i];
            result._y[i] = _y[i] / array1N[i];
            result._z[i] = _z[i] / array1N[i];
        }

        return result;
    }

    NVec3<T, N> &operator/=(const T *array1N)
    {
        for (int i = 0; i < N; i++)
        {
            if (array1N[i] == 0)
            {
                throw DivisionByZeroException();
            }

            _x[i] /= array1N[i];
            _y[i] /= array1N[i];
            _z[i] / array1N[i];
        }

        return *this;
    }

    static std::array<T, N> Dot(const NVec3<T, N> &nV1, const NVec3<T, N> &nV2) noexcept
    {
        std::array<T, N> result = std::array<T, N>();

        for (int i = 0; i < N; i++)
        {
            result[i] = nV1._x[i] * nV2._x[i] + nV1._y[i] * nV2._y[i] + nV1._z[i] * nV2._z[i];
        }

        return result;
    }

    [[nodiscard]] std::array<T, N> SquareMagnitude() const noexcept
    {
        return Dot(*this, *this);
    }

    [[nodiscard]] std::array<T, N> Magnitude() const noexcept
    {
        std::array<T, N> sqrtMagnitude = SquareMagnitude();

        for (int i = 0; i < N; i++)
        {
            sqrtMagnitude[i] = std::sqrt(sqrtMagnitude[i]);
        }

        return sqrtMagnitude;
    }

    [[nodiscard]] std::array<T, N> Normalized() const
    {
        const auto magnitude = Magnitude();

        for (int i = 0; i < N; i++)
        {
            if (magnitude[i] == 0)
            {
                throw DivisionByZeroException();
            }
        }

        const auto array1N = SquareMagnitude();
        std::array<T, N> reciprocalSqrt = std::array<T, N>();

        for (int i = 0; i < N; i++)
        {
            reciprocalSqrt[i] = 1 / std::sqrt(array1N[i]);
        }

        return reciprocalSqrt;
    }
};

using FourVec3F = NVec3<float, 4>;
using EightVec3F = NVec3<float, 8>;
using FourVec3I = NVec3<int, 4>;
using EightVec3I = NVec3<int, 8>;

#pragma region EightVec3F

template<>
inline EightVec3F EightVec3F::operator+(const EightVec3F &nVec2) const noexcept
{
    EightVec3F result = EightVec3F();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_add_ps(x1, x2);
    __m256 y1y2 = _mm256_add_ps(y1, y2);
    __m256 z1z2 = _mm256_add_ps(z1, z2);

    _mm256_storeu_ps(result._x.data(), x1x2);
    _mm256_storeu_ps(result._y.data(), y1y2);
    _mm256_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline EightVec3F &EightVec3F::operator+=(const EightVec3F &nVec2) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());


    __m256 x1x2 = _mm256_add_ps(x1, x2);
    __m256 y1y2 = _mm256_add_ps(y1, y2);
    __m256 z1z2 = _mm256_add_ps(z1, z2);

    _mm256_storeu_ps(_x.data(), x1x2);
    _mm256_storeu_ps(_y.data(), y1y2);
    _mm256_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline EightVec3F EightVec3F::operator-() const noexcept
{
    EightVec3F result = EightVec3F();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());

    __m256 x1x2 = _mm256_sub_ps(_mm256_setzero_ps(), x1);
    __m256 y1y2 = _mm256_sub_ps(_mm256_setzero_ps(), y1);
    __m256 z1z2 = _mm256_sub_ps(_mm256_setzero_ps(), z1);

    _mm256_storeu_ps(result._x.data(), x1x2);
    _mm256_storeu_ps(result._y.data(), y1y2);
    _mm256_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline EightVec3F EightVec3F::operator-(const EightVec3F &nVec2) const noexcept
{
    EightVec3F result = EightVec3F();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_sub_ps(x1, x2);
    __m256 y1y2 = _mm256_sub_ps(y1, y2);
    __m256 z1z2 = _mm256_sub_ps(z1, z2);

    _mm256_storeu_ps(result._x.data(), x1x2);
    _mm256_storeu_ps(result._y.data(), y1y2);
    _mm256_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline EightVec3F &EightVec3F::operator-=(const EightVec3F &nVec2) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_sub_ps(x1, x2);
    __m256 y1y2 = _mm256_sub_ps(y1, y2);
    __m256 z1z2 = _mm256_sub_ps(z1, z2);

    _mm256_storeu_ps(_x.data(), x1x2);
    _mm256_storeu_ps(_y.data(), y1y2);
    _mm256_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline EightVec3F EightVec3F::operator*(const EightVec3F &nVec2) const noexcept
{
    EightVec3F result = EightVec3F();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_mul_ps(x1, x2);
    __m256 y1y2 = _mm256_mul_ps(y1, y2);
    __m256 z1z2 = _mm256_mul_ps(z1, z2);

    _mm256_storeu_ps(result._x.data(), x1x2);
    _mm256_storeu_ps(result._y.data(), y1y2);
    _mm256_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline EightVec3F &EightVec3F::operator*=(const EightVec3F &nVec2) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_mul_ps(x1, x2);
    __m256 y1y2 = _mm256_mul_ps(y1, y2);
    __m256 z1z2 = _mm256_mul_ps(z1, z2);

    _mm256_storeu_ps(_x.data(), x1x2);
    _mm256_storeu_ps(_y.data(), y1y2);
    _mm256_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline EightVec3F EightVec3F::operator/(const EightVec3F &nVec2) const
{
    EightVec3F result = EightVec3F();

    for (int i = 0; i < 8; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_div_ps(x1, x2);
    __m256 y1y2 = _mm256_div_ps(y1, y2);
    __m256 z1z2 = _mm256_div_ps(z1, z2);

    _mm256_storeu_ps(result._x.data(), x1x2);
    _mm256_storeu_ps(result._y.data(), y1y2);
    _mm256_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline EightVec3F &EightVec3F::operator/=(const EightVec3F &nVec2)
{
    for (int i = 0; i < 8; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 x2 = _mm256_loadu_ps(nVec2._x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 y2 = _mm256_loadu_ps(nVec2._y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());
    __m256 z2 = _mm256_loadu_ps(nVec2._z.data());

    __m256 x1x2 = _mm256_div_ps(x1, x2);
    __m256 y1y2 = _mm256_div_ps(y1, y2);
    __m256 z1z2 = _mm256_div_ps(z1, z2);

    _mm256_storeu_ps(_x.data(), x1x2);
    _mm256_storeu_ps(_y.data(), y1y2);
    _mm256_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline std::array<float, 8> EightVec3F::Dot(const NVec3<float, 8> &nV1, const NVec3<float, 8> &nV2) noexcept
{
    std::array<float, 8> result = std::array<float, 8>();

    __m256 x1 = _mm256_loadu_ps(nV1._x.data());
    __m256 y1 = _mm256_loadu_ps(nV1._y.data());
    __m256 z1 = _mm256_loadu_ps(nV1._z.data());

    __m256 x2 = _mm256_loadu_ps(nV2._x.data());
    __m256 y2 = _mm256_loadu_ps(nV2._y.data());
    __m256 z2 = _mm256_loadu_ps(nV2._z.data());

    __m256 x1x2 = _mm256_mul_ps(x1, x2);
    __m256 y1y2 = _mm256_mul_ps(y1, y2);
    __m256 z1z2 = _mm256_mul_ps(z1, z2);

    __m256 resultPartial = _mm256_add_ps(x1x2, y1y2);
    resultPartial = _mm256_add_ps(resultPartial, z1z2);

    _mm256_storeu_ps(result.data(), resultPartial);

    return result;
}

template<>
inline std::array<float, 8> EightVec3F::SquareMagnitude() const noexcept
{
    std::array<float, 8> result = std::array<float, 8>();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());

    __m256 x1x2 = _mm256_mul_ps(x1, x1);
    __m256 y1y2 = _mm256_mul_ps(y1, y1);
    __m256 z1z2 = _mm256_mul_ps(z1, z1);

    __m256 resultPartial = _mm256_add_ps(x1x2, y1y2);
    resultPartial = _mm256_add_ps(resultPartial, z1z2);

    _mm256_storeu_ps(result.data(), resultPartial);

    return result;
}

template<>
inline std::array<float, 8> EightVec3F::Magnitude() const noexcept
{
    std::array<float, 8> result = std::array<float, 8>();

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());

    __m256 x1x2 = _mm256_mul_ps(x1, x1);
    __m256 y1y2 = _mm256_mul_ps(y1, y1);
    __m256 z1z2 = _mm256_mul_ps(z1, z1);

    __m256 resultPartial = _mm256_add_ps(x1x2, y1y2);
    resultPartial = _mm256_add_ps(resultPartial, z1z2);

    __m256 resultSqrt = _mm256_sqrt_ps(resultPartial);

    _mm256_storeu_ps(result.data(), resultSqrt);

    return result;
}

template<>
inline std::array<float, 8> EightVec3F::Normalized() const
{
    std::array<float, 8> result = std::array<float, 8>();

    // Check if magnitude is 0.
    const auto magnitude = Magnitude();

    for (int i = 0; i < 8; i++)
    {
        if (magnitude[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256 x1 = _mm256_loadu_ps(_x.data());
    __m256 y1 = _mm256_loadu_ps(_y.data());
    __m256 z1 = _mm256_loadu_ps(_z.data());

    __m256 xMul = _mm256_mul_ps(x1, x1);
    __m256 yMul = _mm256_mul_ps(y1, y1);
    __m256 zMul = _mm256_mul_ps(z1, z1);

    __m256 resultPartial = _mm256_add_ps(xMul, yMul);
    resultPartial = _mm256_add_ps(resultPartial, zMul);

    __m256 resultSqrt = _mm256_sqrt_ps(resultPartial);

    __m256 resultSqrtReciprocal = _mm256_rcp_ps(resultSqrt);

    _mm256_storeu_ps(result.data(), resultSqrtReciprocal);

    return result;
}

#pragma endregion

#pragma region FourVec3F

template<>
inline FourVec3F FourVec3F::operator+(const FourVec3F &nVec2) const noexcept
{
    FourVec3F result = FourVec3F();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_add_ps(x1, x2);
    __m128 y1y2 = _mm_add_ps(y1, y2);
    __m128 z1z2 = _mm_add_ps(z1, z2);

    _mm_storeu_ps(result._x.data(), x1x2);
    _mm_storeu_ps(result._y.data(), y1y2);
    _mm_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline FourVec3F &FourVec3F::operator+=(const FourVec3F &nVec2) noexcept
{
    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());


    __m128 x1x2 = _mm_add_ps(x1, x2);
    __m128 y1y2 = _mm_add_ps(y1, y2);
    __m128 z1z2 = _mm_add_ps(z1, z2);

    _mm_storeu_ps(_x.data(), x1x2);
    _mm_storeu_ps(_y.data(), y1y2);
    _mm_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline FourVec3F FourVec3F::operator-() const noexcept
{
    FourVec3F result = FourVec3F();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());

    __m128 x1x2 = _mm_sub_ps(_mm_setzero_ps(), x1);
    __m128 y1y2 = _mm_sub_ps(_mm_setzero_ps(), y1);
    __m128 z1z2 = _mm_sub_ps(_mm_setzero_ps(), z1);

    _mm_storeu_ps(result._x.data(), x1x2);
    _mm_storeu_ps(result._y.data(), y1y2);
    _mm_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline FourVec3F FourVec3F::operator-(const FourVec3F &nVec2) const noexcept
{
    FourVec3F result = FourVec3F();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_sub_ps(x1, x2);
    __m128 y1y2 = _mm_sub_ps(y1, y2);
    __m128 z1z2 = _mm_sub_ps(z1, z2);

    _mm_storeu_ps(result._x.data(), x1x2);
    _mm_storeu_ps(result._y.data(), y1y2);
    _mm_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline FourVec3F &FourVec3F::operator-=(const FourVec3F &nVec2) noexcept
{
    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_sub_ps(x1, x2);
    __m128 y1y2 = _mm_sub_ps(y1, y2);
    __m128 z1z2 = _mm_sub_ps(z1, z2);

    _mm_storeu_ps(_x.data(), x1x2);
    _mm_storeu_ps(_y.data(), y1y2);
    _mm_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline FourVec3F FourVec3F::operator*(const FourVec3F &nVec2) const noexcept
{
    FourVec3F result = FourVec3F();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x2);
    __m128 y1y2 = _mm_mul_ps(y1, y2);
    __m128 z1z2 = _mm_mul_ps(z1, z2);

    _mm_storeu_ps(result._x.data(), x1x2);
    _mm_storeu_ps(result._y.data(), y1y2);
    _mm_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline FourVec3F &FourVec3F::operator*=(const FourVec3F &nVec2) noexcept
{
    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x2);
    __m128 y1y2 = _mm_mul_ps(y1, y2);
    __m128 z1z2 = _mm_mul_ps(z1, z2);

    _mm_storeu_ps(_x.data(), x1x2);
    _mm_storeu_ps(_y.data(), y1y2);
    _mm_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline FourVec3F FourVec3F::operator/(const FourVec3F &nVec2) const
{
    FourVec3F result = FourVec3F();

    for (int i = 0; i < 4; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_div_ps(x1, x2);
    __m128 y1y2 = _mm_div_ps(y1, y2);
    __m128 z1z2 = _mm_div_ps(z1, z2);

    _mm_storeu_ps(result._x.data(), x1x2);
    _mm_storeu_ps(result._y.data(), y1y2);
    _mm_storeu_ps(result._z.data(), z1z2);

    return result;
}

template<>
inline FourVec3F &FourVec3F::operator/=(const FourVec3F &nVec2)
{
    for (int i = 0; i < 4; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 x2 = _mm_loadu_ps(nVec2._x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 y2 = _mm_loadu_ps(nVec2._y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());
    __m128 z2 = _mm_loadu_ps(nVec2._z.data());

    __m128 x1x2 = _mm_div_ps(x1, x2);
    __m128 y1y2 = _mm_div_ps(y1, y2);
    __m128 z1z2 = _mm_div_ps(z1, z2);

    _mm_storeu_ps(_x.data(), x1x2);
    _mm_storeu_ps(_y.data(), y1y2);
    _mm_storeu_ps(_z.data(), z1z2);

    return *this;
}

template<>
inline std::array<float, 4> FourVec3F::Dot(const NVec3<float, 4> &nV1, const NVec3<float, 4> &nV2) noexcept
{
    std::array<float, 4> result = std::array<float, 4>();

    __m128 x1 = _mm_loadu_ps(nV1._x.data());
    __m128 y1 = _mm_loadu_ps(nV1._y.data());
    __m128 z1 = _mm_loadu_ps(nV1._z.data());

    __m128 x2 = _mm_loadu_ps(nV2._x.data());
    __m128 y2 = _mm_loadu_ps(nV2._y.data());
    __m128 z2 = _mm_loadu_ps(nV2._z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x2);
    __m128 y1y2 = _mm_mul_ps(y1, y2);
    __m128 z1z2 = _mm_mul_ps(z1, z2);

    __m128 resultPartial = _mm_add_ps(x1x2, y1y2);
    resultPartial = _mm_add_ps(resultPartial, z1z2);

    _mm_storeu_ps(result.data(), resultPartial);

    return result;
}

template<>
inline std::array<float, 4> FourVec3F::SquareMagnitude() const noexcept
{
    std::array<float, 4> result = std::array<float, 4>();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x1);
    __m128 y1y2 = _mm_mul_ps(y1, y1);
    __m128 z1z2 = _mm_mul_ps(z1, z1);

    __m128 resultPartial = _mm_add_ps(x1x2, y1y2);
    resultPartial = _mm_add_ps(resultPartial, z1z2);

    _mm_storeu_ps(result.data(), resultPartial);

    return result;
}

template<>
inline std::array<float, 4> FourVec3F::Magnitude() const noexcept
{
    std::array<float, 4> result = std::array<float, 4>();

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x1);
    __m128 y1y2 = _mm_mul_ps(y1, y1);
    __m128 z1z2 = _mm_mul_ps(z1, z1);

    __m128 resultPartial = _mm_add_ps(x1x2, y1y2);
    resultPartial = _mm_add_ps(resultPartial, z1z2);

    __m128 resultSqrt = _mm_sqrt_ps(resultPartial);

    _mm_storeu_ps(result.data(), resultSqrt);

    return result;
}

template<>
inline std::array<float, 4> FourVec3F::Normalized() const
{
    std::array<float, 4> result = std::array<float, 4>();

    // Check if magnitude is 0.
    const auto magnitude = Magnitude();

    for (int i = 0; i < 4; i++)
    {
        if (magnitude[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128 x1 = _mm_loadu_ps(_x.data());
    __m128 y1 = _mm_loadu_ps(_y.data());
    __m128 z1 = _mm_loadu_ps(_z.data());

    __m128 x1x2 = _mm_mul_ps(x1, x1);
    __m128 y1y2 = _mm_mul_ps(y1, y1);
    __m128 z1z2 = _mm_mul_ps(z1, z1);

    __m128 resultPartial = _mm_add_ps(x1x2, y1y2);
    resultPartial = _mm_add_ps(resultPartial, z1z2);

    __m128 resultSqrt = _mm_sqrt_ps(resultPartial);

    __m128 resultSqrtReciprocal = _mm_rcp_ps(resultSqrt);

    _mm_storeu_ps(result.data(), resultSqrtReciprocal);

    return result;
}

#pragma endregion

#pragma region EightVec3I

template<>
inline EightVec3I EightVec3I::operator+(const EightVec3I &nVec2) const noexcept
{
    EightVec3I result = EightVec3I();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_add_epi32(x1, x2);
    __m256i y1y2 = _mm256_add_epi32(y1, y2);
    __m256i z1z2 = _mm256_add_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline EightVec3I &EightVec3I::operator+=(const EightVec3I &nVec2) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_add_epi32(x1, x2);
    __m256i y1y2 = _mm256_add_epi32(y1, y2);
    __m256i z1z2 = _mm256_add_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_z.data()), z1z2);

    return *this;
}

template<>
inline EightVec3I EightVec3I::operator-() const noexcept
{
    EightVec3I result = EightVec3I();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));

    __m256i x1x2 = _mm256_sub_epi32(_mm256_setzero_si256(), x1);
    __m256i y1y2 = _mm256_sub_epi32(_mm256_setzero_si256(), y1);
    __m256i z1z2 = _mm256_sub_epi32(_mm256_setzero_si256(), z1);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline EightVec3I EightVec3I::operator-(const EightVec3I &nVec2) const noexcept
{
    EightVec3I result = EightVec3I();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_sub_epi32(x1, x2);
    __m256i y1y2 = _mm256_sub_epi32(y1, y2);
    __m256i z1z2 = _mm256_sub_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline EightVec3I &EightVec3I::operator-=(const EightVec3I &nVec2) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_sub_epi32(x1, x2);
    __m256i y1y2 = _mm256_sub_epi32(y1, y2);
    __m256i z1z2 = _mm256_sub_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_z.data()), z1z2);

    return *this;
}

template<>
inline EightVec3I EightVec3I::operator*(const EightVec3I &nVec2) const noexcept
{
    EightVec3I result = EightVec3I();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x2);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y2);
    __m256i z1z2 = _mm256_mullo_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline EightVec3I &EightVec3I::operator*=(const EightVec3I &nVec2) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nVec2._z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x2);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y2);
    __m256i z1z2 = _mm256_mullo_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i *>(_z.data()), z1z2);

    return *this;
}

#ifdef _mm256_div_epi32

template <>
inline EightVec3I EightVec3I::operator/(const EightVec3I& nVec2) const
{
    EightVec3I result = EightVec3I();

    for (int i = 0; i < 8; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._z.data()));

    __m256i x1x2 = _mm256_div_epi32(x1, x2);
    __m256i y1y2 = _mm256_div_epi32(y1, y2);
    __m256i z1z2 = _mm256_div_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._z.data()), z1z2);

    return result;
}

template <>
inline EightVec3I& EightVec3I::operator/=(const EightVec3I& nVec2)
{
    for (int i = 0; i < 8; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nVec2._z.data()));

    __m256i x1x2 = _mm256_div_epi32(x1, x2);
    __m256i y1y2 = _mm256_div_epi32(y1, y2);
    __m256i z1z2 = _mm256_div_epi32(z1, z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_x.data()), x1x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_y.data()), y1y2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_z.data()), z1z2);

    return *this;
}

#endif

template<>
inline std::array<int, 8> EightVec3I::Dot(const NVec3<int, 8> &nV1, const NVec3<int, 8> &nV2) noexcept
{
    std::array<int, 8> result = std::array<int, 8>();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV1._x.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV2._x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV1._y.data()));
    __m256i y2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV2._y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV1._z.data()));
    __m256i z2 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(nV2._z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x2);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y2);
    __m256i z1z2 = _mm256_mullo_epi32(z1, z2);

    __m256i resultPartial = _mm256_add_epi32(x1x2, y1y2);
    resultPartial = _mm256_add_epi32(resultPartial, z1z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result.data()), resultPartial);

    return result;
}

template<>
inline std::array<int, 8> EightVec3I::SquareMagnitude() const noexcept
{
    std::array<int, 8> result = std::array<int, 8>();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(_z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x1);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y1);
    __m256i z1z2 = _mm256_mullo_epi32(z1, z1);

    __m256i resultPartial = _mm256_add_epi32(x1x2, y1y2);
    resultPartial = _mm256_add_epi32(resultPartial, z1z2);

    _mm256_storeu_si256(reinterpret_cast<__m256i *>(result.data()), resultPartial);

    return result;
}

#ifdef _mm256_sqrt_epi32

template <>
inline std::array<int, 8> EightVec3I::Magnitude() const noexcept
{
    std::array<int, 8> result = std::array<int, 8>();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x1);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y1);
    __m256i z1z2 = _mm256_mullo_epi32(z1, z1);

    __m256i resultPartial = _mm256_add_epi32(x1x2, y1y2);
    resultPartial = _mm256_add_epi32(resultPartial, z1z2);

    __m256i resultSqrt = _mm256_sqrt_epi32(resultPartial);

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result.data()), resultSqrt);

    return result;
}

template <>
inline std::array<int, 8> EightVec3I::Normalized() const
{
    std::array<int, 8> result = std::array<int, 8>();

    // Check if magnitude is 0.
    const auto magnitude = Magnitude();

    for (int i = 0; i < 8; i++)
    {
        if (magnitude[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_x.data()));
    __m256i y1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_y.data()));
    __m256i z1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_z.data()));

    __m256i x1x2 = _mm256_mullo_epi32(x1, x1);
    __m256i y1y2 = _mm256_mullo_epi32(y1, y1);
    __m256i z1z2 = _mm256_mullo_epi32(y1, y1);

    __m256i resultPartial = _mm256_add_epi32(x1x2, y1y2);
    resultPartial = _mm256_add_epi32(resultPartial, z1z2);

    __m256i resultSqrt = _mm256_sqrt_epi32(resultPartial);

    __m256i resultSqrtReciprocal = _mm256_rcp_epi32(resultSqrt);

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result.data()), resultSqrtReciprocal);

    return result;
}

#endif

#pragma endregion

#pragma region FourVec3I

template<>
inline FourVec3I FourVec3I::operator+(const FourVec3I &nVec2) const noexcept
{
    FourVec3I result = FourVec3I();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_add_epi32(x1, x2);
    __m128i y1y2 = _mm_add_epi32(y1, y2);
    __m128i z1z2 = _mm_add_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline FourVec3I &FourVec3I::operator+=(const FourVec3I &nVec2) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_add_epi32(x1, x2);
    __m128i y1y2 = _mm_add_epi32(y1, y2);
    __m128i z1z2 = _mm_add_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(_x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_z.data()), z1z2);

    return *this;
}

template<>
inline FourVec3I FourVec3I::operator-() const noexcept
{
    FourVec3I result = FourVec3I();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));

    __m128i x1x2 = _mm_sub_epi32(_mm_setzero_si128(), x1);
    __m128i y1y2 = _mm_sub_epi32(_mm_setzero_si128(), y1);
    __m128i z1z2 = _mm_sub_epi32(_mm_setzero_si128(), z1);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline FourVec3I FourVec3I::operator-(const FourVec3I &nVec2) const noexcept
{
    FourVec3I result = FourVec3I();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_sub_epi32(x1, x2);
    __m128i y1y2 = _mm_sub_epi32(y1, y2);
    __m128i z1z2 = _mm_sub_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline FourVec3I &FourVec3I::operator-=(const FourVec3I &nVec2) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_sub_epi32(x1, x2);
    __m128i y1y2 = _mm_sub_epi32(y1, y2);
    __m128i z1z2 = _mm_sub_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(_x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_z.data()), z1z2);

    return *this;
}

template<>
inline FourVec3I FourVec3I::operator*(const FourVec3I &nVec2) const noexcept
{
    FourVec3I result = FourVec3I();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x2);
    __m128i y1y2 = _mm_mullo_epi32(y1, y2);
    __m128i z1z2 = _mm_mullo_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(result._z.data()), z1z2);

    return result;
}

template<>
inline FourVec3I &FourVec3I::operator*=(const FourVec3I &nVec2) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nVec2._z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x2);
    __m128i y1y2 = _mm_mullo_epi32(y1, y2);
    __m128i z1z2 = _mm_mullo_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(_x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(_z.data()), z1z2);

    return *this;
}

#ifdef _mm_div_epi32

template <>
inline FourVec3I FourVec3I::operator/(const FourVec3I& nVec2) const
{
    FourVec3I result = FourVec3I();

    for (int i = 0; i < 4; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._z.data()));

    __m128i x1x2 = _mm_div_epi32(x1, x2);
    __m128i y1y2 = _mm_div_epi32(y1, y2);
    __m128i z1z2 = _mm_div_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._z.data()), z1z2);

    return result;
}

template <>
inline FourVec3I& FourVec3I::operator/=(const FourVec3I& nVec2)
{
    for (int i = 0; i < 4; i++)
    {
        if (nVec2._x[i] == 0 || nVec2._y[i] == 0 || nVec2._z[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nVec2._z.data()));

    __m128i x1x2 = _mm_div_epi32(x1, x2);
    __m128i y1y2 = _mm_div_epi32(y1, y2);
    __m128i z1z2 = _mm_div_epi32(z1, z2);

    _mm_storeu_si128(reinterpret_cast<__m128i*>(_x.data()), x1x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(_y.data()), y1y2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(_z.data()), z1z2);

    return *this;
}

#endif

template<>
inline std::array<int, 4> FourVec3I::Dot(const NVec3<int, 4> &nV1, const NVec3<int, 4> &nV2) noexcept
{
    std::array<int, 4> result = std::array<int, 4>();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV1._x.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV2._x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV1._y.data()));
    __m128i y2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV2._y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV1._z.data()));
    __m128i z2 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(nV2._z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x2);
    __m128i y1y2 = _mm_mullo_epi32(y1, y2);
    __m128i z1z2 = _mm_mullo_epi32(z1, z2);

    __m128i resultPartial = _mm_add_epi32(x1x2, y1y2);
    resultPartial = _mm_add_epi32(resultPartial, z1z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result.data()), resultPartial);

    return result;
}

template<>
inline std::array<int, 4> FourVec3I::SquareMagnitude() const noexcept
{
    std::array<int, 4> result = std::array<int, 4>();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i *>(_z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x1);
    __m128i y1y2 = _mm_mullo_epi32(y1, y1);
    __m128i z1z2 = _mm_mullo_epi32(z1, z1);

    __m128i resultPartial = _mm_add_epi32(x1x2, y1y2);
    resultPartial = _mm_add_epi32(resultPartial, z1z2);

    _mm_storeu_si128(reinterpret_cast<__m128i *>(result.data()), resultPartial);

    return result;
}

#ifdef _mm_sqrt_epi32

template <>
inline std::array<int, 4> FourVec3I::Magnitude() const noexcept
{
    std::array<int, 4> result = std::array<int, 4>();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x1);
    __m128i y1y2 = _mm_mullo_epi32(y1, y1);
    __m128i z1z2 = _mm_mullo_epi32(z1, z1);

    __m128i resultPartial = _mm_add_epi32(x1x2, y1y2);
    resultPartial = _mm_add_epi32(resultPartial, z1z2);

    __m128i resultSqrt = _mm_sqrt_epi32(resultPartial);

    _mm_storeu_si128(reinterpret_cast<__m128i*>(result.data()), resultSqrt);

    return result;
}

template <>
inline std::array<int, 4> FourVec3I::Normalized() const
{
    std::array<int, 4> result = std::array<int, 4>();

    // Check if magnitude is 0.
    const auto magnitude = Magnitude();

    for (int i = 0; i < 4; i++)
    {
        if (magnitude[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_x.data()));
    __m128i y1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_y.data()));
    __m128i z1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_z.data()));

    __m128i x1x2 = _mm_mullo_epi32(x1, x1);
    __m128i y1y2 = _mm_mullo_epi32(y1, y1);
    __m128i z1z2 = _mm_mullo_epi32(y1, y1);

    __m128i resultPartial = _mm_add_epi32(x1x2, y1y2);
    resultPartial = _mm_add_epi32(resultPartial, z1z2);

    __m128i resultSqrt = _mm_sqrt_epi32(resultPartial);

    __m128i resultSqrtReciprocal = _mm_rcp_epi32(resultSqrt);

    _mm_storeu_si128(reinterpret_cast<__m128i*>(result.data()), resultSqrtReciprocal);

    return result;
}

#endif

#pragma endregion
