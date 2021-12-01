#pragma once

#define smoothingCoefficient_Generic 0.04
#define smoothingCoefficient_Fine 0.004

const int maxBufferSize = 192000;

const double PI = 3.14159265359;
const double TWO_PI = 6.28318530718;

inline float linearInterpolation(float v0, float v1, float t)
{
    return (1 -t) * v0 + t * v1;
}
