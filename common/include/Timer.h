#pragma once

/**
 * @headerfile A Timer class using the <chrono> standard library.
 * @author Olivier
 */

#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> _startTime;
    std::chrono::duration<float> _deltaTime{0.f};

public:
    /**
    * @brief Init is a method that tells the timer to start counting down.
    */
    void Init() noexcept;

    /**
    * @brief Tick is a method that updates the timer to measure the time elapsed between frames.
    */
    void Tick() noexcept;

    /**
    * @brief DeltaTime is a method that calculates the time elapsed between two consecutive frames.
    * @return The time elapsed between two consecutive frames in seconds.
    */
    [[nodiscard]] float DeltaTime() const noexcept;

    /**
    * @brief TotalTime is a method that calculates the time since the Init() function was called.
    * @return The time since the Init() function was called in seconds.
    */
    [[nodiscard]] float TotalTime() const noexcept;
};