/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file   Button.h
  * @author Naigon's Electronic Creations
  * @brief  Button
  *         Class for managing input from a single button.
  * 
  *         NOTE: A system is limited to 256 active buttons for its entire lifetime.
  * 
  *         NOTE: It is expected that each button will be created as a global
  *         variable and last the duration of the application. This ensures that each
  *         button retains a single unique Id for the entire life of the program, and
  *         prevents the system from running out of ids even when there are less than
  *         256 active buttons.
  *************************************************************************************
**/

#ifndef __Button_H_
#define __Button_H_

#include "Arduino.h"
#include "ButtonState.h"

class Button
{
  public:
    /**
     * @brief   Constructs a new instance of the Button class.
     *
     * @param   pin
     *          Digital pin to associate as an input with this button. Should be a
     *          valid value from the unnamed enum in variants.h file.
     *          IE PA9, PB9
     *
     *          For OneFX, defined constants SW1 and SW2 can be used, which map
     *          to the two switch pads on the board.
     *
     * @param   bType
     *          Defines what type of button is attached.
     *
     * @param   bPolarity
     *          Defines if the button is considered pressed when it sees low or high.
     *
     * @param   heldMS
     *          Length in milliseconds that is considered to be the held state vs short
     *          press.
     **/
    Button(uint32_t pin, ButtonType bType, ButtonPolarity bPolarity, uint32_t heldMS);

    /**
     * @brief   Updates the button properties for the specified button.
     *
     * @param   bType
     *          Defines what type of button is attached.
     *
     * @param   bPolarity
     *          Defines if the button is considered pressed when it sees low or high.
     *
     * @param   heldMS
     *          Length in milliseconds that is considered to be the held state vs short
     *          press.
     **/
    void UpdateButtonProperties(
        ButtonType bType,
        ButtonPolarity bPolarity,
        uint32_t heldMS);

    /**
     * @summary Determine the current button state. This method is ensured to return
     *          the state exactly once; subsequent reads after the first with a result
     *          will return NotPressed. This ensures that a new action will not be
     *          observed until the user releases the button.
     *
     *          In order for this method to work appropriately, it must be called in
     *          a periodic fashion, ie ever 10ms.
     *
     * @return  Pressed if the user released the button less than the specified length;
     *          Held if the button was held and released or still being held and the
     *          time it was held was longer than heldMS;
     *          otherwise, NotPressed.
     **/
    ButtonState DetermineButtonState();

    /**
     * @brief   Simple indication of whether this button is being pressed or not.
     *
     * @return  True if the button is depressed or latched; otherwise false.
     **/
    bool IsPressed() const;

    /**
     * @brief   Get the unique id assigned to this button.
     *
     * @return  Unique Id for this button.
     **/
    uint8_t Id() const;

  private:
    ButtonState m1(uint32_t);
    ButtonState m2(uint32_t);

    ButtonType _buttonType;
    ButtonState _buttonState;
    ButtonPolarity _buttonPolarity;
    uint8_t _u8_1;
    uint32_t _u32_1, _u32_2, _u32_3, _u32_4, _u32_5;
    bool _b_1, _b_2;
};

#endif //__Button_H_
