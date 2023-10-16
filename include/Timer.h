/**
 * @headerfile Timer namespace using chrono standard library.
 * @author Olivier
 */

#pragma once

#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::steady_clock> _startOfProgramTime;
    std::chrono::time_point<std::chrono::steady_clock> _startOfFrameTime;
    std::chrono::time_point<std::chrono::steady_clock> _endOfFrameTime;
    std::chrono::duration<float> _frameTime{0.f};

public:
    void Init() noexcept;
    void Tick() noexcept;

    /**
    * @return Time between 2 frames in seconds.
    */
    [[nodiscard]] float DeltaTime() const noexcept;

    /**
    * @return Time since Init() function was called in seconds.
    */
    [[nodiscard]] float TotalTime() const noexcept;
};