F_CPU = 8000000UL
MCU = m328p

CC = avr-gcc

MODULES = user nrf24

BUILD_ROOT = build
BUILD_DIR := $(addprefix $(BUILD_ROOT)/,$(MODULES))

FIRMWARE_ROOT = firmware
HEX_FILE = $(FIRMWARE_ROOT)/app.hex
ELF_FILE = $(FIRMWARE_ROOT)/app.elf

SRC_DIR	:= $(MODULES)
SRC	:= $(foreach sdir,$(SRC_DIR),$(wildcard $(sdir)/*.c))

OBJS = $(patsubst %.c,$(BUILD_ROOT)/%.o,$(SRC))

INCLUDES := $(foreach sdir,$(SRC_DIR),$(patsubst %,-I%, $(addsuffix /include, $(sdir))))

CFLAGS = -g -Os -mmcu=atmega328 -c -DF_CPU=$(F_CPU) $(INCLUDES)
LDFLAGS = -g -mmcu=atmega328

.PHONY: all hex clean dirs

all: hex

flash: hex
	avrdude -F -V -c stk500v1 -p m328p -P /dev/ttyUSB0 -b 57600 -U flash:w:$(HEX_FILE)

hex: clean dirs $(HEX_FILE)

clean:
	@rm -rf $(BUILD_ROOT)
	@rm -rf $(FIRMWARE_ROOT)

dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(FIRMWARE_ROOT)

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) $< -o $@

$(ELF_FILE): $(OBJS)
	$(CC) $(LINKERFLAGS) $^ -o $@

$(HEX_FILE): $(ELF_FILE)
	avr-objcopy -j .text -j .data -O ihex $< $@
