ifndef SDK_PATH
	$(error SDK_PATH must be defined before this file is included)
endif

SHELL := /bin/bash
DEBUG=y

export $BOARD
export $ARM_CPU
export $ARM_ARCH
export $MULTI_GPOS

# Directories
cur_dir=$(SDK_PATH)/src
src_dir=$(cur_dir)
bin_dir=$(cur_dir)/../bin

# Name & Version
export PROJECT_NAME = LTZVisor
export PROJECT_VERSION = 0.1

# Configuration File
ifeq ($(BOARD), ZYNQ)
	export BOARD_DIR=zynq
	TARGET_CCFLAGS += -DCONFIG_ZYNQ=1
	TARGET_ASMFLAGS += -DCONFIG_ZYNQ=1
endif

-include $(CONFIG_FILE)

# Architecture (ARMv7)
ifeq ($(ARM_ARCH), ARMV7)
	export ARCH_DIR=armv7
endif

# CPU definition
ifeq ($(ARM_CPU), CORTEX_A9)
	TARGET_CCFLAGS += -DCONFIG_CORTEX_A9=1 -mcpu=cortex-a9
	TARGET_ASMFLAGS += -DCONFIG_CORTEX_A9=1 -mcpu=cortex-a9
	export PLATFORM_DIR=Cortex-A9
endif

# Load NS_Guest to DDR 
ifeq ($(GPOS_DDR), y)
	TARGET_CCFLAGS += -DCONFIG_GPOSDDR=1
	TARGET_ASMFLAGS += -DCONFIG_GPOSDDR=1
endif

# Support S_Guest
ifeq ($(OS_SUPPORT), y)
	TARGET_CCFLAGS += -DCONFIG_OS_SUPPORT=1
	TARGET_ASMFLAGS += -DCONFIG_OS_SUPPORT=1
endif


# Setup path of Hypervisor directories
export cpu_arch_dir=$(src_dir)/arch/$(ARCH_DIR)
export cpu_platform_dir=$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)
export lib_dir=$(src_dir)/lib
export core_dir=$(src_dir)/core
export drivers_common_dir=$(src_dir)/drivers/common
export drivers_dir=$(src_dir)/drivers/$(BOARD_DIR)
export ns_guest_dir=$(src_dir)/ns_guest
export s_guest_dir=$(src_dir)/s_guest

OFFSETS_FILE= $(cpu_arch_dir)/inc/asm-offsets.h
LD_SCRIPT	= $(drivers_dir)/linker.ld
KERNEL		= $(s_guest_dir)/kernel.o

# Setup list of objects for compilation
cpu-platform-mks=$(shell if [ -d $(cpu_platform_dir) ]; then find $(cpu_platform_dir) -iname "objects.mk" | sort -r; fi)
cpu-object-mks=$(shell if [ -d $(cpu_arch_dir) ]; then find $(cpu_arch_dir) -iname "objects.mk" | sort -r; fi)
lib-object-mks=$(shell if [ -d $(lib_dir) ]; then find $(lib_dir) -iname "objects.mk" | sort -r; fi)
core-object-mks=$(shell if [[ -d $(core_dir) ]]; then find $(core_dir) -iname "objects.mk" | sort -r; fi)
drivers-common-object-mks=$(shell if [ -d $(drivers_common_dir) ]; then find $(drivers_common_dir) -iname "objects.mk" | sort -r; fi)
drivers-object-mks=$(shell if [ -d $(drivers_dir) ]; then find $(drivers_dir) -iname "objects.mk" | sort -r; fi)
ns_guest-object-mks=$(shell if [ -d $(ns_guest_dir) ]; then find $(ns_guest_dir) -iname "objects.mk" | sort -r; fi)
s_guest-object-mks=$(shell if [ -d $(s_guest_dir) ]; then find $(s_guest_dir) -iname "objects.mk" | sort -r; fi)

