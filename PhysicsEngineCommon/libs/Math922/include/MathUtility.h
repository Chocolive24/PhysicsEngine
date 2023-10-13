#pragma once
/**
 * @headerfile A collection of useful math constants and functions.
 * @author Alexis, Olivier, Constantin, Remy
 */

#include "Angle.h"
#include "lookupTables/LookUpTableSin.h"
#include "lookupTables/LookUpTableCos.h"
#include "lookupTables/LookUpTableCot.h"
#include "lookupTables/LookUpTableTan.h"


namespace MathUtility
{
    constexpr static float Pi = 3.14159265358979323846f;
    constexpr static float Epsilon = 0.001f;

    constexpr static int const CosIterNbr = 5;

    constexpr static const float TanMargin = 0.001f;
    // Value to be withdrawn from the start and the end of the range, because tan isn't precise for values
    // too far from zero.
    constexpr static const int TanTestErrorMargin = 10;
    constexpr static const float TanRangeStart = -Pi / 2.f + TanMargin;
    constexpr static const float TanRangeEnd = Pi / 2.f - TanMargin;
    constexpr static const double CotRangeStart = 0 + TanMargin;
    constexpr static const double CotRangeEnd = Pi - TanMargin;
    constexpr static const double CotStepSize = (CotRangeEnd - CotRangeStart)/CotTableSize;

    template <typename T>
    [[nodiscard]] constexpr T Abs(T nbr) noexcept
    {
        return nbr < 0 ? -nbr : nbr;
    }

    template <typename T>
    [[nodiscard]] constexpr T Clamp(T x, T min, T max) noexcept
    {
        if (min > max)
        {
            T tmp = min;
            min = max;
            max = tmp;
        }

        if (x < min)
        {
            x = min;
        }
        else if (x > max)
        {
            x = max;
        }

        return x;
    }

    template <typename T>
    [[nodiscard]] constexpr T Min(const T x, const T y) noexcept
    {
        return x < y ? x : y;
    }

    template <typename T>
    [[nodiscard]] constexpr T Max(const T x, const T y) noexcept
    {
        return x > y ? x : y;
    }

    template<typename T>
    [[nodiscard]] constexpr T Fact(const T n) noexcept
    {
        T result = 1;

        for (int i = 2; i <= Abs(n); i++)
        {
            result *= i;
        }

        if (n < 0)
        {
            result = -result;
        }

        return result;
    }

    template<typename T>
    [[nodiscard]] constexpr T Pow(const T x, const unsigned int power)
    {
        if (x == 0)
        {
            return 0;
        }

        T result = 1;

        for (int i = 1; i <= power; i++)
        {
            result *= x;
        }

        return result;
    }

    [[nodiscard]] constexpr float Sin(const Radian radian) noexcept
    {
        const auto radianValue = static_cast<float>(radian);
        const int index = static_cast<int>(radianValue / SinStep);

        if (index == SinSize -1) return SinTable[index];

        const float indexValue = SinTable[index];
        const float nextValue = SinTable[index + 1];
        const float ratio = (radianValue - index * SinStep) / SinStep;

        return indexValue + (nextValue - indexValue) * ratio;
    }

    [[nodiscard]] constexpr float Cos(const Radian radian) noexcept
    {
        const auto radianValue = static_cast<float>(radian);
        const int index = static_cast<int>(radianValue / CosStep);

        if (index == CosSize -1) return CosTable[index];

        const float indexValue = CosTable[index];
        const float nextValue = CosTable[index + 1];
        const float ratio = (radianValue - index * CosStep) / CosStep;

        return indexValue + (nextValue - indexValue) * ratio;
    }

    /**
     * @brief Get tangent value of an angle inside the LookUpTableTan.
     * @note Angle values in the degree range [-55, 55] are accurate to 5 decimal places.
     * Then the precision is lower and lower down to -90 and 90 degrees, which are indeterminate
     * @param radian The angle in radian.
     * @return An approximate value of the tangent function.
     */
    [[nodiscard]] constexpr float Tan(const Radian radian) noexcept
    {
        const auto radianValue = static_cast<float>(radian);

        const int index = MathUtility::Abs(
                static_cast<int>((static_cast<float>(radianValue) - TanRangeStart) / TanStep));

        if (index == TanSize -1) return table[index];

        const float indexValue = table[index];
        const float nextValue  = table[index + 1];

        const float ratio = (static_cast<float>(radianValue) -
                (TanRangeStart + static_cast<float>(index) * TanStep)) / TanStep;

        return indexValue + (nextValue - indexValue) * ratio;
    }

    [[nodiscard]] constexpr double CosTaylor(const double x) noexcept
    {
        double result = 0.0;
        int sign = 1;

        for (int n = 0; n <= CosIterNbr; n++)
        {
            const auto powX = MathUtility::Pow<double>(x, 2 * n);
            const auto fact = MathUtility::Fact<double>(2 * n);

            result += sign * powX / fact;
            sign = -sign;
        }
        return result;
    }

    [[nodiscard]] constexpr float CotLut(const Radian angle) noexcept
    {
        const int index = static_cast<int>((static_cast<float>(angle) - CotRangeStart) / CotStepSize);
        const double indexValue = CotTable[index];
        const double nextValue  = CotTable[index + 1];

        const double ratio = (static_cast<float>(angle) - (CotRangeStart + index * CotStepSize)) / CotStepSize;
        return indexValue + (nextValue - indexValue) * ratio;
    }


    constexpr int const taylorSeriesIterationNbr = 25;
    [[nodiscard]] constexpr float Cot(const Radian angle) noexcept
    {
        double resultSin = 0;
        double resultCos = 0;

        int sign = 1;
        for (int n = 0; n <= taylorSeriesIterationNbr; n++)
        {
            auto powXSin = MathUtility::Pow<double>(static_cast<float>(angle), 2 * n + 1);
            auto factorialSin = MathUtility::Fact<double>(2 * n + 1);
            resultSin += sign / factorialSin * powXSin;

            auto powXCos = MathUtility::Pow<double>(static_cast<float>(angle), 2 * n);
            auto factorialCos = MathUtility::Fact<double>(2 * n);
            resultCos += sign / factorialCos * powXCos;
            sign = -sign;
        }
        return resultCos/resultSin;
    }
}