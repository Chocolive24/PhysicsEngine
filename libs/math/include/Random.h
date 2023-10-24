#pragma once

/**
* @headerfile Random number generator functions and classes
* @author Alexis
*/

#include <random>

/**
 * @brief A namespace for random number generator functions and classes
 */
namespace Math::Random
{
    template <class T>
    [[nodiscard]] T Range(T min, T max) noexcept
    {
        if (min > max)
        {
            T temp = min;
            min = max;
            max = temp;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(min, max);

        return dis(gen);
    }

    template <>
    [[nodiscard]] int Range(int min, int max) noexcept;

    template <>
    [[nodiscard]] unsigned int Range(unsigned int min, unsigned int max) noexcept;

    template <>
    [[nodiscard]] long Range(long min, long max) noexcept;
}