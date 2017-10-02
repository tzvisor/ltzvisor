/*
 * LTZVisor, a Lightweight TrustZone-assisted Hypervisor
 *
 * Copyright (c) TZVisor Project (www.tzvisor.org), 2017-
 *
 * Authors:
 *  Sandro Pinto <sandro@tzvisor.org>
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
 * [s_handlers.S]
 *
 * This file contains the secure vector table.
 * 
 * (#) $id: s_handlers.S 27-09-2017 s_pinto$
*/

 #include <ltzvisor_syscall_asm.h>

/**
 * Secure vector table 
 *
 * @param
 *
 * @retval	 
 */
.align 8
.globl _secure_vector_table
	/** Monitor Vector Table definition */
_secure_vector_table:
	b	.				@ Reset exception handler
	b	 _undefined_entry		@ Undefined exception handler
	b	.				@ SVC exception handler
	b	_prefetch_entry			@ Prefetch Abort exception handler
	b	_low_level_abt			@ Data Abort exception handler
	nop	  				@ Placeholder for address exception vector
	b     	.				@ IRQ exception handler -not used
	ldr   	pc, _fiq			@ FIQ exception handler

.globl sFIQ_handler
_fiq:     
	.word 	sFIQ_handler

_undefined_entry:
	b	.	@ Stuck (FIXME)

_prefetch_entry:
	b	.	@ Stuck (FIXME)

_low_level_abt:
	b	.	@ Stuck (FIXME)


.global yield
yield:
	/* Explicit hypercall */
	ldr	r0,=LTZVISOR_SCHED_SYSCALL
	smc 	0
	bx 	lr


