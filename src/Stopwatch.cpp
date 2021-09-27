/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

#include "Stopwatch.h"

Stopwatch::Stopwatch()
    : _elapsedTime(0)
    , _elapsedMicros(0)
    , _lastCheckedTime(0)
    , _lastCheckedMicros(0)
    , _isPaused(true)
{
}

// ------------------------------------------------------------------------------------
// Properties
// ------------------------------------------------------------------------------------

bool Stopwatch::HasElapsed(uint32_t targetMS) const
{
    return this->ElapsedTime() >= targetMS;
}

bool Stopwatch::HasElapsedMicros(uint32_t targetMicros) const
{
    return this->ElapsedTimeMicros() >= targetMicros;
}

uint32_t Stopwatch::ElapsedTime() const
{
    return this->_elapsedTime;
}

uint32_t Stopwatch::ElapsedTimeMicros() const
{
    return this->_elapsedMicros;
}

// ------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------
// Public Methods
// ------------------------------------------------------------------------------------

void Stopwatch::Update()
{
    if (this->_isPaused) return;

    this->_elapsedTime += (millis() - this->_lastCheckedTime);
    this->_lastCheckedTime = millis();

    this->_elapsedMicros += (micros() - this->_lastCheckedMicros);
    this->_lastCheckedMicros = micros();
}

void Stopwatch::Start()
{
    this->_isPaused = false;
    this->_lastCheckedTime = millis();
    this->_lastCheckedMicros = micros();
}

void Stopwatch::Stop()
{
    this->_isPaused = true;
}

void Stopwatch::Reset()
{
    this->_elapsedTime = 0;
    this->_elapsedMicros = 0;
    this->Start();
}

// ------------------------------------------------------------------------------------
