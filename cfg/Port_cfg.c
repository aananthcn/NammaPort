#include <Port_cfg.h>


// This file is autogenerated, any hand modifications will be lost!

Port_ConfigType PortConfigs = {
	.num_pins = PORT_NUM_OF_PINS,
	.pin[0] = {
		.pin_id = 65535,
		.pin_dir = PORT_PIN_IN,
		.pin_mode = PORT_PIN_MODE_DIO,
		.pin_level = PORT_PIN_LEVEL_LOW,
		.pin_initial_mode = PORT_PIN_MODE_DIO,
		.pin_dir_changeable = FALSE,
		.pin_mode_changeable = FALSE
	},
	.pin[1] = {
		.pin_id = 34,
		.pin_dir = PORT_PIN_OUT,
		.pin_mode = PORT_PIN_MODE_DIO_WDG,
		.pin_level = PORT_PIN_LEVEL_HIGH,
		.pin_initial_mode = PORT_PIN_MODE_DIO_WDG,
		.pin_dir_changeable = FALSE,
		.pin_mode_changeable = TRUE
	},
	.pin[2] = {
		.pin_id = 5,
		.pin_dir = PORT_PIN_IN,
		.pin_mode = PORT_PIN_MODE_CAN,
		.pin_level = PORT_PIN_LEVEL_LOW,
		.pin_initial_mode = PORT_PIN_MODE_CAN,
		.pin_dir_changeable = TRUE,
		.pin_mode_changeable = TRUE
	}
};
