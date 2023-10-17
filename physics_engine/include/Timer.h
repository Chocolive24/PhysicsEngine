#pragma once

/**
 * @headerfile Timer class using <chrono> standard library.
 * @author Olivier
 */

#include <chrono>

namespace PhysicsEngine
{
    class Timer
    {
    private:
        std::chrono::time_point<std::chrono::steady_clock> _startOfProgramTime;
        std::chrono::time_point<std::chrono::steady_clock> _startOfFrameTime;
        std::chrono::time_point<std::chrono::steady_clock> _endOfFrameTime;
        std::chrono::duration<float> _frameTime{0.f};

    public:
        /**
        * @brief Init is a method that tells the timer to start counting down.
        */
        void Init() noexcept;

        /**
        * @brief Tick is a method that calculates the time between frames.
        */
        void Tick() noexcept;

        /**
        * @return Time between frames in seconds.
        */
        [[nodiscard]] float DeltaTime() const noexcept;

        /**
        * @return Time since Init() function was called in seconds.
        */
        [[nodiscard]] float TotalTime() const noexcept;
    };
}