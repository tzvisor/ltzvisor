HYPERVISOR_PRODUCT = LTZVisor
HYPERVISOR_MAJOR_VERSION = 0
HYPERVISOR_MINOR_VERSION = 1

export ARM_CPU:= CORTEX_A9
export ARM_ARCH:= ARMV7
export BOARD:= ZC702
export OS_SUPPORT:=y
export BM_SUPPORT:=y
export FreeRTOS_SUPPORT:=n
export GPOS_DDR:=n

export SDK_PATH= $(CURDIR)
export CROSS_COMPILE=/opt/CodeSourcery/arm-2010q1/bin/arm-none-linux-gnueabi-

all:
	echo 'LTZVisor builds start'
	$(MAKE) -C $(SDK_PATH)/src
	
clean:
	$(MAKE) -C $(SDK_PATH)/src clean
	
	sudo rm -f bin/*.bin bin/*.elf
	sudo rm -f $(VERSION_FILE)
