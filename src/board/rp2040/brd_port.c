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


uint16 get_rp2040_mode(Port_PinModeType mode) {
	uint16 brd_mode = 0xFFFF;

	switch (mode) {
	case PORT_PIN_MODE_DIO:
	case PORT_PIN_MODE_DIO_GPT:
	case PORT_PIN_MODE_DIO_WDG:
		brd_mode = GPIO_FUNC_SIO;
		break;
	case PORT_PIN_MODE_ICU:
	case PORT_PIN_MODE_PWM:
		brd_mode = GPIO_FUNC_PWM;
		break;
	case PORT_PIN_MODE_SPI:
		brd_mode = GPIO_FUNC_SPI;
		break;
	default:
	case PORT_PIN_MODE_ADC:
	case PORT_PIN_MODE_CAN:
	case PORT_PIN_MODE_FLEXRAY:
	case PORT_PIN_MODE_LIN:
	case PORT_PIN_MODE_MEM:
		break;
	}

	return brd_mode;
}


/* Raspberry Pi specific port mode set function */
void brd_set_port_pad(Port_PinType pin_id, PortPin *pin_cfg) {
	uint32 brd_mode;
	uint32 pin_level;
	uint32 pin_dir;

	/* input validation */
	if (NULL == pin_cfg) {
		return;
	}

	/* convert AUTOSAR pin mode to board specific pin mode */
	brd_mode = pin_cfg->pin_mode;
	if (pin_cfg->pin_mode >= PORT_PIN_MODE_ADC) {
		brd_mode = get_rp2040_mode(pin_cfg->pin_mode);
	}

	/* pin direction related settings */
	if (pin_cfg->pin_dir == PORT_PIN_IN) {
		pin_dir = 0xC0;
	}
	else {
		pin_dir = 0;
	}

	/* set the PADS_BANK0 or 1  */
	SET_PAD_GPIO(pin_id, pin_dir);

	/* initial pin level */
	if (pin_cfg->pin_level == PORT_PIN_LEVEL_HIGH) {
		pin_level = 0x3 << 8;
	}
	else {
		pin_level = 0x2 << 8;
	}

	SET_GPIO_CTRL(pin_id, ((0x3 << 12) | pin_level | brd_mode));
}