#include "Timer.h"

void Timer::Init() noexcept
{
    auto nowTime = std::chrono::high_resolution_clock::now();
    _startOfProgramTime = nowTime;
    _startOfFrameTime = nowTime;
}

void Timer::Tick() noexcept
{
    _endOfFrameTime = std::chrono::high_resolution_clock::now();

    _frameTime = std::chrono::duration_cast<std::chrono::duration<float>>(
            _endOfFrameTime - _startOfFrameTime);

    _startOfFrameTime = _endOfFrameTime;
}

[[nodiscard]] float Timer::DeltaTime() const noexcept
{
    return _frameTime.count();
}

[[nodiscard]] float Timer::TotalTime() const noexcept
{
    return std::chrono::duration_cast<std::chrono::duration<float>>(
            std::chrono::high_resolution_clock::now() - _startOfProgramTime).count();
}
