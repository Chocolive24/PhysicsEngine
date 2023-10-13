#pragma once

/**
* @headerfile Random number generator functions and classes
* @author Alexis Haldy
*/

#include <random>

/**
 * @brief A namespace for random number generator functions and classes
 */
namespace Random
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
    [[nodiscard]] int Range(int min, int max) noexcept
    {
        if (min > max)
        {
            int temp = min;
            min = max;
            max = temp;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dis(min, max);

        return dis(gen);
    }

    template <>
    [[nodiscard]] unsigned int Range(unsigned int min, unsigned int max) noexcept
    {
        if (min > max)
        {
            unsigned int temp = min;
            min = max;
            max = temp;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<unsigned int> dis(min, max);

        return dis(gen);
    }

    template <>
    [[nodiscard]] long Range(long min, long max) noexcept
    {
        if (min > max)
        {
            long temp = min;
            min = max;
            max = temp;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<long> dis(min, max);

        return dis(gen);
    }
}