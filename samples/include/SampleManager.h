#pragma once

#include "Sample.h"
#include "UniquePtr.h"

#include "SDL.h"

#include <vector>

class SampleManager
{
private:
    std::array<UniquePtr<Sample>, 2> _samples;
    int _currentSampleIdx = 0;

public:
    void Init() noexcept;
    void HandleInputs(SDL_Event event);
    void Update() const noexcept;
    void Render() const noexcept;
};
