/*
 * Created on Mon Sep 05 2022 7:44:37 PM
 *
 * The MIT License (MIT)
 * Copyright (c) 2022 Aananth C N
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software without restriction:
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense:
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so:
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT:
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <rp2040.h>
#include <Port_cfg.h>
#include <stddef.h>

#include <bsp_port.h>


uint16 get_rp2040_mode(Port_PinModeType mode) {
        uint16 bsp_mode = 0xFFFF;

        switch (mode) {
        case PORT_PIN_MODE_DIO:
        case PORT_PIN_MODE_DIO_GPT:
        case PORT_PIN_MODE_DIO_WDG:
                bsp_mode = GPIO_FUNC_SIO;
                break;
        case PORT_PIN_MODE_ICU:
        case PORT_PIN_MODE_PWM:
                bsp_mode = GPIO_FUNC_PWM;
                break;
        case PORT_PIN_MODE_SPI:
                bsp_mode = GPIO_FUNC_SPI;
                break;
        case PORT_PIN_MODE_LIN:
                bsp_mode = GPIO_FUNC_UART;
                break;
        default:
        case PORT_PIN_MODE_ADC:
        case PORT_PIN_MODE_CAN:
        case PORT_PIN_MODE_FLEXRAY:
        case PORT_PIN_MODE_MEM:
                break;
        }

        return bsp_mode;
}


/* Raspberry Pi specific port mode set function */
uint8 bsp_set_port_pad(Port_PinType pin_id, PortPin *pin_cfg) {
        uint32 bsp_mode;
        uint8 pin_dir = 0;
        uint8 slewf = 0;

        /* input validation */
        if (NULL == pin_cfg) {
                return -1;
        }

        /* convert AUTOSAR pin mode to board specific pin mode */
        bsp_mode = pin_cfg->pin_mode;
        if (pin_cfg->pin_mode >= PORT_PIN_MODE_ADC) {
                bsp_mode = get_rp2040_mode(pin_cfg->pin_mode);
        }

        /* pin direction related settings */
        if (pin_cfg->pin_dir == PORT_PIN_IN) {
                pin_dir = 0xC0;
        }

        /* Slew rate control */
        if (bsp_mode == GPIO_FUNC_SPI) {
                slewf = 0x01; // Fast
        }

        /* set the PADS_BANK0 or 1  */
        SET_PAD_GPIO(pin_id, pin_dir|slewf);

        /* GPIO func_sel & output enable settings */
        SET_GPIO_CTRL(pin_id, bsp_mode);

        /* Set additional GPIO setting if mode == GPIO */
        if (bsp_mode == GPIO_FUNC_SIO) {
                SIO_GPIO_OE |= 1 << pin_id;

                /* initial pin level */
                if (pin_cfg->pin_level == PORT_PIN_LEVEL_HIGH) {
                        SIO_GPIO_OUT |= 1 << pin_id;
                }
                else {
                        SIO_GPIO_OUT &= ~(1 << pin_id);
                }
        }

        return 0;
}



uint8 bsp_set_pin_direction(Port_PinType pin_id, Port_PinDirectionType dir) {
        uint32 pad_reg;

        pad_reg = GET_PAD_GPIO(pin_id);
        if (dir == PORT_PIN_IN) {
                pad_reg |= 0xC0;
        }
        else {
                pad_reg &= ~(0xC0);
        }

        /* set the PADS_BANK0 or 1  */
        SET_PAD_GPIO(pin_id, pad_reg);

        return 0;
}


Port_PinDirectionType bsp_get_pin_direction(Port_PinType pin_id) {
        Port_PinDirectionType pin_dir = PORT_PIN_OUT;
        uint32 pad_reg;

        pad_reg = GET_PAD_GPIO(pin_id);
        if ((pad_reg & 0xC0) == 0xC0) {
                pin_dir = PORT_PIN_IN;
        }

        return pin_dir;
}


uint8 bsp_set_pin_mode(Port_PinType pin_id, Port_PinModeType pin_mode) {
        uint32 bsp_mode;
        uint32 ctrl_reg;

        bsp_mode = pin_mode;
        if (pin_mode >= PORT_PIN_MODE_ADC) {
                bsp_mode = get_rp2040_mode(pin_mode);
        }

        /* mask the last 5 bits (FUNCSEL) */
        ctrl_reg = GET_GPIO_CTRL(pin_id) & ~(0x1f);
        SET_GPIO_CTRL(pin_id, ctrl_reg | bsp_mode);

        return 0;
}