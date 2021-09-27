/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2021. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    MathUtils.h
  * @author  Naigon's Electronic Creations
  * @brief   MathUtils
  *          Math functionality wrappers
  *************************************************************************************
**/

#ifndef __MathUtils_H_
#define __MathUtils_H_

#include "Arduino.h"

#define minimum(a, b) (a) < (b) ? a : b
#define maximum(a, b) (a) > (b) ? a : b

extern "C"
{
    /**
     * @brief   Returns the random value between two integers. It does not matter which
     *          order the values are passed in.
     * 
     * @param   a
     *          One of the two bounds.
     * 
     * @param   b
     *          The other bounds.
     * 
     * @return  Random interger that is inclusively between a and b.
     **/
    int32_t randomBetween(int32_t a, int32_t b);

    /**
     * @brief   Returns a random value between [0, 1].
     **/
    float randomPercent();
}

#endif  //__MathUtils_H_
