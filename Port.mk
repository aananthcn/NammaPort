#COMPILER=
#CC=${COMPILER}gcc
#LD=${COMPILER}gcc
#AS=${COMPILER}as
#OBJCOPY=${COMPILER}objcopy
#ARCH = x86

INCDIRS  += -I ${PORT_PATH}/src \
	    -I ${PORT_PATH}/api	\
	    -I ${PORT_PATH}/cfg \
	    -I ${PORT_PATH}/src/board/

LDFLAGS  += -g
CFLAGS   += -Werror ${INCDIRS} -g
ASFLAGS  += ${INCDIRS} -g

$(info compiling Port source files)


PORT_OBJS := \
	${PORT_PATH}/src/Port.o \
	${PORT_PATH}/src/board/rp2040/brd_port.o \
	${PORT_PATH}/cfg/Port_cfg.o

