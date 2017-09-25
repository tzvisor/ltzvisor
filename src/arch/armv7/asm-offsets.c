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
 * [asm_offsets.c]
 *
 * This file contains code for generating asm_offsets.h.
 * 
 * (#) $id: asm_offsets.c 03-05-2015 j_pereira $
*/


#include <types.h>
#include <ltzvisor.h>
#include <gic.h>

#define pos(a, b) ((size_t) &((a*)0)->b)
#define GEN_SYM(name, value) \
	asm volatile("\n->" #name " %0 " #value : : "j" (value))

int main(void)
{

	GEN_SYM(_ASM_CP_SCTLR_OFFSET, pos(tzmachine, core.vcpu_regs_cp15.c1_SCTLR));
	GEN_SYM(_ASM_MON_SPSR_OFFSET, pos(tzmachine, core.vcpu_regs_core.spsr_mon));
	GEN_SYM(_ASM_MON_LR_OFFSET, pos(tzmachine, core.vcpu_regs_core.lr_mon));
	GEN_SYM(_ASM_R4_OFFSET, pos(tzmachine, core.vcpu_regs_core.r4));
	GEN_SYM(_ASM_SP_OFFSET, pos(tzmachine, core.vcpu_regs_core.r13_sys));

	GEN_SYM(_ASM_ARCH_REGS_OFFSET, pos(tzmachine, core.vcpu_regs_core));

	GEN_SYM(_ASM_GIC_INT_ID, pos(Cpu_Interface, ICCIAR));

	return 0;
}

