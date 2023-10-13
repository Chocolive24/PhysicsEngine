#include "Timer.h"

#include "gtest/gtest.h"

#include <chrono>

TEST(Timer, TotalTime)
{
    Timer::Init();

    auto startTime = std::chrono::high_resolution_clock::now();
    float totalTime;

    float expectedTime = 2.f;
    float epsilon = 0.00001f;

    while(true)
    {
         totalTime = std::chrono::duration_cast<std::chrono::duration<float>>(
                std::chrono::high_resolution_clock::now() - startTime).count();

        if (std::abs(totalTime - expectedTime) < epsilon)
        {
            break;
        }
    }

    EXPECT_NEAR(Timer::TotalTime(), totalTime, epsilon);
}