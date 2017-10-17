ifndef SDK_PATH
	$(error SDK_PATH must be defined before this file is included)
endif

SHELL := /bin/bash
DEBUG=y

export $BOARD


# Directories
cur_dir=$(SDK_PATH)/src
src_dir=$(cur_dir)
bin_dir=$(cur_dir)/../bin

# Name & Version
export PROJECT_NAME = LTZVisor
export PROJECT_VERSION = $(HYPERVISOR_MAJOR_VERSION).$(HYPERVISOR_MINOR_VERSION).$(HYPERVISOR_REVISION_VERSION)

# Configuration File
ifeq ($(BOARD), ZC702)
	export BOARD_DIR = zc702
	export ARM_ARCH = ARMV7
	export ARM_CPU = CORTEX_A9
	TARGET_CCFLAGS += -DCONFIG_ZYNQ=1
	TARGET_ASMFLAGS += -DCONFIG_ZYNQ=1
endif
ifeq ($(BOARD), ZEDBOARD)
	export BOARD_DIR = zedboard
	export ARM_ARCH = ARMV7
	export ARM_CPU = CORTEX_A9
	TARGET_CCFLAGS += -DCONFIG_ZYNQ=1
	TARGET_ASMFLAGS += -DCONFIG_ZYNQ=1
endif
ifeq ($(BOARD), ZYBO)
	export BOARD_DIR = zybo
	export ARM_ARCH = ARMV7
	export ARM_CPU = CORTEX_A9
	TARGET_CCFLAGS += -DCONFIG_ZYNQ=1
	TARGET_ASMFLAGS += -DCONFIG_ZYNQ=1
endif

-include $(CONFIG_FILE)

# Architecture definition
ifeq ($(ARM_ARCH), ARMV7)
	export ARCH_DIR=armv7
endif

# CPU definition
ifeq ($(ARM_CPU), CORTEX_A9)
	TARGET_CCFLAGS += -DCONFIG_CORTEX_A9=1 -mcpu=cortex-a9
	TARGET_ASMFLAGS += -DCONFIG_CORTEX_A9=1 -mcpu=cortex-a9
	export PLATFORM_DIR=Cortex-A9
endif

# Support NS_Guest
ifeq ($(NS_GUEST), BARE_METAL)
	TARGET_CCFLAGS += -DCONFIG_NS_BM=1
	TARGET_ASMFLAGS += -DCONFIG_NS_BM=1
endif


# Setup path of Hypervisor directories
export cpu_arch_dir=$(src_dir)/arch/$(ARCH_DIR)
export cpu_platform_dir=$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)
export lib_dir=$(src_dir)/lib
export core_dir=$(src_dir)/core
export drivers_common_dir=$(src_dir)/drivers
export boards_dir=$(src_dir)/boards/$(BOARD_DIR)
export ns_guest_dir=$(src_dir)/ns_guest
export s_guest_dir=$(src_dir)/s_guest

OFFSETS_FILE= $(cpu_arch_dir)/inc/asm-offsets.h
LD_SCRIPT	= $(boards_dir)/linker.ld
#ifeq ($(BM_SUPPORT), y)
	KERNEL = $(s_guest_dir)/kernel.o
#endif
#ifeq ($(FreeRTOS_SUPPORT), y)
#	KERNEL = $(s_guest_dir)/kernel.o
#endif

# Setup list of objects for compilation
cpu-platform-mks=$(shell if [ -d $(cpu_platform_dir) ]; then find $(cpu_platform_dir) -iname "objects.mk" | sort -r; fi)
cpu-object-mks=$(shell if [ -d $(cpu_arch_dir) ]; then find $(cpu_arch_dir) -iname "objects.mk" | sort -r; fi)
lib-object-mks=$(shell if [ -d $(lib_dir) ]; then find $(lib_dir) -iname "objects.mk" | sort -r; fi)
core-object-mks=$(shell if [[ -d $(core_dir) ]]; then find $(core_dir) -iname "objects.mk" | sort -r; fi)
drivers-common-object-mks=$(shell if [ -d $(drivers_common_dir) ]; then find $(drivers_common_dir) -iname "objects.mk" | sort -r; fi)
boards-object-mks=$(shell if [ -d $(boards_dir) ]; then find $(boards_dir) -iname "objects.mk" | sort -r; fi)
ns_guest-object-mks=$(shell if [ -d $(ns_guest_dir) ]; then find $(ns_guest_dir) -iname "objects.mk" | sort -r; fi)
s_guest-object-mks=$(shell if [ -d $(s_guest_dir) ]; then find $(s_guest_dir) -iname "objects.mk" | sort -r; fi)

# Setup path of S_Guest directories
ifeq ($(S_GUEST), BARE_METAL)
	export bm_core_dir=$(s_guest_dir)/BareApp
	export bm_core_port_dir=$(bm_core_dir)/portable
	# Setup list of objects for compilation
	bm_core-mks=$(shell if [ -d $(bm_core_dir) ]; then find $(bm_core_dir) -iname "objects.mk" | sort -r; fi)
	bm_core_port-mks=$(shell if [ -d $(bm_core_port_dir) ]; then find $(bm_core_port_dir) -iname "objects.mk" | sort -r; fi)
