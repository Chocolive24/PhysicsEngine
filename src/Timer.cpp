#include "Timer.h"

namespace Timer
{
    std::chrono::time_point<std::chrono::steady_clock> _startOfProgramTime;
    std::chrono::time_point<std::chrono::steady_clock> _startOfFrameTime;
    std::chrono::time_point<std::chrono::steady_clock> _endOfFrameTime;
    std::chrono::duration<float> _frameTime{0.f};

    void Init() noexcept
    {
        auto nowTime = std::chrono::high_resolution_clock::now();
        _startOfProgramTime = nowTime;
        _startOfFrameTime = nowTime;
    }

    void Tick() noexcept
    {
        _endOfFrameTime = std::chrono::high_resolution_clock::now();

        _frameTime = std::chrono::duration_cast<std::chrono::duration<float>>(
                _endOfFrameTime - _startOfFrameTime);

        _startOfFrameTime = _endOfFrameTime;
    }

    [[nodiscard]] float DeltaTime() noexcept
    {
        return _frameTime.count();
    }

    [[nodiscard]] float TotalTime() noexcept
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(
                std::chrono::high_resolution_clock::now() - _startOfProgramTime).count();
    }
}