/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

#include "Button.h"

#define DetermineButtonStateMomentary m1
#define DetermineButtonStateLatching m2

#define _targetMillis _u32_1
#define _pinName _u32_2
#define _onState _u32_3
#define _heldMS _u32_4
#define _cooloffTarget _u32_5

#define _buttonId _u8_1

#define _isLongPressHandled _b_1
#define _isCooloff _b_2


namespace ButtonHelpers
{
    uint8_t globalButtonId = 0;
}

Button::Button(uint32_t pin, ButtonType bType, ButtonPolarity bPolarity, uint32_t heldMS)
    : _buttonType(bType)
    , _buttonState(ButtonState::NotPressed)
    , _buttonPolarity(bPolarity)
    , _pinName(pin)
    , _isLongPressHandled(false)
    , _isCooloff(false)
    , _heldMS(heldMS)
{
    pinMode(pin, INPUT);
    _buttonId = ButtonHelpers::globalButtonId++;
}

uint8_t Button::Id() const
{
    return _buttonId;
}

bool Button::IsPressed() const
{
#ifdef USE_DIGITAL_READ_LIB
    int val = digitalReadEx(_pinName);
#else
    int val = digitalRead(_pinName);
#endif
    return _buttonPolarity == ButtonPolarity::ActiveLow
        ? val == LOW
        : val == HIGH;
}

void Button::UpdateButtonProperties(ButtonType bType, ButtonPolarity bPolarity, uint32_t heldMS)
{
    _buttonType = bType;
    _buttonPolarity = bPolarity;
    _heldMS = heldMS;
}

ButtonState Button::DetermineButtonState()
{
    if (_buttonType == ButtonType::Momentary)
    {
        return DetermineButtonStateMomentary(_heldMS);
    }
    else
    {
        return DetermineButtonStateLatching(_heldMS);
    }
}

ButtonState Button::DetermineButtonStateMomentary(uint32_t heldMS)
{
    ButtonState result = ButtonState::NotPressed;

    if (_isCooloff && millis() < _cooloffTarget)
    {
        // Force not pressed when cooling off from held
        return ButtonState::NotPressed;
    }
    else if (_isCooloff)
    {
        _isCooloff = false;
    }

    if (IsPressed()
        && !_isLongPressHandled
        && _buttonState == ButtonState::Pressed
        && millis() >= _targetMillis)
    {
        // Can safely assume the long press since it was over the elapsed time.
        result = ButtonState::LongPress;
        _isLongPressHandled = true;
        _buttonState = ButtonState::NotPressed;
    }
    else if (!IsPressed()
        && _buttonState == ButtonState::Pressed)
    {
        // If we see it's not pressed and the held test didn't pass above, the use let go before the held length. Thus,
        // it is safe to call it a short press.
        result = ButtonState::ShortPress;
        _buttonState = ButtonState::NotPressed;
    }
    else if (IsPressed() && !_isLongPressHandled)
    {
        // We don't know if they will let go before the held time, so just mark that we are pressed.
        _targetMillis = _buttonState == ButtonState::Pressed ? _targetMillis : millis() + heldMS;
        _buttonState = ButtonState::Pressed;
    }
    else if (!IsPressed())
    {
        // Not being pressed at all so just clear everything.
        _isCooloff = _isLongPressHandled;
        result = _isLongPressHandled ? ButtonState::Released : ButtonState::NotPressed;
        _isLongPressHandled = false;
        // Set this even if it isn't needed to avoid if statement.
        _cooloffTarget = millis() + 100;
    }

    return result;
}

ButtonState Button::DetermineButtonStateLatching(uint32_t heldMS)
{
    ButtonState result = ButtonState::NotPressed;

    bool isPressed = IsPressed();
    if (_buttonState == ButtonState::NotPressed
        && isPressed)
    {
        result = ButtonState::Pressed;
        _buttonState = ButtonState::Pressed;
    }
    else if (!isPressed)
    {
        _buttonState = ButtonState::NotPressed;
    }

    return result;
}
