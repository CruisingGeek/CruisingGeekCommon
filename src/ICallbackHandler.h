/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    ICallbackHandler.h
  * @author  Naigon's Electronic Creations
  * @brief   ICallbackHandler
  *          Interface for registering and calling a single user-defined callback. IE
  *          a limited observable pattern, where only one method can be registered,
  *          and a pointer to only one parameter can be sent.
  *************************************************************************************
**/

#ifndef __ICallbackHandler_H_
#define __ICallbackHandler_H_

#define CallbackHandler_UnableToRegister -1

struct ICallbackHandler
{
    /**
     * @brief   Register the callback to this instance. If a callback is already
     *          registered, it will be a no-op.
     *
     * @param   callback
     *          Pointer to the callback function, which takes the form:
     *          void callback(void *arg)
     *
     *          This will need to be a C-style function since C++ requires special
     *          method designations to callback class methods, and in a small-scale
     *          environment that is too heavy weight.
     *
     *          The argument 'arg' is a void pointer, but it is upto the callback's
     *          implementation to cast to the appropriate type.
     *
     * @return  Valid token to use for unregister if successful; otherwise
     *          CallbackHandler_UnableToRegister.
     **/
    virtual int8_t RegisterCallback(void(*callback)(void *arg)) = 0;

    /**
     * @summary Unregister the callback so that it will no-longer be called by the
     *          system.
     **/
    virtual void UnregisterCallback() = 0;
};

#endif //__ICallbackHandler_H_
