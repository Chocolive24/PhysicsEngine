//
// Created by Olivier on 27.10.2023.
//

#include "SampleManager.h"
#include "PlanetSystemSample.h"
#include "TriggerColliderSample.h"

void SampleManager::Init() noexcept
{
    _samples[0] = UniquePtr<Sample>(new PlanetSystemSample);
    _samples[1] = UniquePtr<Sample>(new TriggerColliderSample);

    _samples[_currentSampleIdx]->Init();
}

void SampleManager::HandleInputs(SDL_Event event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.scancode)
            {
                case SDL_SCANCODE_1:
                    _samples[_currentSampleIdx]->Deinit();
                    _currentSampleIdx = static_cast<int>(SampleType::PlanetSystem);
                    _samples[_currentSampleIdx]->Init();
                    break;
                case SDL_SCANCODE_2:
                    _samples[_currentSampleIdx]->Deinit();
                    _currentSampleIdx = static_cast<int>(SampleType::Trigger);
                    _samples[_currentSampleIdx]->Init();
                    break;
                default:
                    break;
            } // Switch key.keysym.scancode.
        } //  Case Key down.
    } // Switch event type.

    _samples[_currentSampleIdx]->HandleInputs(event);
}

void SampleManager::Update() const noexcept
{
    _samples[_currentSampleIdx]->Update();
}