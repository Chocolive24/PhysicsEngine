/**
 * @headerfile Timer namespace using chrono standard library.
 * @author Olivier
 */

#pragma once

#include <chrono>

namespace Timer
{
    /**
    * @return Delta time in seconds.
    */
    [[nodiscard]] float DeltaTime() noexcept;

    /**
    * @return Time since Init() function was called in seconds.
    */
    [[nodiscard]] float TotalTime() noexcept;

    void Init() noexcept;
    void Tick() noexcept;
};