/*
 * Created on Mon Sep 05 2022 6:02:18 PM
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

#include <Port.h>
#include <stddef.h>


#include <zephyr/logging/log.h> // for LOG_DBG()

/// @brief Initializes ports based on device tree structure
/// @param  none
/// @return 0 if all is well. Negative port number in case of error.
int port_zephyr_dt_init(void); // defined in Port_cfg.c


// Global variables
LOG_MODULE_REGISTER(Port, LOG_LEVEL_DBG);


/// @brief Initializes ports as per AUTOSAR specification
/// @param ConfigPtr 
void Port_Init(const Port_ConfigType* ConfigPtr) {
	int retval;

	if (NULL == ConfigPtr) {
		LOG_DBG("ERROR: %s initialization failed as argument passed is invalid!", __func__);
		return;
	}

	retval = port_zephyr_dt_init();
	if (0 != retval) {
		LOG_DBG("ERROR: %s initialization failed for pin %d!", __func__, -retval);
		return;
	}

	LOG_DBG("%s complete!\n", __func__);
}