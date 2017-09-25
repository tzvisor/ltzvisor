/*
 * LTZVisor, a Lightweight TrustZone-assisted Hypervisor
 *
 * Copyright (c) TZVisor Project (www.tzvisor.org), 2017-
 *
 * Authors:
 *  Sandro Pinto <sandro@tzvisor.org>
 *  Jorge Pereira <jorgepereira89@gmail.com>
 *
 * This file is part of LTZVisor.
 *
 * LTZVisor is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation, with a special   
 * exception described below.
 * 
 * Linking this code statically or dynamically with other modules 
 * is making a combined work based on this code. Thus, the terms 
 * and conditions of the GNU General Public License V2 cover the 
 * whole combination.
 *
 * As a special exception, the copyright holders of LTZVisor give  
 * you permission to link LTZVisor with independent modules to  
 * produce a statically linked executable, regardless of the license 
 * terms of these independent modules, and to copy and distribute  
 * the resulting executable under terms of your choice, provided that 
 * you also meet, for each linked independent module, the terms and 
 * conditions of the license of that module. An independent module  
 * is a module which is not derived from or based on LTZVisor.
 *
 * LTZVisor is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 *
 * [gic.h]
 *
 * This file contains the GIC driver implementation (header).
 * 
 * (#) $id: gic.h 10-05-2015 s_pinto$
 * (#) $id: gic.h 19-09-2017 s_pinto (modified)$
*/

#ifndef __GIC_H
#define __GIC_H

#include <types.h>
#include <cpu_vcpu.h>
#include <platform_zynq.h>

/** GIC generic registers and values definition */
#define SPURIOUS_INTERRUPT			1023
#define NO_OF_INTERRUPTS_IMPLEMENTED 		96
#define GIC_NUM_REGISTERS 			NO_OF_INTERRUPTS_IMPLEMENTED/32
#define GIC_PRIORITY_REGISTERS			24
#define GIC_TARGET_REGISTERS			24
#define GIC_CONFIG_REGISTERS			6
#define GIC_SPI_STATUS_REGISTERS		2
#define GIC_PERIPHERAL_ID			4
#define GIC_COMPONENT_ID			4
#define INTERRUPT_MASK     			0x000003FF
#define IPI_MASK           			0x0000000F
#define CPUID_MASK         			0x00000C00
#define BINARY_POINT_MASK  			0x00000007
#define PRIORITY_MASK_MASK 			0x000000F0
#define CPUID_SHIFT        			10
#define PRIORITY_SHIFT      			4
#define IPI_TARGET_SHIFT   			16
#define IPI_TARGET_FILTER_SHIFT 		24
#define USE_TARGET_LIST   			0x0
#define ALL_BUT_SELF      			0x1
#define SELF              			0x2
#define GIC_ACK_INTID_MASK			0x3FF
#define FAKE_INTERRUPT 				1023
#define HIGHEST_PRIORITY       			0x0
#define LOWEST_PRIORITY        			0xE
#define DEFAULT_PRIORITY       			0xF
#define RESCHEDULE_PRIORITY    			LOWEST_PRIORITY

/** GIC Reserved address space (size expressed in 32 bit words) */
#define GIC_RESERVED_BEFORE_SECURITY		0x1D
#define GIC_RESERVED_BEFORE_SET_ENABLE		0x1D
#define GIC_RESERVED_BEFORE_CLEAR_ENABLE	0x1D
#define GIC_RESERVED_BEFORE_SET_PENDING		0x1D
#define GIC_RESERVED_BEFORE_CLEAR_PENDING	0x1D
#define GIC_RESERVED_BEFORE_ACTIVE_BIT		0x1D
#define GIC_RESERVED_BEFORE_PRIORITY		0x3D
#define GIC_RESERVED_BEFORE_TARGET		0xE8
#define GIC_RESERVED_BEFORE_CONFIG		0xE8
#define GIC_RESERVED_BEFORE_PPI_STATUS		0x3A
#define GIC_RESERVED_BEFORE_SGI			0x7D
#define GIC_RESERVED_BEFORE_IDENTIFICATION	0x33
#define GIC_INT_RESERVED_BEFORE_CPUINTID	0x37

