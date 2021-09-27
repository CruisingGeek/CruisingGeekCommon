/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    Stopwatch.h
  * @author  Naigon's Electronic Creations
  * @brief   Stopwatch class for inline time monitoring. Does not use timer hardware.
  *          Good for low-priority monitoring such as determining if a button was held
  *          for a certain duration.
  *
  *************************************************************************************
**/

#ifndef __Stopwatch_H_
#define __Stopwatch_H_

#include "Arduino.h"


class Stopwatch
{
  public:
    Stopwatch();

    void Start();

    void Stop();

    void Reset();

    void Update();

    bool HasElapsed(uint32_t targetMS) const;
    bool HasElapsedMicros(uint32_t targetMicros) const;

    uint32_t ElapsedTime() const;
    uint32_t ElapsedTimeMicros() const;

  private:
    uint32_t _elapsedTime;
    uint32_t _elapsedMicros;
    uint32_t _lastCheckedTime;
    uint32_t _lastCheckedMicros;
    bool _isPaused;
};

#endif //__Stopwatch_H_
