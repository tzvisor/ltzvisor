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
 * [cpu_cp15_switch.S]
 *
 * This file contains the CP15 coprocessor context-switch code.
 * 
 * (#) $id: cpu_cp15_switch.S 04-05-2015 s_pinto & j_pereira $
*/


/**
 * SCR_NS_Bit set (macro)
 */
.macro scr_nsbit_set rt
	mrc     p15, 0, \rt, c1, c1, 0  @ Read Secure Configuration Register
	orr	\rt, \rt, #1
	mcr     p15, 0, \rt, c1, c1, 0  @ Write Secure Configuration Register
.endm

/**
 * SCR_NS_Bit clear (macro)
 */
.macro scr_nsbit_clear rt
	mrc     p15, 0, \rt, c1, c1, 0  @ Read Secure Configuration Register
	bic	\rt, \rt, #1
	mcr     p15, 0, \rt, c1, c1, 0  @ Write Secure Configuration Register
.endm

/**
 * CP15 save context (macro)
 *
 * @param	r0 - cp15 context pointer  
 *
 * @retval 
 */
.macro save_cp15_context
	mrc	p15, 2, r2, c0, c0, 0 /* CSSELR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c1, c0, 0 /* SCTLR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c1, c0, 1 /* ACTLR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c2, c0, 0 /* TTBR0 */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c2, c0, 1 /* TTBR1 */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c2, c0, 2 /* TTBCR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c3, c0, 0 /* DACR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c5, c0, 0 /* DFSR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c5, c0, 1 /* IFSR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c6, c0, 0 /* DFAR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c6, c0, 2 /* IFAR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c7, c4, 0 /* PAR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c10, c2, 0 /* PRRR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c10, c2, 1 /* NMRR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c12, c0, 0 /* VBAR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c13, c0, 0 /* FCSEIDR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c13, c0, 1 /* CONTEXTIDR */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c13, c0, 2 /* TPIDRURW */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c13, c0, 3 /* TPIDRURO */
	str	r2, [r0], #4
	mrc	p15, 0, r2, c13, c0, 4 /* TPIDRPRW */
	str	r2, [r0], #4
.endm

/**
 * CP15 restore context (macro)
 *
 * @param	r0 - cp15 context pointer 
 *
 * @retval 
 */
.macro restore_cp15_context
	ldr	r2, [r0], #4
	mcr	p15, 2, r2, c0, c0, 0 /* CSSELR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c1, c0, 0 /* SCTLR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c1, c0, 1 /* ACTLR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c2, c0, 0 /* TTBR0 */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c2, c0, 1 /* TTBR1 */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c2, c0, 2 /* TTBCR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c3, c0, 0 /* DACR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c5, c0, 0 /* DFSR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c5, c0, 1 /* IFSR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c6, c0, 0 /* DFAR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c6, c0, 2 /* IFAR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c7, c4, 0 /* PAR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c10, c2, 0 /* PRRR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c10, c2, 1 /* NMRR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c12, c0, 0 /* VBAR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c13, c0, 0 /* FCSEIDR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c13, c0, 1 /* CONTEXTIDR */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c13, c0, 2 /* TPIDRURW */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c13, c0, 3 /* TPIDRURO */
	ldr	r2, [r0], #4
	mcr	p15, 0, r2, c13, c0, 4 /* TPIDRPRW */
.endm

/**
 * CP15 restore context
 *
 * @param	r0 - cp15 context pointer
 *
 * @retval 
 */
.global cp15_restore
.func cp15_restore
	@ void cp15_restore(struct cp15_regs * p_cp15_context);
cp15_restore:
	@ Move to NS
	scr_nsbit_set r2
	@ restore c15 context
	restore_cp15_context
	@ Move back to secure
	scr_nsbit_clear r2
	bx	lr
.endfunc
