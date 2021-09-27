/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    MotionSensor.h
  * @author  Naigon's Electronic Creations
  * @brief   CallbackHandler
  *          Class handles registering and calling a single user-defined callback. In
  *          general, an implemented class with have this class as a private member,
  *          and itself will implement the ICallbackHandler interface, defering to
  *          this class to do the lifting. The FireCallback method will then not be
  *          exposed to the outside class, allowing it control of when to notify
  *          the observer.
  * 
  *          This is basically the observable pattern, but limited to only one observer
  *          and only allowing a pointer to one argument.
  *************************************************************************************
**/

#ifndef __CallbackHandler_H_
#define __CallbackHandler_H_

#include "Arduino.h"
#include "ICallbackHandler.h"

class CallbackHandler : public ICallbackHandler
{
  public:
    CallbackHandler();

    // -------------------------------------------------------------------------------
    // ICallbackHandler methods. See ICallbackHandler.h for method details.
    // -------------------------------------------------------------------------------
    int8_t RegisterCallback(void(*callback)(void *arg));
    void UnregisterCallback();

    /**
     * @brief   Causes the method registered with this instance to be called with the
     *          supplied argument pointer.
     *
     * @param   arg
     *          Pointer to the argument that will be send when it is fired. It is up
     *          to the callback to handle performing a static cast to the known type.
     *
     *          IMPORTANT! When the callback occurs, it should be considered that the
     *          argument passed is short-lived and will not be in memory after the
     *          callback is complete.
     **/
    void FireCallback(void *arg);

  private:
    void(*_callback)(void *arg);
    bool _isRegistered;
};

#endif //__CallbackHandler_H_