# Setup path of S_Guest directories
export freertos_core_dir=$(s_guest_dir)/FreeRTOS
export freertos_core_apps_dir=$(freertos_core_dir)/apps
export freertos_portable_gcc_dir=$(freertos_core_dir)/portable/GCC
export freertos_portable_mem_dir=$(freertos_core_dir)/portable/MemMang

# Setup list of objects for compilation
freertos-core-mks=$(shell if [ -d $(freertos_core_dir) ]; then find $(freertos_core_dir) -iname "objects.mk" | sort -r; fi)
freertos-portable-gcc-mks=$(shell if [ -d $(freertos_portable_gcc_dir) ]; then find $(freertos_portable_gcc_dir) -iname "objects.mk" | sort -r; fi)
freertos-portable-mem-mks=$(shell if [ -d $(freertos_portable_mem_dir) ]; then find $(freertos_portable_mem_dir) -iname "objects.mk" | sort -r; fi)
freertos-core-apps-mks=$(shell if [ -d $(freertos_core_apps_dir) ]; then find $(freertos_core_apps_dir) -iname "objects.mk" | sort -r; fi)

include $(cpu-platform-mks)
include $(cpu-object-mks)
include $(lib-object-mks)
include $(core-object-mks)
include $(drivers-common-object-mks) 
include $(drivers-object-mks)
include $(ns_guest-object-mks)
include $(s_guest-object-mks)

include $(freertos-core-mks)
include $(freertos-core-apps-mks)
include $(freertos-portable-gcc-mks)
include $(freertos-portable-mem-mks)

objs-y+=$(foreach obj,$(cpu-objs-y),$(src_dir)/arch/$(ARCH_DIR)/$(obj))
objs-y+=$(foreach obj,$(cpu-platform-objs-y),$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)/$(obj))
objs-y+=$(foreach obj,$(lib-objs-y),$(src_dir)/lib/$(obj))
objs-y+=$(foreach obj,$(core-objs-y),$(src_dir)/core/$(obj))
objs-y+=$(foreach obj,$(drivers-common-objs-y),$(src_dir)/drivers/common/$(obj))
objs-y+=$(foreach obj,$(drivers-objs-y),$(src_dir)/drivers/$(BOARD_DIR)/$(obj))
objs-y+=$(foreach obj,$(ns_guest-objs-y),$(src_dir)/ns_guest/$(obj))
objs-y+=$(foreach obj,$(s_guest-objs-y),$(src_dir)/s_guest/$(obj))

kernel-objs-y=$(foreach obj,$(kernel-portable-gcc-objs-y),$(freertos_portable_gcc_dir)/$(obj))
kernel-objs-y+=$(foreach obj,$(kernel-core-objs-y),$(freertos_core_dir)/$(obj))
kernel-objs-y+=$(foreach obj,$(kernel-core-app-objs-y),$(freertos_core_apps_dir)/$(obj))
kernel-objs-y+=$(foreach obj,$(kernel-portable-mem-objs-y),$(freertos_portable_mem_dir)/$(obj))

# Setup list of targets for compilation
targets-y=$(bin_dir)/$(PROJECT_NAME).elf
targets-y+=$(bin_dir)/$(PROJECT_NAME).bin

# Setup Hypervisor compilation environment
cpp=$(CROSS_COMPILE)cpp -g
cppflags=-I$(SDK_PATH)/inc
cppflags+=-I$(src_dir)/lib/inc
cppflags+=-I$(src_dir)/core/inc
cppflags+=-I$(src_dir)/arch/$(ARCH_DIR)/inc
cppflags+=-I$(src_dir)/drivers/common/inc
cppflags+=-I$(src_dir)/drivers/$(BOARD_DIR)/inc
cppflags+=-I$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)/inc
cppflags+=-I$(svisor_dir)/core/inc
cppflags+=-I$(src_dir)/ns_guest/inc

# Setup FreeRTOS compilation environment
cppflags+=-I $(freertos_core_dir)/inc
cppflags+=-I $(freertos_portable_gcc_dir)/inc
cppflags+=-I $(freertos_portable_mem_dir)/inc