/** Inter Processor Interrupts IDs */
#define IPI_0      				0 		
#define IPI_1      				1 		
#define IPI_2      				2 	
#define IPI_3      				3 	
#define IPI_4     				4 	
#define IPI_5      				5 	
#define IPI_6      				6 	
#define IPI_7      				7 	
#define IPI_8      				8 
#define IPI_9      				9 
#define IPI_10    				10 
#define IPI_11    				11 
#define IPI_12    				12 
#define IPI_13    				13 
#define IPI_14    				14 
#define IPI_15    				15 

/** Generic */
#define SET           				1
#define UNSET         				0
#define ENABLE        				1
#define DISABLE       				0

/** Critical sections Macros */
#define INTERRUPT_CRITICAL_ENTRY(){\
	cpu_inter->ICCPMR = 0x00;\
}

#define INTERRUPT_CRITICAL_EXIT(){\
	cpu_inter->ICCPMR = 0xF0;\
}

/** */
typedef enum
{
	Int_S = 0x00, 
	Int_NS = 0x01
}IntSecurity_TypeDef;						

/** GIC Distributor register structure */
typedef struct{
	/* Distributor Control Register (R/W) */
	uint32_t ICDDCR;
	/* Interrupt Controller Type Register (RO) */
	volatile uint32_t const ICDICTR;
	/* Distributor Implementer Identification Register (RO) */				
	volatile uint32_t const ICDIIDR; 
		/* Reserved : 29(0x1D) bytes */				
	const uint32_t reserved1[GIC_RESERVED_BEFORE_SECURITY]; 
	/* Interrupt Security Registers (R/W) */		
	volatile uint32_t ICDISRx[GIC_NUM_REGISTERS]; 	
		/* Reserved : 29(0x1D) bytes */		
	const uint32_t reserved2[GIC_RESERVED_BEFORE_SET_ENABLE];
	/* Interrupt Set-Enable Registers (R/W) */		
	volatile uint32_t ICDISERx[GIC_NUM_REGISTERS]; 	
		/* Reserved : 29(0x1D) bytes */		
	const uint32_t reserved3[GIC_RESERVED_BEFORE_CLEAR_ENABLE];
	/* Interrupt Clear-Enable Registers (R/W) */		
	volatile uint32_t ICDICERx[GIC_NUM_REGISTERS];	
		/* Reserved : 29(0x1D) bytes */		
	const uint32_t reserved4[GIC_RESERVED_BEFORE_SET_PENDING]; 
	/* Interrupt Set-Pending Registers (R/W) */		
	volatile uint32_t ICDISPRx[GIC_NUM_REGISTERS]; 	
		/* Reserved : 29(0x1D) bytes */		
	const uint32_t reserved5[GIC_RESERVED_BEFORE_CLEAR_PENDING]; 
	/* Interrupt Clear-Pending Registers (R/W) */		
	volatile uint32_t ICDICPRx[GIC_NUM_REGISTERS]; 	
		/* Reserved : 29(0x1D) bytes */		
	const uint32_t reserved6[GIC_RESERVED_BEFORE_ACTIVE_BIT]; 
	/* Active Bit Registers (R/W) */		
	volatile uint32_t ICDABRx[GIC_NUM_REGISTERS]; 	
		/* Reserved : 61(0x3D) bytes */		
	const uint32_t reserved7[GIC_RESERVED_BEFORE_PRIORITY]; 
	/* Interrupt Priority Registers (R/W) */		
	volatile uint32_t ICDIPRx[GIC_PRIORITY_REGISTERS]; 
		/* Reserved : 232(0xE8) bytes */		
	const uint32_t reserved8[GIC_RESERVED_BEFORE_TARGET]; 
	/* Interrupt Processor Target Registers (R/W) */			
	volatile uint32_t ICDIPTRx[GIC_TARGET_REGISTERS]; 
		/* Reserved : 232(0xE8) bytes */		
	const uint32_t reserved9[GIC_RESERVED_BEFORE_CONFIG]; 
	/* Interrupt Configuration Registers (R/W) */			
	volatile uint32_t ICDICFRx[GIC_CONFIG_REGISTERS]; 
		/* Reserved : 58(0x3A) bytes */		
	const uint32_t reserved10[GIC_RESERVED_BEFORE_PPI_STATUS]; 
	/* PPI Status Register (RO) */		
	volatile uint32_t const PPI_STATUS; 
	/* SPI Status Registers (RO) */				
	volatile uint32_t const SPI_STATUS[GIC_SPI_STATUS_REGISTERS]; 
		/* Reserved : 125(0x7D) bytes */
	const uint32_t reserved11[GIC_RESERVED_BEFORE_SGI]; 
	/* Software Generated Interrupt Register (R/W) */			
	volatile uint32_t ICDSGIR; 	
		/* Reserved : 51(0x33) bytes */				
	const uint32_t reserved12[GIC_RESERVED_BEFORE_IDENTIFICATION];	
	/* Peripheral Identification Registers [4:7] (RW) */	
	volatile uint32_t ICPIDR_4_7[GIC_PERIPHERAL_ID];
	/* Peripheral Identification Registers [0:3] (RW) */ 		
	volatile uint32_t ICPIDR_0_3[GIC_PERIPHERAL_ID]; 
	/* Component Identification Registers (RW) */		
	volatile uint32_t ICCIDRx[GIC_COMPONENT_ID]; 			
} Interrupt_Distributor;

