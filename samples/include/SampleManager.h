#pragma once

#include "Sample.h"
#include "UniquePtr.h"

#include "SDL.h"

#include <vector>

class SampleManager
{
public:
    static constexpr int SampleCount = 4;

    void Init() noexcept;
    void HandleCurrentSampleInputs(SDL_Event event, bool isMouseOnAnImGuiWindow) const noexcept;
    void UpdateCurrentSample() const noexcept;
    void RenderCurrentSample() const noexcept;

    void RestartSample() noexcept;
    void ChangeSample(int index) noexcept;

    constexpr int CurrentSampleIdx() const noexcept { return _currentSampleIdx; }
    const Sample* CurrentSample() const noexcept { return _samples[_currentSampleIdx].Get(); }
    const Sample* GetSampleAtIndex(int index) const noexcept { return _samples[index].Get(); }

private:
    HeapAllocator _heapAllocator;
    std::array<UniquePtr<Sample>, SampleCount> _samples;

    int _currentSampleIdx = 0;
};
