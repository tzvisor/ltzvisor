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
 * [gic.c]
 *
 * This file contains the GIC driver implementation.
 * 
 * (#) $id: gic.c 10-05-2015 s_pinto$
 * (#) $id: gic.c 19-09-2017 s_pinto (modified)$
*/

#include <gic.h>
#include <zynq_ttc.h>

/** Interrupt Distributor instance */
Interrupt_Distributor * int_dist = (Interrupt_Distributor *)(MPID_BASE);

/** CPU Interface instance - aliased for each CPU */
Cpu_Interface * const cpu_inter = (Cpu_Interface *)(MPIC_BASE);

/** Array of FIQ handlers */
tHandler* fiq_handlers[NO_OF_INTERRUPTS_IMPLEMENTED] = {
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, ttc_interrupt_clear, ttc_interrupt_clear, ttc_interrupt_clear, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, ttc_interrupt_clear,
	ttc_interrupt_clear, ttc_interrupt_clear, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL
};


void fiq_handler(uint32_t interrupt){
	if (fiq_handlers[interrupt])
		fiq_handlers[interrupt]((void *) interrupt);
}




/**
 * Initialize the GIC Distributor
 *
 * @param  	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t interrupt_distributor_init(void){

	uint32_t i;

	/** Check the ARM Legacy Identification Register Field values */
	if (int_dist->ICPIDR_0_3[0] != 0x90 || int_dist->ICPIDR_0_3[1] != 0xB3 ||
	    int_dist->ICPIDR_0_3[2] != 0x1B || int_dist->ICPIDR_0_3[3] != 0x00 ||
	    int_dist->ICPIDR_4_7[0] != 0x04 || int_dist->ICPIDR_4_7[1] != 0x00 ||
	    int_dist->ICPIDR_4_7[2] != 0x00 || int_dist->ICPIDR_4_7[3] != 0x00 ||
	    int_dist->ICCIDRx[0] != 0x0D || int_dist->ICCIDRx[1] != 0xF0 ||
	    int_dist->ICCIDRx[2] != 0x05 || int_dist->ICCIDRx[3] != 0xB1){

		return FALSE;
	}

	/** Disable the whole controller (S and NS) */
	int_dist->ICDDCR = 0x00000000;

	/** Disable all interrupts */
	for (i = 0; i < GIC_NUM_REGISTERS; i++){
		/* Clear-Enable */
		int_dist->ICDICERx[i] = 0xFFFFFFFF;	
	}

	/** Clear all SPI interrupts */
	for (i = 1; i < GIC_NUM_REGISTERS; i++){
		/* Clear-Pending */
		int_dist->ICDICPRx[i] = 0xFFFFFFFF;	
	}

	/** Reset SPI interrupt priorities */
	for (i = 8; i < GIC_PRIORITY_REGISTERS; i++){

		int_dist->ICDIPRx[i] = 0x00000000;
	}

	/** Reset interrupt targets */
	for (i = 0; i < GIC_TARGET_REGISTERS; i++){

		int_dist->ICDIPTRx[i] = 0x00000000;
	}

	/** Set interrupt configuration (level high sensitive, 1-N) */
	for (i = 2; i < (NO_OF_INTERRUPTS_IMPLEMENTED - 32) / 16; i++){

		int_dist->ICDICFRx[i] = 0x55555555;
	}

	/** Enable the interrupt controller (group0 and group1) */
	int_dist->ICDDCR = 0x00000003;

	return TRUE;
}


/**
 * Initialize the CPU Interface
 *
 * @param  	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t interrupt_interface_init(void){

	uint32_t i;

	/** Clear the bits of the distributor which are CPU-specific */
	/* Clear-Pending */
	int_dist->ICDICPRx[0] = 0xFFFFFFFF;			
	for (i = 0; i < 8; i++){
		/* SGI and PPI interrupt priorities */
		int_dist->ICDIPRx[i] = 0x00000000;
	}
	/* SGI and PPI set interrupt configuration */
	int_dist->ICDICFRx[0] = 0xAAAAAAAA;
	int_dist->ICDICFRx[1] = 0xAAAAAAAA;

	/** Disable CPU Interface */
	cpu_inter->ICCICR = 0x00000000;

	/** Allow interrupts with higher priority (i.e. lower number) than 0xF */
	cpu_inter->ICCPMR = 0x000000F0;

	/** All priority bits are compared for pre-emption */
	cpu_inter->ICCBPR = 0x00000003;	

	/** Clear any pending interrupts */
	for( ; ; ){

		uint32_t temp;
		/* interrupt_ack */
		temp = cpu_inter->ICCIAR;			

		if((temp & GIC_ACK_INTID_MASK) == FAKE_INTERRUPT)
		{
			break;
		}
		/* end_of_interrupt */
		cpu_inter->ICCEOIR = temp;			
	}

	/** Enable the CPU Interface */
	cpu_inter->ICCICR = 0x00000009;	

	return TRUE;
}


