//
// Created by Olivier on 19.10.2023.
//

#include "Sample.h"

void Sample::Init() noexcept
{
    _world.Init(_startBodyCount);
    _timer.Init();
}

void Sample::Deinit() noexcept
{
    _world.Deinit();
}
