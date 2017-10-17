LTZVisor
=========


Introduction
------------

LTZVisor is a lightweight TrustZone-assisted hypervisor. It allows the 
consolidation of two virtual machines (VMs), running each of them in 
an independent virtual world (secure and non-secure) supported by 
TrustZone-enabled processors. 
The secure world is tipically used for running a small TCB size VM, 
while the non-secure world is used for running a rich environment. 
  
For the Cortex-A series a tipical configuration encompasses 
running a RTOS as secure VM and a GPOS as non-secure VM.
For the new generation Cortex-M microcontrollers it can be used for 
running a bare metal application or a lightweight RTOS as secure VM 
side by side with a RTOS or an embedded OS for IoT as non-secure VM.  


**NOTE**: This is work in progress! Don't expect things to be complete. 
Use at your own risk.


Community Resources
-------------------

Project website:

 - http://www.tzvisor.org/

Project home:

 - https://github.com/tzvisor
 
LTZVisor source code:

 - https://github.com/tzvisor/ltzvisor
 
Mailing list:
	
 - ltzvisor-dev@googlegroups.com
 
Frequently Asked Questions (FAQ):

 - Please see [FAQ file](FAQ.md)
 
Contributing:

 - Please see [Contribution file](CONTRIBUTING)


Hardware requirements
------------

LTZVisor is limited by design to TrustZone-enabled ARM processors,
which include all Cortex-A series (ARMv7-A and ARMv8-A) and the 
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

 - ARMv7-A
	* Xilinx Zynq-7000 All Programmable SoC ZC702 Evaluation Kit
	* ZedBoard Zynq-7000 ARM/FPGA SoC Development Board 
	* Zybo Zynq-7000 ARM/FPGA SoC Trainer Board 
	* PYNQ-Z1 Python Productivity for Zynq (on going)
	* i.MX 6QuadPlus SABRE Development Board (on going)
	
 - ARMv8-A
	* Xilinx Zynq UltraScale+ MPSoC ZCU102 Evaluation Kit (on going)
 

 
Software requirements
------------
For building LTZVisor a host system should exist. The host system 
must be endowed with an Operating Systems supporting a compilation 
toolchain. We strongly recommend the use of Linaro GNU Toolchain:

 - Ubuntu 12.04 and Linaro GNU Toolchain (7.1.1-2017.08)
	* arm-eabi-gcc 7.1.1 
	* arm-eabi-as 2.28.2
	* arm-none-eabi-ld 2.28.2
	* arm-none-eabi-objcopy 2.28.2 

Download: https://releases.linaro.org/components/toolchain/binaries/7.1-2017.08/arm-eabi/

LTZVisor was also tested under the following host 
configurations:

 - Ubuntu 12.04 and Sourcery G++ Lite Toolchain (2011.03-42)
	* arm-none-eabi-gcc 4.5.2 
	* arm-none-eabi-as 2.20.51
	* arm-none-eabi-ld 2.20.51 
	* arm-none-eabi-objcopy 2.20.51 

For Xilinx-based platforms LTZVisor was also tested under 
the following host configurations:	

 - Ubuntu 12.04 and Sourcery CodeBench Lite Toolchain (2012.09-105)
	* arm-xilinx-eabi-gcc 4.7.2
	* arm-xilinx-eabi-as 2.23.51 
	* arm-xilinx-eabi-ld 2.23.51 
	* arm-xilinx-eabi-objcopy 2.23.51 

 - Windows 10 and Sourcery CodeBench Lite Toolchain (2015.05-16)
	* arm-xilinx-eabi-gcc 4.9.2
	* arm-xilinx-eabi-as 2.24.51 
	* arm-xilinx-eabi-ld 2.24.51 
	* arm-xilinx-eabi-objcopy 2.24.51 
	
Guest Operating Systems
------------

LTZVisor supports the following guest operating systems:

 - Secure: FreeRTOS, bare metal
 - Non-secure: Linux, bare metal

Build & Compile
------------

For build LTZVisor, just run `make`:

	make 
	
The default configuration targets the ZedBoard platform, uses
the Sourcery G++ Lite Toolchain, and setup ups a system with two
bare metal VMs. 

Optionally it is possible to specify the target board:

 - Xilinx Zynq-7000 All Programmable SoC ZC702 Evaluation Kit:
	
	`make BOARD=ZC702`

 - ZedBoard Zynq-7000 ARM/FPGA SoC Development Board
 
	`make BOARD=ZEDBOARD`
 
 - Zybo Zynq-7000 ARM/FPGA SoC Trainer Board
 
	`make BOARD=ZYBO`
	
It is also possible to specify the cross compile toolchain as well
as the VMs configuration:

	make [BOARD=ZC702] [CROSS_COMPILE=arm-xilinx-eabi-] [S_GUEST=BARE_METAL] [NS_GUEST=BARE_METAL]

(Instructions explaining how to run FreeRTOS as secure guest-OS 
and Linux as non-secure guest-OS will be added soon).	

Demonstration
------------

Before power-on your board, please make sure that you copy the 
bootloader and LTZVisor binary images to the SD card . The bootloader
is provided in the LTZVisor source project under the folder "bootloader".
Each board as a specific bootloader. Also, please make sure that your 
board is configured to boot from the SD card.

1. Power-on your board;

2. Run any terminal and setup the serial port for 115200 bps (baud rate);

3. Stop the autoboot by hitting any key;

4. Type the following sequence of commands:

	- Xilinx Zynq-7000 All Programmable SoC ZC702 Evaluation Kit:
 
		`mmcinfo`
		
		`fatload mmc 0 0x3C000000 LTZVisor.bin`
		
		`go 0x3C000000` 

	- ZedBoard Zynq-7000 ARM/FPGA SoC Development Board:
 
		`mmcinfo`
		
		`fatload mmc 0 0x1C000000 LTZVisor.bin`
		
		`go 0x1C000000` 
	
	- Zybo Zynq-7000 ARM/FPGA SoC Trainer Board:
 
		`mmcinfo`
		
		`fatload mmc 0 0x1C000000 LTZVisor.bin`
		
		`go 0x1C000000` 

LTZVisor shall start immediately running! For the default system 
configuration (two bare metal VMs) the secure VM shall blink a 
set of LEDs every second, while the non-secure VM shall print 
"Hello World" messages. 

References
------------

 1. Sandro Pinto, Jorge Pereira, Tiago Gomes, Adriano Tavares, and Jorge Cabral. 
 "LTZVisor: TrustZone is the Key." In LIPIcs-Leibniz International Proceedings 
 in Informatics, vol. 76. Schloss Dagstuhl-Leibniz-Zentrum fuer Informatik, 2017.
 
 2. Sandro Pinto, Daniel Oliveira, Jorge Pereira, Nuno Cardoso, Mongkol 
 Ekpanyapong, Jorge Cabral, and Adriano Tavares. "Towards a lightweight embedded 
 virtualization architecture exploiting ARM TrustZone." In Emerging Technology 
 and Factory Automation (ETFA), IEEE, pp. 1-4., 2014.

