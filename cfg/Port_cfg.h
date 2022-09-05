#ifndef NAMMA_AUTOSAR_PORT_CFG_H
#define NAMMA_AUTOSAR_PORT_CFG_H

// This file is autogenerated, any hand modifications will be lost!

#include <port_types.h>


typedef struct {
	Port_PinType pin_id;
	Port_PinDirectionType pin_dir;
	boolean pin_dir_changeable;
	Port_PinModeType pin_mode;
	Port_PinModeType pin_initial_mode;
	uint8 pin_level;
	boolean pin_mode_changeable;
} PortPin;


#define PORT_NUM_OF_PINS  (3)
typedef struct {
	Port_PinType num_pins;
	PortPin pin[PORT_NUM_OF_PINS];
} Port_ConfigType;

extern Port_ConfigType PortConfigs;



#endif
