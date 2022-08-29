/*
 * Created on Mon Aug 29 2022 11:20:57 PM
 *
 * The MIT License (MIT)
 * Copyright (c) 2022 Aananth C N
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
#ifndef PORT_H
#define PORT_H

#include <Std_Types.h>


/////////////////////////////////////////////
// Error codes
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                0x0A
/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE   0x0B
/* API Port_Init service called with wrong parameter */
#define PORT_E_INIT_FAILED              0x0C
/* API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_PARAM_INVALID_MODE       0x0D
/* API Port_SetPinMode service called when mode is unchangeable. */
#define PORT_E_MODE_UNCHANGEABLE        0x0E
/* API service called without module initialization */
#define PORT_E_UNINIT                   0x0F
/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER            0x10



/////////////////////////////////////////////
// Port data types
typedef uint16 Port_PinType;


typedef enum {
        PORT_PIN_IN,
        PORT_PIN_OUT
} Port_PinDirectionType;

typedef uint8 Port_PinModeType;


typedef struct {
        Port_PinModeType mode;                  /* DIO, ADC, SPI... */
        Port_PinDirectionType direction;        /* input, output */
        uint8 level;                            /* high, low */
        uint8 slewrate;
        uint8 pullup;
} Port_ConfigType;


/////////////////////////////////////////////
// Port Functions
void Port_Init(const Port_ConfigType* ConfigPtr);
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction);
void Port_RefreshPortDirection(void);
void Port_GetVersionInfo(Std_VersionInfoType* versioninfo);
void Port_SetPinMode(Port_PinType Pin,Port_PinModeType Mode);


#endif