/**
 * Interrupt enable/disable
 *
 * @param	interrupt = interrupt number
 *		enable = set (enable=1) or clear (enable=0)   	
 *
 * @retval	 	
 */
void interrupt_enable(uint32_t interrupt, uint32_t enable){

	uint32_t word;

	/** Calculate interrupt position */
	word = interrupt / 32;
	interrupt %= 32;
	interrupt = 1 << interrupt;

	if (enable){
		/* Set */
		int_dist->ICDISERx[word] = interrupt;
	}
	else{
		/* Clear */
		int_dist->ICDICERx[word] = interrupt;
	}
}

/**
 * Interrupt priority set
 *
 * @param	interrupt = interrupt number
 *		priority = priority value   	
 *
 * @retval	Return original priority	 	
 */
uint32_t interrupt_priority_set(uint32_t interrupt, uint32_t priority){

	uint32_t word, bit_shift, temp, old_priority;

	priority &= 0xF;
	/* Get register of interrupt */
	word = interrupt / 4; 					
	bit_shift = (interrupt % 4) * 8 + 4; 			

	/* Get priority register */
	temp = old_priority = int_dist->ICDIPRx[word]; 		
	/* Reset the priority for this interrupt to 0 */
	temp &= ~((uint32_t)0xF << bit_shift); 			
	/* Set the new priority */
	temp |= (priority << bit_shift); 			
	int_dist->ICDIPRx[word] = temp; 			

	return ((old_priority >> bit_shift) & 0xF); 		
}

/**
 * Set interrupt target
 *
 * @param	interrupt = interrupt number
 *		cpu = target cpu id 
 *		set = set value  	
 *
 * @retval	 	
 */
void interrupt_target_set(uint32_t interrupt, uint32_t cpu, uint32_t set){

	uint32_t word, bit_shift, temp;

	/* Get register of interrupt */
	word = interrupt / 4;
	bit_shift = (interrupt % 4) * 8;
	cpu = (1 << cpu) << bit_shift;

	temp = int_dist->ICDIPTRx[word];
	if (set){
		/* Set */
		temp |= cpu;
	}
	else{
		/* Clear */
		temp &= ~cpu;
	}
	int_dist->ICDIPTRx[word] = temp;
}

/**
 * Clear interrupt
 *
 * @param	interrupt = interrupt number
 *		target =  	
 *
 * @retval	 	
 */
void interrupt_clear(uint32_t interrupt, uint32_t target){

	/* Clear interrupt */
	cpu_inter->ICCEOIR = ( target << 10) | interrupt;
}

/**
 * Configure all interrupts' security
 *
 * @param	
 *
 * @retval	 	
 */
void interrupt_security_configall(void){

	uint32_t num_regs;
	/* Configure all global interrupts as NS Interrupts */
	for(num_regs=1; num_regs < GIC_NUM_REGISTERS; num_regs++){
		int_dist->ICDISRx[num_regs] = 0xFFFFFFFF;
	}

}

/**
 * Config interrupt security
 *
 * @param	interrupt = interrupt number
 * 		security = security state (NS or S)	
 *
 * @retval	 	
 */
void interrupt_security_config(uint32_t interrupt, IntSecurity_TypeDef security){

	uint32_t word, temp;

	/* Calculate interrupt position in register */
	word = interrupt / 32;
	interrupt %= 32;
	interrupt = 1 << interrupt;

	temp = int_dist->ICDISRx[word];
	if (security == Int_NS){
		temp |= interrupt;
	}
	else{
		temp &= ~interrupt;
	}
	int_dist->ICDISRx[word] = temp;
}

/**
 * Get number of current interrupt
 *
 * @param
 *
 * @retval	Return the number of current interrupt	 	
 */
uint32_t interrupt_number_get() {

	return cpu_inter->ICCIAR;
}

/**
 * Enter critical section
 *
 * @param
 *
 * @retval		
 */
void interrupt_critical_entry() {
	/* Set higher priority to 0x00 */
	cpu_inter->ICCPMR = 0x00;
}

/**
 * Exit critical section
 *
 * @param
 *
 * @retval		
 */
void interrupt_critical_exit() {
	/* Set higher priority to 0xF0 */
	cpu_inter->ICCPMR = 0xF0;
}

/**
 * Generate IPI interrupt
 *
 * @param	id = IPI identifier
 *		target = target CPU
 *
 * @retval		
 */
void interrupt_IPI_generate(uint32_t id, uint32_t target){
	/* Software Generated Interrupt Register */
   	int_dist->ICDSGIR = (target << IPI_TARGET_SHIFT) | id;		
}



