/**************************************************************************************
 * Copyright Naigon's Electronic Creations 2018. All rights reserved.
 **************************************************************************************/

/**
  *************************************************************************************
  * @file    IEventCallbackHandler.h
  * @author  Naigon's Electronic Creations
  * @brief   IEventCallbackHandler
  *          Interface for registering and calling back different functions when a
  *          specific event occurs.
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
