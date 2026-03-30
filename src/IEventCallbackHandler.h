/**************************************************************************************
 * Copyright Cruising Geek 2021. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    IEventCallbackHandler.h
  * 
  * @author  Scott DeBoer of Cruising Geek
  * 
  * @brief   Define methods for generic method callback.
  * 
  * @details Interface for registering and calling back different functions when a
  *          specific event occurs. Generally a class will implement this interface,
  *          and will hold a private instance of a Callback class.
  * 
  *          This version supports an EventId, which is a unique identifier that can
  *          be associated with the event that triggered the callback.
  * 
  *************************************************************************************
**/

#ifndef __IEventCallbackHandler_H_
#define __IEventCallbackHandler_H_

#include "Arduino.h"

// EventName type is just a character array of size 4.
//typedef struct EventName { char x[4]; } EventName;
typedef uint8_t EventId;

struct IEventCallbackHandler
{
    virtual void RegisterEventCallback(
        const EventId& eventId,
        void(*callback)(void*)) = 0;

    virtual void UnregisterEventCallback(int8_t);
};

#endif