export CROSS_COMPILE=/opt/CodeSourcery/arm-2010q1/bin/arm-none-linux-gnueabi-
# Compiler and Flags
sstrip = 	$(CROSS_COMPILE)strip
cc=			$(CROSS_COMPILE)gcc
lib_ld = 	$(CROSS_COMPILE)ld
as=			$(CROSS_COMPILE)gcc
ar=			$(CROSS_COMPILE)ar
ranlib=		$(CROSS_COMPILE)ranlib
ld=			$(CROSS_COMPILE)gcc
objcopy=	$(CROSS_COMPILE)objcopy
nm=			$(CROSS_COMPILE)nm
size=		$(CROSS_COMPILE)size

cflags= -O0 -Wall -fno-common -msoft-float -mno-thumb-interwork -marm -nostdlib -fno-short-enums
ifeq ($(DEBUG), y)
	cflags += -g
endif
ifeq ($(CONFIG_NEON_SUPPORT), y)
	cflags+= -mfloat-abi=softfp -mfpu=neon
endif
 
asflags= -Wall -D__ASSEMBLY__ -fno-common -mno-thumb-interwork -marm
ifeq ($(DEBUG), y)
	asflags += -g
endif
ifeq ($(CONFIG_NEON_SUPPORT), y)
	asflags+= -mfpu=neon
endif

ldflags= -nostdlib -nostartfiles  -T $(LD_SCRIPT)
ifeq ($(DEBUG), y)
	ldflags += -g
endif

visor_cflags=$(cppflags) $(TARGET_CCFLAGS) $(cflags) -DSW_KERNEL
visor_asflags=$(asflags) $(cppflags) $(TARGET_ASMFLAGS) -DSW_KERNEL -nostdlib

final-objs-y=$(objs-y)
final-objs-y+=$(kernel-objs-y)

# Default rule "make"
.PHONY: all
all: $(CONFIG_FILE) $(OFFSETS_FILE) $(targets-y)
	echo 'LTZVisor ready!!'
	
$(bin_dir)/$(PROJECT_NAME).elf: $(final-objs-y) #$(KERNEL)
	$(V)$(lib_ld) $(ldflags) $(final-objs-y) -o $@
ifneq ($(DEBUG), y)
	$(V)$(sstrip) -s $@
endif
	rm -f $(cpu_arch_dir)/asm-offsets.s;
	rm -f $(final-objs-y)
	
$(bin_dir)/$(PROJECT_NAME).bin: $(bin_dir)/$(PROJECT_NAME).elf
	$(V)$(objcopy) -O binary $< $@

$(OFFSETS_FILE): $(cpu_arch_dir)/asm-offsets.s
	sed -ne $(sed-y) $< >> $@
	sed -i '1i/* THIS FILE WAS GENERATED AUTOMATICALLY */' $@

#Making asm-offset.h
$(cpu_arch_dir)/asm-offsets.s: $(cpu_arch_dir)/asm-offsets.c
	$(V)$(cc) $(visor_cflags) -g -S -c $< -o $@

$(src_dir)/%.o: $(src_dir)/%.S
	$(V)$(as) $(visor_asflags) -g -c $< -o $@

$(src_dir)/%.o: $(src_dir)/%.c
	$(V)$(cc) $(visor_cflags) -g -c $< -o $@


define sed-y
        "/^->/{s:->#\(.*\):/* \1 */:; \
        s:^->\([^ ]*\) [\$$#]*\([^ ]*\) \(.*\):#define \1 \2 /* \3 */:; \
        s:->::; p;}"
endef	

.PHONY: clean
clean:
	rm -f $(OFFSETS_FILE)
	rm -f $(cpu_arch_dir)/asm-offsets.s; 
	rm -f $(final-objs-y)
	rm -f $(bin)/$(PROJECT_NAME).elf
	rm -f $(bin)/$(PROJECT_NAME).bin
