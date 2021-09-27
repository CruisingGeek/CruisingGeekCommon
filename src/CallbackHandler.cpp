/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

#include "CallbackHandler.h"

CallbackHandler::CallbackHandler()
    : _isRegistered(false)
{
}

int8_t CallbackHandler::RegisterCallback(void(*callback)(void *arg))
{
    if (this->_isRegistered) { return CallbackHandler_UnableToRegister; }

    this->_callback = callback;
    this->_isRegistered = true;

    return 1;
}

void CallbackHandler::UnregisterCallback()
{
    this->_isRegistered = false;
    this->_callback = nullptr;
}

void CallbackHandler::FireCallback(void *arg)
{
    if (!this->_isRegistered) { return; }
    this->_callback(arg);
}