endif
ifeq ($(S_GUEST), FREERTOS)
	export freertos_core_dir=$(s_guest_dir)/FreeRTOS
	export freertos_core_apps_dir=$(freertos_core_dir)/apps
	export freertos_portable_gcc_dir=$(freertos_core_dir)/portable/GCC
	export freertos_portable_mem_dir=$(freertos_core_dir)/portable/MemMang
	# Setup list of objects for compilation
	freertos-core-mks=$(shell if [ -d $(freertos_core_dir) ]; then find $(freertos_core_dir) -iname "objects.mk" | sort -r; fi)
	freertos-portable-gcc-mks=$(shell if [ -d $(freertos_portable_gcc_dir) ]; then find $(freertos_portable_gcc_dir) -iname "objects.mk" | sort -r; fi)
	freertos-portable-mem-mks=$(shell if [ -d $(freertos_portable_mem_dir) ]; then find $(freertos_portable_mem_dir) -iname "objects.mk" | sort -r; fi)
	freertos-core-apps-mks=$(shell if [ -d $(freertos_core_apps_dir) ]; then find $(freertos_core_apps_dir) -iname "objects.mk" | sort -r; fi)
endif

include $(cpu-platform-mks)
include $(cpu-object-mks)
include $(lib-object-mks)
include $(core-object-mks)
include $(drivers-common-object-mks) 
include $(boards-object-mks)
include $(ns_guest-object-mks)
include $(s_guest-object-mks)
ifeq ($(S_GUEST), BARE_METAL)
	include $(bm_core-mks)
	include $(bm_core_port-mks)
endif
ifeq ($(S_GUEST), FREERTOS)
	include $(freertos-core-mks)
	include $(freertos-core-apps-mks)
	include $(freertos-portable-gcc-mks)
	include $(freertos-portable-mem-mks)
endif

objs-y+=$(foreach obj,$(cpu-objs-y),$(src_dir)/arch/$(ARCH_DIR)/$(obj))
objs-y+=$(foreach obj,$(cpu-platform-objs-y),$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)/$(obj))
objs-y+=$(foreach obj,$(lib-objs-y),$(src_dir)/lib/$(obj))
objs-y+=$(foreach obj,$(core-objs-y),$(src_dir)/core/$(obj))
objs-y+=$(foreach obj,$(drivers-common-objs-y),$(src_dir)/drivers/$(obj))
objs-y+=$(foreach obj,$(boards-objs-y),$(src_dir)/boards/$(BOARD_DIR)/$(obj))
objs-y+=$(foreach obj,$(ns_guest-objs-y),$(src_dir)/ns_guest/$(obj))

ifeq ($(S_GUEST), BARE_METAL)
	bm_guest-objs-y=$(foreach obj,$(s_guest-objs-y),$(bm_core_dir)/$(obj))
	bm_guest-objs-y+=$(foreach obj,$(s_guest_port-objs-y),$(bm_core_port_dir)/$(obj))
endif
ifeq ($(S_GUEST), FREERTOS)
	objs-y+=$(foreach obj,$(s_guest-objs-y),$(src_dir)/s_guest/$(obj))
	kernel-objs-y=$(foreach obj,$(kernel-portable-gcc-objs-y),$(freertos_portable_gcc_dir)/$(obj))
	kernel-objs-y+=$(foreach obj,$(kernel-core-objs-y),$(freertos_core_dir)/$(obj))
	kernel-objs-y+=$(foreach obj,$(kernel-core-app-objs-y),$(freertos_core_apps_dir)/$(obj))
	kernel-objs-y+=$(foreach obj,$(kernel-portable-mem-objs-y),$(freertos_portable_mem_dir)/$(obj))
endif

# Setup list of targets for compilation
targets-y=$(bin_dir)/$(PROJECT_NAME).elf
targets-y+=$(bin_dir)/$(PROJECT_NAME).bin

# Setup Hypervisor compilation environment
cpp=$(CROSS_COMPILE)cpp -g
cppflags=-I$(SDK_PATH)/inc
cppflags+=-I$(src_dir)/lib/inc
cppflags+=-I$(src_dir)/core/inc
cppflags+=-I$(src_dir)/arch/$(ARCH_DIR)/inc
cppflags+=-I$(src_dir)/drivers/inc
cppflags+=-I$(src_dir)/boards/$(BOARD_DIR)/inc
cppflags+=-I$(src_dir)/arch/$(ARCH_DIR)/$(PLATFORM_DIR)/inc
cppflags+=-I$(src_dir)/ns_guest/inc

# Setup S_Guest compilation environment
ifeq ($(S_GUEST), BARE_METAL)
	cppflags+=-I $(bm_core_port_dir)/inc
endif
ifeq ($(S_GUEST), FREERTOS)
	cppflags+=-I $(freertos_core_dir)/inc
	cppflags+=-I $(freertos_portable_gcc_dir)/inc
	cppflags+=-I $(freertos_portable_mem_dir)/inc
endif


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

visor_cflags=$(cppflags) $(TARGET_CCFLAGS) $(cflags)
visor_asflags=$(asflags) $(cppflags) $(TARGET_ASMFLAGS) -nostdlib

final-objs-y=$(objs-y)
ifeq ($(S_GUEST), BARE_METAL)
	final-objs-y+=$(bm_guest-objs-y)
endif
ifeq ($(S_GUEST), FREERTOS)
	final-objs-y+=$(kernel-objs-y)
endif

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
