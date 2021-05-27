###############################################################################
# Makefile for the project Move_4_UART
###############################################################################

## General Flags
PROJECT = Move_4_UART
MCU = atmega128
TARGET = Move_4_UART.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -O0 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Move_4_UART.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = Move_4_UART.o avr_lib.o RBC_Motor.o Robocar_init.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Move_4_UART.hex Move_4_UART.eep Move_4_UART.lss size

## Compile
Move_4_UART.o: ../Move_4_UART.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

avr_lib.o: ../avr_lib.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

RBC_Motor.o: ../RBC_Motor.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Robocar_init.o: ../Robocar_init.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Move_4_UART.elf dep/* Move_4_UART.hex Move_4_UART.eep Move_4_UART.lss Move_4_UART.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

