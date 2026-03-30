/**************************************************************************************
 * Copyright Cruising Geek 2021. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    ICallbackHandler.h
  * 
  * @author  Scott DeBoer of Cruising Geek
  * 
  * @brief   Define methods for generic method callback.
  * 
  *          Interface for registering and calling back different functions when a
  *          specific event occurs. Generally a class will implement this interface,
  *          and will hold a private instance of a Callback class.
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
