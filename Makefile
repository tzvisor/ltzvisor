HYPERVISOR_PRODUCT = LTZVisor
HYPERVISOR_MAJOR_VERSION = 0
HYPERVISOR_MINOR_VERSION = 1

export BOARD:= ZYNQ
export ARM_CPU:= CORTEX_A9
export ARM_ARCH:= ARMV7
export OS_SUPPORT:=y
export GPOS_DDR:=y

# .::FreeRTOS APPs::. #
export NORMAL_APPLICATION:=y

export SDK_PATH= $(CURDIR)

all:
	echo 'LTZVisor builds start'
	$(MAKE) -C $(SDK_PATH)/src
	
clean:
	$(MAKE) -C $(SDK_PATH)/src clean
	
	sudo rm -f bin/*
	sudo rm -f $(VERSION_FILE)
