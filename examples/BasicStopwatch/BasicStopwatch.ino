/**************************************************************************************
 * Copyright Cruising Geek 2021. All rights reserved.
 **************************************************************************************/

 /*
  * Demonstrates using a stopwatch to send serial information at specified timing.
  *
  * All examples are setup for an Arduino Uno R3 board - others should work with minimal
  * changes.
  */

#include "Arduino.h"

#include <Button.h>
#include <Stopwatch.h>

// ------------------------------------------------------------------------------------
// Pin Setup
// ------------------------------------------------------------------------------------

const uint8_t buttonPin = 7;

// ------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------
// Variables
// ------------------------------------------------------------------------------------

#define BUTTON_HELD_MS 500
#define USE_PULLUP true
Button button(
    buttonPin,
    ButtonType::Momentary,
    ButtonPolarity::ActiveLow,
    BUTTON_HELD_MS,
    USE_PULLUP);

Stopwatch stopWatch;

// ------------------------------------------------------------------------------------


void setup()
{
    Serial.begin(115200);

    //
    // Make sure to start the stopwatch in your setup.
    //
    // It is also possible to stop/start in the loop based on desired conditions.
    //
    stopWatch.Start();
}

void loop()
{
    // First always make a call to update the stopwatch at the beginning of the loop.
    stopWatch.Update();

    // Now the stopwatch can be checked to see if the desired time has elapsed.
    if (stopWatch.HasElapsed(1000))
    {
        Serial.println("1000ms loop execution has passed");

        // Generally you want to reset the stopwatch after handling the timed action;
        // otherwise HasElapsed will continue to return true for this duration.
        //
        stopWatch.Reset();
    }

    ButtonState buttonState = button.DetermineButtonState();

    if (buttonState == ButtonState::LongPress)
    {
        Serial.print("Button was held for ");
        Serial.print(BUTTON_HELD_MS);
        Serial.println("ms.");
    }
    else if (buttonState == ButtonState::ShortPress)
    {
        Serial.println("Button was quickly pressed");
    }
}
