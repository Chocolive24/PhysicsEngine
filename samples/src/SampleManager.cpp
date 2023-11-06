//
// Created by Olivier on 27.10.2023.
//

#include "SampleManager.h"
#include "PlanetSystemSample.h"
#include "TriggerColliderSample.h"
#include "CollisionSample.h"

#ifdef TRACY_ENABLE
#include "Tracy.hpp"
#endif // TRACY_ENABLE


void SampleManager::Init() noexcept
{
    _samples[2] = MakeUnique<Sample>(TriggerColliderSample());
    _samples[1] = MakeUnique<Sample>(PlanetSystemSample());
    _samples[0] = MakeUnique<Sample>(CollisionSample());

    _samples[_currentSampleIdx]->Init();
}

void SampleManager::HandleCurrentSampleInputs(const SDL_Event event, const bool isMouseOnAnImGuiWindow) const noexcept
{
    _samples[_currentSampleIdx]->HandleInputs(event, isMouseOnAnImGuiWindow);
}

void SampleManager::UpdateCurrentSample() const noexcept
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif // TRACY_ENABLE

    _samples[_currentSampleIdx]->Update();
}

void SampleManager::RenderCurrentSample() const noexcept
{
#ifdef TRACY_ENABLE
    ZoneScoped;
#endif // TRACY_ENABLE
    _samples[_currentSampleIdx]->Render();
}

void SampleManager::RestartSample() noexcept
{
    _samples[_currentSampleIdx]->Deinit();
    _samples[_currentSampleIdx]->Init();
}

void SampleManager::ChangeSample(const int index) noexcept
{
    _samples[_currentSampleIdx]->Deinit();
    _currentSampleIdx = index;
    _samples[_currentSampleIdx]->Init();
}
