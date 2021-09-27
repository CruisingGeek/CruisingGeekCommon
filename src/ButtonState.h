/*************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 *************************************************************************************/

/**
  *************************************************************************************
  * @file    ButtonState.h
  * @author  Naigon's Electronic Creations
  * @brief   ButtonState enum
  *          Defines all the possible states in which a button can be in.
  *
  *************************************************************************************
**/

#ifndef __ButtonState_H_
#define __ButtonState_H_

enum ButtonState
{
    // This state means the button is not pressed.
    NotPressed = 0,

    // This state means the button is pressed, however it cannot be determined or it is
    // not important if the button is going to be released as a long or short press.
    Pressed,

    // This means the button was pressed and released less than the time deemed to be
    // the long length. The button is definitely released to get into this state.
    ShortPress,

    // This means the button is held for at least the length defined as the long press
    // time. The button could still be held or it could be released.
    LongPress,

    // This state indicates that a button went from held to released within the previous
    // cycle.
    Released,
};

enum ButtonType
{
    // Momentary button is the default state. Assumed NO type. Allows for both a short
    // and long press states.
    Momentary = 0,

    // Latching button. Assumed NO type. Only allows pressed and not pressed states.
    Latching = 1,
};

enum ButtonPolarity
{
    ActiveLow = 0,
    ActiveHigh = 1,
};

#endif //__ButtonState_H_
