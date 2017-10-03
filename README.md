LTZVisor
=========


Introduction
------------

LTZVisor is a lightweight TrustZone-assisted hypervisor. It allows the 
consolidation of two virtual machines (VMs), running each oh them in 
an independent virtual world supported by TrustZone-enabled processors. 
The secure world tipically is used for running a small TCB size VM, 
while the non-secure world is used for running a rich environment. 
  
For the Cortex-A series a tipical configuration includes 
running a RTOS as secure VM and a GPOS as non-secure VM.
For the new generation Cortex-M microcontrollers it can be used for 
running a bare metal application or a lightweight RTOS as secure VM 
side by side with a RTOS or an embedded OS for IoT as non-secure VM.  


NOTE: This is work in progress! Don't expect things to be complete. 
Use at your own risk


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

LTZVisor was extensible tested under the following host configurations:

 - Ubuntu 12.04 and Sourcery G++ Lite Toolchain (2011.03-42)
	* arm-none-eabi-gcc 4.5.2 
	* arm-none-eabi-as 2.20.51
	* arm-none-eabi-ld 2.20.51 
	* arm-none-eabi-objcopy 2.20.51 
	
 - Ubuntu 12.04 and Sourcery CodeBench Lite Toolchain (2012.09-105)
	* arm-xilinx-eabi-gcc 4.7.2
	* arm-xilinx-eabi-as 2.23.51 
	* arm-xilinx-eabi-ld 2.23.51 
	* arm-xilinx-eabi-objcopy 2.23.51 


Build & Compile
------------

Compiling information comming soon ...


Demonstration
------------

Demo information comming soon ...


References
------------

 1. Sandro Pinto, Jorge Pereira, Tiago Gomes, Adriano Tavares, and Jorge Cabral. "LTZVisor: TrustZone is the Key." In LIPIcs-Leibniz International Proceedings in Informatics, vol. 76. Schloss Dagstuhl-Leibniz-Zentrum fuer Informatik, 2017.
 
 2. Sandro Pinto, Daniel Oliveira, Jorge Pereira, Nuno Cardoso, Mongkol Ekpanyapong, Jorge Cabral, and Adriano Tavares. "Towards a lightweight embedded virtualization architecture exploiting ARM TrustZone." In Emerging Technology and Factory Automation (ETFA), IEEE, pp. 1-4., 2014.
