//
// Created by remla on 09/10/2023.
//
#pragma once

#include <array>
#include "Intrinsics.h"
#include "Exception.h"


template<typename T, int N>
class NScalar
{
private:
    std::array<T, N> _scalarValue;

public :

    NScalar() = default;
    NScalar(const NScalar<T, N>& scalar) = default;

    constexpr explicit NScalar(const std::array<T, N> scalars) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue[i] = scalars[i];
        }
    }

    constexpr explicit NScalar(const T scalar) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue[i] = scalar;
        }
    }

    NScalar<T, N> operator+(const NScalar<T, N> nScalar) const noexcept
    {
        NScalar<T, N> result = NScalar<T, N>();

        for (int i = 0; i < N; i++)
        {
            result._scalarValue[i] = _scalarValue[i] + nScalar._scalarValue[i];
        }
        return result;
    }

    NScalar<T, N>& operator+=(const NScalar<T, N> nScalar) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue[i] += nScalar._scalarValue[i];
        }

        return *this;
    }

    NScalar<T, N> operator-() const noexcept
    {
        NScalar<T, N> result = NScalar<T, N>();
        for (int i = 0; i < N; i++)
        {
            result._scalarValue[i] = -_scalarValue[i];
        }
        return result;
    }

    NScalar<T, N> operator-(const NScalar<T, N> nScalar) const noexcept
    {
        NScalar<T, N> result = NScalar<T, N>();
        for (int i = 0; i < N; i++)
        {
            result._scalarValue[i] = _scalarValue[i] - nScalar._scalarValue[i];
        }
        return result;
    }

    NScalar<T, N>& operator-=(const NScalar<T, N> nScalar) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue -= nScalar._scalarValue[i];
        }
        return *this;
    }

    NScalar<T, N> operator*(const NScalar<T, N> nScalar) const noexcept
    {
        NScalar<T, N> result = NScalar<T, N>();
        for (int i = 0; i < N; i++)
        {
            result._scalarValue[i] = _scalarValue[i] * nScalar._scalarValue[i];
        }
        return result;
    }

    NScalar<T, N>& operator*=(const NScalar<T, N> nScalar) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue[i] *= nScalar._scalarValue[i];
        }
        return *this;
    }

    NScalar<T, N> operator/(const NScalar<T, N> nScalar) const
    {
        NScalar<T, N> result = NScalar<T, N>();

        for (int i = 0; i < N; i++)
        {
            if (nScalar._scalarValue[i] == 0)
            {
                throw DivisionByZeroException();
            }
            result._scalarValue[i] = _scalarValue[i] / nScalar._scalarValue[i];
        }
        return result;
    }

    NScalar<T, N>& operator/=(const NScalar<T, N> nScalar)
    {
        for (int i = 0; i < N; i++)
        {
            if (nScalar._scalarValue[i] == 0)
            {
                throw DivisionByZeroException();
            }
            _scalarValue[i] /= nScalar._scalarValue[i];
        }

        return *this;
    }

    NScalar<T, N> operator*(const std::array<T, N> array1N) const noexcept
    {
        NScalar<T, N> result = NScalar<T, N>();
        for (int i = 0; i < N; i++)
        {
            result._scalarValue[i] = _scalarValue[i] * array1N[i];
        }
        return result;
    }

    NScalar<T, N>& operator*=(const std::array<T, N> array1N) noexcept
    {
        for (int i = 0; i < N; i++)
        {
            _scalarValue[i] *= array1N[i];
        }
        return *this;
    }

    NScalar<T, N> operator/(const std::array<T, N> array1N) const
    {
        NScalar<T, N> result = NScalar<T, N>();

        for (int i = 0; i < N; i++)
        {
            if (array1N[i] == 0)
            {
                throw DivisionByZeroException();
            }

            result._scalarValue[i] = _scalarValue[i] / array1N[i];
        }
        return result;
    }

    NScalar<T, N>& operator/=(const std::array<T, N> array1N)
    {
        for (int i = 0; i < N; i++)
        {
            if (array1N[i] == 0)
            {
                throw DivisionByZeroException();
            }
            _scalarValue[i] /= array1N[i];
        }
        return *this;
    }

    T operator[](const int index) const
    {
        return  _scalarValue[index];
    }
};

using FourScalarF = NScalar<float, 4>;
using EightScalarF = NScalar<float, 8>;
using FourScalarI = NScalar<int, 4>;
using EightScalarI = NScalar<int, 8>;


