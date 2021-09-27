/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2021. All rights reserved.
 **************************************************************************************/

#include "MathUtils.h"

extern "C"
{
    int32_t randomBetween(int32_t a, int32_t b)
    {
        if (a > b)
        {
            int32_t temp = a;
            a = b;
            b = temp;
        }

        // Now we can assume b is bigger.
        int32_t diff = b - a;

        return (int32_t)(randomPercent() * diff) + a;
    }

    float randomPercent()
    {
        return (float)random(1000) / 1000.0f;
    }
}