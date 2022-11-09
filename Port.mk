INCDIRS  += -I ${PORT_PATH}/src \
	    -I ${PORT_PATH}/api	\
	    -I ${PORT_PATH}/cfg \
	    -I ${PORT_PATH}/src/bsp/

LDFLAGS  += -g
CFLAGS   += -Werror ${INCDIRS} -g
ASFLAGS  += ${INCDIRS} -g

$(info compiling Port source files)


PORT_OBJS := \
	${PORT_PATH}/src/Port.o \
	${PORT_PATH}/src/bsp/rp2040/bsp_port.o \
	${PORT_PATH}/cfg/Port_cfg.o

