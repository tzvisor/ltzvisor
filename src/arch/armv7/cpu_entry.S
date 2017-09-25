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
 * [cpu_entry.S]
 *
 * This file contains ARMv7-A specific boot code.
 * 
 * (#) $id: cpu_entry.S 03-05-2015 s_pinto & j_pereira $
 * (#) $id: cpu_entry.S 16-09-2017 s_pinto (modified)$
*/

#include <cpu_defines.h>
#include <asm-offsets.h>
#include <platform_asm.h>

.text

.globl _reset_handler
_reset_handler:

	/** Run CPU0 and stuck other CPUs */
	bl	get_cpu_id
	cmp	r0, #0		@ CPU0?
	bne	__stuck_loop

__start_secure_core:

	/** Set CPU State */
__setup_CPU:
	/* Set SCTLR */
	mrc	p15, 0, r1, c1, c0, 0			@ Read SCTLR 
	bic	r1, r1, #0x10000000			@ Clear TEX bit
	bic	r1, r1, #0x00002000			@ Clear Vectors bit 
	mcr	p15, 0, r1, c1, c0, 0			@ Write SCTLR 
	/* Set NSACR */
	mrc	p15, 0, r1, c1, c1, 2			@ Read NSACR 
	ldr	r2, =NSACR_REG_VAL			
	orr	r1, r1, r2				@ Mask r1 with r2
	mcr	p15, 0, r1, c1, c1, 2			@ Write NSACR 
	/* Non-Route FIQs Monitor */
	mrc	p15, 0, r1, c1, c1, 0			@ Read SCR 
	bic  	r1, r1, #SCR_FIQ_BIT			@ Clear FIQ bit (disable route FIQs monitor)
	mcr	p15, 0, r1, c1, c1, 0			@ Write SCR 
	/* Set Auxiliary register reset value */
	mrc	p15, 0, r0, c1, c0, 1			@ Read ACTLR
	ldr  	r0, =0x00				@ Clear registers
	mcr	p15, 0, r0, c1, c0, 1			@ Write ACTLR

	/** Set secure vector table (VBAR) */
	ldr	r0, =_secure_vector_table		@ Read the Secure Vector Table's Base Address
	mcr	p15, 0, r0, c12, c0, 0			@ Write VBAR

	/** Set monitor vector table (VBAR) */
	ldr	r0, =_monitor_vector_table		@ Read the Monitor Vector Table's Base Address
	mcr	p15, 0, r0, c12, c0, 1			@ Write MVBAR


	/** Setup Stacks for all CPU modes */
__setup_stacks:
	/* Get CPU id*/
	bl	get_cpu_id
	/* FIQ mode */
	msr	cpsr_c,#(FIQ_MODE | IRQ_BIT | FIQ_BIT)		@ Change CPSR to Fiq MODE and disable FIQ and IRQ
	ldr	r1,=_fiq_stack				
	add	r1, r1, r0, lsl #STACK_SIZE_SHIFT	
	add	sp, r1, #STACK_SIZE			
	/* ABORT mode */
	msr	cpsr_c,#(ABORT_MODE | IRQ_BIT | FIQ_BIT)	@ Change CPSR to Abort MODE and disable FIQ and IRQ 
	ldr	r1,=_abort_stack				
	add	r1, r1, r0, lsl #STACK_SIZE_SHIFT		
	add	sp, r1, #STACK_SIZE				
	/* UNDEFINED mode */
	msr	cpsr_c,#(UNDEFINED_MODE | IRQ_BIT | FIQ_BIT)	@ Change CPSR to Undefined MODE and disable FIQ and IRQ
	ldr	r1,=_undefined_stack				
	add	r1, r1, r0, lsl #STACK_SIZE_SHIFT		
	add	sp, r1, #STACK_SIZE				
	/* SYSTEM mode */
	msr	cpsr_c,#(SYSTEM_MODE | IRQ_BIT | FIQ_BIT)	@ Change CPSR to System MODE and disable FIQ and IRQ interrupts
	ldr	r1,=_user_stack
	add	r1, r1, r0, lsl #STACK_SIZE_SHIFT
	add	sp, r1, #STACK_SIZE
	/* MONITOR mode */
	msr	cpsr_c,#(MONITOR_MODE | IRQ_BIT | FIQ_BIT)	@ Change CPSR to Monitor MODE and disable only IRQ interrupts
	ldr	r1,=_monitor_stack				
	add	r1, r1, r0, lsl #STACK_SIZE_SHIFT		
	add	sp, r1, #STACK_SIZE				
	

	/** Handling cache and MMU subsystems */
__init_vmemory:	
	/* Disable MMU */
	mrc 	p15, 0, r1, c1, c0, 0			@ Read SCTLR register
	bic 	r1, r1, #SCTLR_MMU_BIT			@ Clear M bit (disable MMU)
	mcr 	p15, 0, r1, c1, c0, 0			@ Write SCTLR register
	/* Disable L1 Caches */
	mrc 	p15, 0, r1, c1, c0, 0			@ Read SCTLR register
	bic 	r1, r1, #SCTLR_DCACHE_BIT		@ Clear C bit (disable D-Cache)
	bic 	r1, r1, #SCTLR_ICACHE_BIT		@ Clear I bit (disable I-Cache)
	mcr 	p15, 0, r1, c1, c0, 0			@ Write SCTLR register
	/* Invalidate Instruction cache */
	mov 	r1,#0					
	mcr 	p15, 0, r1, c7, c5, 0			@ Instruction Cache Invalidate All
	/* Invalidate Data caches */
	@mov	r0, #1					
	@bl	data_cache_clean_invalidate_all		@ Invalidate data cache
	/* Invalidate Branch Predictor arrays */
	mov 	r1,#0					
	mcr	p15, 0, r1, c7, c5, 6			@ Invalidate BP
	/* Invalidate TLBs */
	mov 	r1, #0x0				
	mcr 	p15, 0, r1, c8, c3, 0			@ Invalidate entire unified TLB Inner Shareable


	/** Handling VFP and NEON */
__init_vfp:
	/* FIX IT */
	

	/** Initializing C environment */
__init_c_env:
	bl	c_environment_init


	/**  Call Main */
__call_main:
//.globl cpu_init
	//bl	cpu_init				@@@ Jump to Operating System 'c' entry function
.globl ltzvisor_main
	bl	ltzvisor_main				@ Jump to LTZVisor entry function
	/* This point should never be reached */
	b	.


/**
 * Stuck other CPUs than CPU0
 *
 * @param
 *
 * @retval 
 */
__stuck_loop:
	b	__stuck_loop

/**
 * Get CPU id
 *
 * @param	
 *
 * @retval 	r0 - CPU id
 */
.global get_cpu_id
.func get_cpu_id
  @ uint32_t get_cpu_id(void)
get_cpu_id:
	mrc	p15, 0, r0, c0, c0, 5
	and	r0, r0, #0x03
	bx	lr
.endfunc

/**
 * Initializing C environment
 *
 * @param	
 *
 * @retval 	
 */
.globl c_environment_init
c_environment_init:
	/* bss initialization (zeros) */
	ldr	r1, =_SW_BSS_START
	ldr	r2, =_SW_BSS_END
	mov	r0, #0
2:
	cmp	r1, r2
	bgt	1f
	str	r0,	[r1], #4
	b	2b
1:
	mov		pc, lr

