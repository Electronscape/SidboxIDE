# toolchain.mk - shared toolchain and flags

# Set this to your exact desired compiler path
# TOOLCHAIN := /usr/st/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/bin
# TOOLCHAIN := /opt/st/stm32cubeide_1.6.0/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/tools/bin
# TOOLCHAIN := /opt/st/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.9-2020-q2-update.linux64_1.5.0.202011040924/bin
TOOLCHAIN := /home/kbox/sidbox-applet-compiler/tools/bin



CC      := $(TOOLCHAIN)/arm-none-eabi-gcc
OBJCOPY := $(TOOLCHAIN)/arm-none-eabi-objcopy
OBJDUMP := $(TOOLCHAIN)/arm-none-eabi-objdump
SIZE    := $(TOOLCHAIN)/arm-none-eabi-size
NM      := $(TOOLCHAIN)/arm-none-eabi-nm

#switch off warnings
WARNINGS := -w
#INCLUDES := -I$(PROJECT_DIR)/../../../_coreapi_
INCLUDES := -I$(CORE_DIR)
# INCLUDES := 

# Common flags
CFLAGS   := -mcpu=cortex-m7 -mthumb -mfpu=fpv5-d16 -std=gnu99 -c -ffunction-sections -fdata-sections -Wall -fstack-usage --specs=nano.specs -mfloat-abi=hard
#CFLAGS   += mstackrealign 
CFLAGS   += -mno-unaligned-access
CFLAGS   += $(WARNINGS) 
CFLAGS   += $(INCLUDES)


LDFLAGS  := -mcpu=cortex-m7 --specs=nosys.specs -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb
LDLIBS   := -Wl,--start-group -lc -lm -Wl,--end-group
