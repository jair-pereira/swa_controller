#
#             LUFA Library
#     Copyright (C) Dean Camera, 2014.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#
# --------------------------------------
#         LUFA Project Makefile.
# --------------------------------------

# Run "make help" for target help.
# at90usb1286 for teensy and atmega32u4 for arduino

MCU          = at90usb1286
ARCH         = AVR8
F_CPU        = 16000000
F_USB        = $(F_CPU)
OPTIMIZATION = s
TARGET       = build/Joystick

LIB_DIRS     := $(wildcard lib/*/)
SRC          = Joystick.c Descriptors.c $(LUFA_SRC_USB) $(LUFA_SRC_SERIAL) $(wildcard $(addsuffix *.c,$(LIB_DIRS)))
LUFA_PATH    = ./lib/external/lufa/LUFA

CC_FLAGS     = -DUSE_LUFA_CONFIG_HEADER -IConfig/ $(addprefix -I,$(LIB_DIRS))
LD_FLAGS     =

# Default target
all:

# Include LUFA build script makefiles
include $(LUFA_PATH)/Build/lufa_core.mk
include $(LUFA_PATH)/Build/lufa_sources.mk
include $(LUFA_PATH)/Build/lufa_build.mk
include $(LUFA_PATH)/Build/lufa_cppcheck.mk
include $(LUFA_PATH)/Build/lufa_doxygen.mk
include $(LUFA_PATH)/Build/lufa_dfu.mk
include $(LUFA_PATH)/Build/lufa_hid.mk
include $(LUFA_PATH)/Build/lufa_avrdude.mk
include $(LUFA_PATH)/Build/lufa_atprogram.mk