/** GIC CPU Interface register structure */
typedef struct
{
	/* CPU Interface Control Register (R/W) */
	volatile uint32_t ICCICR; 
	/* Priority Mask Register (R/W) */					
	volatile uint32_t ICCPMR;
	/* Binary Point Register (R/W) */ 					
	volatile uint32_t ICCBPR;
	/* Interrupt Acknowledge Register (R/W) */ 					
	volatile uint32_t ICCIAR; 
	/* End of Interrupt Register (R/W) */					
	volatile uint32_t ICCEOIR; 
	/* Running Priority Register (R/W) */					
	volatile uint32_t ICCRPR; 
	/* Highest Pending Interrupt Register (R/W) */					
	volatile uint32_t ICCHPIR; 
	/* Aliased Non-secure Binary Point Register (R/W) */					
	volatile uint32_t ICCABPR; 
		/* Reserved : 55(0x37) bytes */				
	const uint32_t reserved1[GIC_INT_RESERVED_BEFORE_CPUINTID]; 	
	/* CPU Interface Implementer Identification Register (RO) */	
	volatile uint32_t const ICCIDR; 				
} Cpu_Interface;


/** Type definition of the interrupt handler */
typedef void (tHandler)(void * t);


void interrupt_install_handler(void);

/**
 * Initialize the GIC Distributor
 *
 * @param  	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t interrupt_distributor_init(void);

/**
 * Initialize the CPU Interface
 *
 * @param  	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t interrupt_interface_init(void);

/**
 * Interrupt enable/disable
 *
 * @param	interrupt = interrupt number
 *		enable = set (enable=1) or clear (enable=0)   	
 *
 * @retval	 	
 */
void interrupt_enable(uint32_t interrupt, uint32_t enable);

/**
 * Interrupt priority set
 *
 * @param	interrupt = interrupt number
 *		priority = priority value   	
 *
 * @retval	Return original priority	 	
 */
uint32_t interrupt_priority_set(uint32_t interrupt, uint32_t priority);

/**
 * Set interrupt target
 *
 * @param	interrupt = interrupt number
 *		cpu = target cpu id 
 *		set = set value  	
 *
 * @retval	 	
 */
void interrupt_target_set(uint32_t interrupt, uint32_t cpu, uint32_t set);

/**
 * Clear interrupt
 *
 * @param	interrupt = interrupt number
 *		target =  	
 *
 * @retval	 	
 */
void interrupt_clear(uint32_t interrupt, uint32_t target);

/**
 * Configure all interrupts' security
 *
 * @param	
 *
 * @retval	 	
 */
void interrupt_security_configall(void);

/**
 * Config interrupt security
 *
 * @param	interrupt = interrupt number
 * 		security = security state (NS or S)	
 *
 * @retval	 	
 */
void interrupt_security_config(uint32_t interrupt, IntSecurity_TypeDef security);

/**
 * Get number of current interrupt
 *
 * @param
 *
 * @retval	Return the number of current interrupt	 	
 */
uint32_t interrupt_number_get();


void interrupt_critical_entry();
void interrupt_critical_exit();

void scheduling_point_IPI(uint32_t id, uint32_t target);


#endif /* __GIC_H */