template<>
inline EightScalarF EightScalarF::operator+(const EightScalarF nScalar) const noexcept
{
    EightScalarF result = EightScalarF();

    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_add_ps(x1, x2);
    _mm256_storeu_ps(result._scalarValue.data(), x1x2);

    return result;
}

template<>
inline EightScalarF& EightScalarF::operator+=(const EightScalarF nScalar) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_add_ps(x1, x2);
    _mm256_storeu_ps(_scalarValue.data(), x1x2);

    return *this;
}

template<>
inline EightScalarF EightScalarF::operator-() const noexcept
{
    EightScalarF result = EightScalarF();
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x1x2 = _mm256_sub_ps(_mm256_setzero_ps(), x1);
    _mm256_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline EightScalarF EightScalarF::operator-(const EightScalarF nScalar) const noexcept
{
    EightScalarF result = EightScalarF();
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_sub_ps(x1, x2);
    _mm256_storeu_ps(result._scalarValue.data(), x1x2);

    return result;
}


template<>
inline EightScalarF& EightScalarF::operator-=(const EightScalarF nScalar) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_sub_ps(x1, x2);
    _mm256_storeu_ps(_scalarValue.data(), x1x2);
    return *this;
}

template<>
inline EightScalarF EightScalarF::operator*(const EightScalarF nScalar) const noexcept
{
    EightScalarF result = EightScalarF();
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_mul_ps(x1, x2);
    _mm256_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline EightScalarF& EightScalarF::operator*=(const EightScalarF nScalar) noexcept
{
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_mul_ps(x1, x2);
    _mm256_storeu_ps(_scalarValue.data(), x1x2);

    return *this;
}

template<>
inline EightScalarF EightScalarF::operator/(const EightScalarF nScalar) const
{
    EightScalarF result = EightScalarF();

    for (int i = 0; i < 8; i++)
    {
        if (nScalar._scalarValue[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_div_ps(x1, x2);
    _mm256_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline EightScalarF& EightScalarF::operator/=(const EightScalarF nScalar)
{
    for (int i = 0; i < 8; i++)
    {
        if (nScalar._scalarValue[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }
    __m256 x1 = _mm256_loadu_ps(_scalarValue.data());
    __m256 x2 = _mm256_loadu_ps(nScalar._scalarValue.data());
    __m256 x1x2 = _mm256_div_ps(x1, x2);
    _mm256_storeu_ps(_scalarValue.data(), x1x2);

    return *this;
}



template<>
inline FourScalarF FourScalarF::operator+(const FourScalarF nScalar) const noexcept
{
    FourScalarF result = FourScalarF();

    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_add_ps(x1, x2);
    _mm_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline FourScalarF& FourScalarF::operator+=(const FourScalarF nScalar) noexcept
{
    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_add_ps(x1, x2);
    _mm_storeu_ps(_scalarValue.data(), x1x2);
    return *this;
}

template<>
inline FourScalarF FourScalarF::operator-() const noexcept
{
    FourScalarF result = FourScalarF();
    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x1x2 = _mm_sub_ps(_mm_setzero_ps(), x1);
    _mm_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline FourScalarF FourScalarF::operator-(const FourScalarF nScalar) const noexcept
{
    FourScalarF result = FourScalarF();

    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_sub_ps(x1, x2);
    _mm_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline FourScalarF& FourScalarF::operator-=(const FourScalarF nScalar) noexcept
{
    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_sub_ps(x1, x2);
    _mm_storeu_ps(_scalarValue.data(), x1x2);

    return *this;
}

template<>
inline FourScalarF FourScalarF::operator*(const FourScalarF nScalar) const noexcept
{
    FourScalarF result = FourScalarF();

    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_mul_ps(x1, x2);
    _mm_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline FourScalarF& FourScalarF::operator*=(const FourScalarF nScalar) noexcept
{
    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_mul_ps(x1, x2);
    _mm_storeu_ps(_scalarValue.data(), x1x2);
    return *this;
}

template<>
inline FourScalarF FourScalarF::operator/(const FourScalarF nScalar) const
{
    FourScalarF result = FourScalarF();

    for (int i = 0; i < 4; i++)
    {
        if (nScalar._scalarValue[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_div_ps(x1, x2);
    _mm_storeu_ps(result._scalarValue.data(), x1x2);
    return result;
}

template<>
inline FourScalarF& FourScalarF::operator/=(const FourScalarF nScalar)
{
    for (int i = 0; i < 4; i++)
    {
        if (nScalar._scalarValue[i] == 0)
        {
            throw DivisionByZeroException();
        }
    }

    __m128 x1 = _mm_loadu_ps(_scalarValue.data());
    __m128 x2 = _mm_loadu_ps(nScalar._scalarValue.data());
    __m128 x1x2 = _mm_div_ps(x1, x2);
    _mm_storeu_ps(_scalarValue.data(), x1x2);
    return *this;
}

template <>
inline FourScalarI FourScalarI::operator+(const FourScalarI nScalar) const noexcept
{
    FourScalarI result = FourScalarI();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_add_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline FourScalarI& FourScalarI::operator+=(const FourScalarI nScalar) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_add_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(_scalarValue.data()), x1x2);

    return *this;
}

template <>
inline FourScalarI FourScalarI::operator-() const noexcept
{
    FourScalarI result = FourScalarI();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x1x2 = _mm_sub_epi32(_mm_setzero_si128(), x1);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._scalarValue.data()), x1x2);

    return result;
}

template <>
inline FourScalarI FourScalarI::operator-(const FourScalarI nScalar) const noexcept
{
    FourScalarI result = FourScalarI();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_sub_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._scalarValue.data()), x1x2);

    return result;
}

template <>
inline FourScalarI& FourScalarI::operator-=(const FourScalarI nScalar) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_sub_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(_scalarValue.data()), x1x2);
    return *this;
}

template <>
inline FourScalarI FourScalarI::operator*(const FourScalarI nScalar) const noexcept
{
    FourScalarI result = FourScalarI();

    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_mullo_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline FourScalarI& FourScalarI::operator*=(const FourScalarI nScalar) noexcept
{
    __m128i x1 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(_scalarValue.data()));
    __m128i x2 = _mm_loadu_si128(reinterpret_cast<const __m128i*>(nScalar._scalarValue.data()));
    __m128i x1x2 = _mm_mullo_epi32(x1, x2);
    _mm_storeu_si128(reinterpret_cast<__m128i*>(_scalarValue.data()), x1x2);
    return *this;
}


template <>
inline EightScalarI EightScalarI::operator+(const EightScalarI nScalar) const noexcept
{
    EightScalarI result = EightScalarI();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_add_epi32(x1, x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline EightScalarI& EightScalarI::operator+=(const EightScalarI nScalar) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_add_epi32(x1, x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_scalarValue.data()), x1x2);
    return *this;
}

template <>
inline EightScalarI EightScalarI::operator-() const noexcept
{
    EightScalarI result = EightScalarI();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x1x2 = _mm256_sub_epi32(_mm256_setzero_si256(), x1);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline EightScalarI EightScalarI::operator-(const EightScalarI nScalar) const noexcept
{
    EightScalarI result = EightScalarI();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_sub_epi32(x1, x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline EightScalarI& EightScalarI::operator-=(const EightScalarI nScalar) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_sub_epi32(x1, x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_scalarValue.data()), x1x2);
    return *this;
}

template <>
inline EightScalarI EightScalarI::operator*(const EightScalarI nScalar) const noexcept
{
    EightScalarI result = EightScalarI();

    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_mullo_epi32(x1, x2);

    _mm256_storeu_si256(reinterpret_cast<__m256i*>(result._scalarValue.data()), x1x2);
    return result;
}

template <>
inline EightScalarI& EightScalarI::operator*=(const EightScalarI nScalar) noexcept
{
    __m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
    __m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
    __m256i x1x2 = _mm256_mullo_epi32(x1, x2);
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(_scalarValue.data()), x1x2);
    return *this;
}

#ifdef _mm256_div_epi32
template <>
inline EightScalarI EightScalarI::operator/(const EightScalarI nScalar) const
{
	EightScalarI result = EightScalarI();

	for (int i = 0; i < 8; i++)
	{
		if (nScalar._scalarValue[i] == 0)
		{
			throw DivisionByZeroException();
		}
	}

	__m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
	__m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
	__m256i x1x2 = _mm256_div_epi32(x1, x2);
	_mm256_storeu_si256(reinterpret_cast<__m256i*>(result._scalarValue.data()), x1x2);
	return result;
}

template <>
inline EightScalarI& EightScalarI::operator/=(const EightScalarI nScalar)
{
	for (int i = 0; i < 8; i++)
	{
		if (nScalar._scalarValue[i] == 0)
		{
			throw DivisionByZeroException();
		}
	}

	__m256i x1 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(_scalarValue.data()));
	__m256i x2 = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(nScalar._scalarValue.data()));
	__m256i x1x2 = _mm256_div_epi32(x1, x2);
	_mm256_storeu_si256(reinterpret_cast<__m256i*>(_scalarValue.data()), x1x2);
	return *this;
}
#endif