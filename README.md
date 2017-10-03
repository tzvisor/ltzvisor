LTZVisor
=========


Introduction
------------

LTZVisor is a lightweight TrustZone-assisted hypervisor. It allows the 
consolidation of two virtual machines (VMs), running in each virtual world
supported by TrustZone-enabled processors. The secure world tipically
is used for running a small TCB size VM, while the non-secure world 
  
For the Cortex-A series a tipical configuration includes 
running a RTOS as secure VM side by side with a GPOS as non-secure VM.
For the new generation Cortex-M microcontrollers it can be used for 
running a bare metal application or a lightweight RTOS as secure VM 
side by side with a RTOS or an embedded OS for IoT as non-secure VM.  


NOTE: This is work in progress! Don't expect things to be complete. Use at your own risk


Community Resources
-------------------

Project website:

 - http://www.tzvisor.org/

Project home:

 - https://github.com/tzvisor
 
LTZVisor source code:

 - https://github.com/tzvisor/ltzvisor
 - git@github.com:tzvisor/ltzvisor.git
 
Mailing list:
	
 - ltzvisor-dev@googlegroups.com
 
Frequently Asked Questions (FAQ):

 - Comming soon ...
 
Contributing:

 - Please check [contribution doc](CONTRIBUTING.md) for details.


Hardware requirements
------------

LTZVisor is limited by design to TrustZone-enabled ARM processors,
which includes all Cortex-A series (ARMv7-A and ARMv8-A) and the 
new generation Cortex-M series (ARMv8-M):

 - ARM Cortex-A5 (ARMv7-A)
 - ARM Cortex-A7 (ARMv7-A)
 - ARM Cortex-A8 (ARMv7-A)
 - ARM Cortex-A9 (ARMv7-A)
 - ARM Cortex-A15 (ARMv7-A)
 - ARM Cortex-A17 (ARMv7-A)
 
 - ARM Cortex-A32 (ARMv8-A)
 - ARM Cortex-A35 (ARMv8-A)
 - ARM Cortex-A53 (ARMv8-A)
 - ARM Cortex-A57 (ARMv8-A)
 - ARM Cortex-A72 (ARMv8-A)
 - ARM Cortex-A73 (ARMv8-A)
 
 - ARM Cortex-M23 (ARMv8-M)
 - ARM Cortex-M33 (ARMv8-M)


LTZVisor has support for the following boards:

 - Xilinx Zynq-7000 All Programmable SoC ZC702 Evaluation Kit
 - ZedBoard Zynq-7000 ARM/FPGA SoC Development Board 
 - Zybo Zynq-7000 ARM/FPGA SoC Trainer Board 
 - PYNQ-Z1 Python Productivity for Zynq (on going)
 - Xilinx Zynq UltraScale+ MPSoC ZCU102 Evaluation Kit (on going)
 - NXP i.MX6 (on going)

Software requirements
------------

LTZVisor was extensible tested under the following host configuration:

 - Ubuntu 12.04
	* arm-none-linux-gcc 


Configure
------------

Configuration information requirements comming soon ...


Build & Compile
------------

Configuration information requirements comming soon ...


Demonstration
------------

Demonstration information comming soon ...


References
------------

 1. LTZVisor ...
 
 2. Towards ...
