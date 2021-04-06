PROJ_NAME=bldc
BUILD_DIR=./build

# Path to dependencies.
LIBS_DIR=${HOME}/opt

# Path to LIBC.
LIBC_DIR=$(LIBS_DIR)
LIBC_PATH=$(LIBC_DIR)/buildresults/src

RTOS_DIR=./rtos

HAL_SRC_DIR=./hal/src

UCMD_DIR=./libs/ucmd

CODEGEN_DIR=./mbd/codegen/ctrl_ert_rtw

HAL_INC=./hal/inc

RTOS_INC=$(RTOS_DIR)/include \
	$(RTOS_DIR)/ARM_CM4F \

INC_DIRS+=./sys/inc
INC_DIRS+=./hw/inc
INC_DIRS+=./app/inc
INC_DIRS+=$(RTOS_INC)
INC_DIRS+=$(HAL_INC)
INC_DIRS+=./libs/printf
INC_DIRS+=./libs/ucmd
INC_DIRS+=$(CODEGEN_DIR)

SRCS=app/src/main.c
SRCS+=hw/src/gpio.c
SRCS+=hw/src/adc.c
SRCS+=hw/src/pwm.c
SRCS+=hw/src/uart.c
SRCS+=hw/src/tmr.c
SRCS+=hw/src/enc.c
SRCS+=app/src/apptasks.c
SRCS+=app/src/app.c
SRCS+=app/src/mtrif.c
SRCS+=app/src/command.c
SRCS+=sys/src/system_stm32f3xx.c
SRCS+=sys/src/startup_stm32f302x8.s
SRCS+=sys/src/stm32f3xx_it.c

# Code generated files.
SRCS+=$(CODEGEN_DIR)/ctrl.c
SRCS+=$(CODEGEN_DIR)/ctrl_fast.c
SRCS+=$(CODEGEN_DIR)/ctrl_slow.c
SRCS+=$(CODEGEN_DIR)/ctrl_data.c

SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_cortex.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_rcc.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_rcc_ex.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_gpio.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_adc.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_adc_ex.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_dma.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_tim.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_tim_ex.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_uart.c
SRCS+=$(HAL_SRC_DIR)/stm32f3xx_hal_uart_ex.c

# Location for command utility.
SRCS+=$(UCMD_DIR)/ucmd.c
SRCS+=$(UCMD_DIR)/line.c
SRCS+=$(UCMD_DIR)/err.c
SRCS+=$(UCMD_DIR)/utils.c

# This is the location for printf.c file implementation from Embdedded Artistry.
SRCS+=./libs/printf/printf.c
 
# This is the location of port.c file.
SRCS+=$(RTOS_DIR)/ARM_CM4F/port.c
SRCS+=$(RTOS_DIR)/MemMang/heap_2.c

# This is where the actual implementation of FreeRTOS is.
SRCS+=$(RTOS_DIR)/task.c
SRCS+=$(RTOS_DIR)/timers.c
SRCS+=$(RTOS_DIR)/queue.c
SRCS+=$(RTOS_DIR)/list.c
SRCS+=$(RTOS_DIR)/stream_buffer.c

# SRCS:=$(shell find $(SRC_DIRS) -name *.c)
OBJS:=$(SRCS:%=$(BUILD_DIR)/%.o)

CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy
OBJDUMP=arm-none-eabi-objdump
GDB=arm-none-eabi-gdb-py
SZ=arm-none-eabi-size

# Project Defines.
DEFS=-DSTM32F302x8 \
	-D__SLOG__ \
	-DUSE_HAL_DRIVER \
#	-D__DBG__ \

TARGET_FLAGS=-mcpu=cortex-m4 \
	-mthumb \
	-mfpu=fpv4-sp-d16 \
	-mfloat-abi=hard \

CFLAGS=$(TARGET_FLAGS) \
	-g \
	-Os \
	-Wall \
	-lc \
	--specs=nosys.specs \
	-fsingle-precision-constant \
	-fdata-sections \
	-ffunction-sections \
	-fno-math-errno \

LINKER_FILE=./linker/stm32f30_flash.ld

LFLAGS=$(TARGET_FLAGS) \
	-Wl,-Map,$(BUILD_DIR)/$(PROJ_NAME).map -T$(LINKER_FILE) \
	-Wl,--gc-sections \
	-Wl,--print-memory-usage \
	-lc \
	-lm \

# Dependencies and object file definitions,
INCLUDE=$(addprefix -I,$(INC_DIRS))

# Use compiler flags w/ optimizations turned for libraries, as it most likely
# this will not need to be debugged. Use the same LIB_FLAGS for all libraries.
# $(HAL_OBJS): CFLAGS:=$(LIB_FLAGS)
$(BUILD_DIR)/$(PROJ_NAME): $(OBJS)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(OBJS) -o $@.elf $(LFLAGS)
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJ_NAME).elf   $(BUILD_DIR)/$(PROJ_NAME).hex
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(PROJ_NAME).elf $(BUILD_DIR)/$(PROJ_NAME).bin
	$(SZ) $(BUILD_DIR)/$(PROJ_NAME).elf

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(DEFS) $(CFLAGS) $(EXTRA_FLAGS) -c -o $@ $<

$(BUILD_DIR)/%.s.o: %.s
	mkdir -p $(dir $@)
	$(CC) $(INCLUDE) $(DEFS) -c -o $@ $< $(CFLAGS) $(EXTRA_FLAGS)

dump:
	$(OBJDUMP) -D --source $(BUILD_DIR)/$(PROJ_NAME).elf > $(BUILD_DIR)/$(PROJ_NAME).dump

clean:
	rm -rf $(BUILD_DIR)

flash:
	st-flash write $(BUILD_DIR)/$(PROJ_NAME).bin 0x8000000

stlink:
	st-util -p4242

all:
	make clean && make && make flash

# before you start gdb, you must start st-util
debug:
	st-util &
	$(GDB) $(BUILD_DIR)/$(PROJ_NAME).elf
	killall st-util

.PHONY: dump clean flash stlink all debug hal rtos $(PROJ_NAME)
