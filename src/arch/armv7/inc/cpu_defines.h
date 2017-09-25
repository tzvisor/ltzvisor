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
 * [cpu_defines.h]
 *
 * This file contains ARMv7-specific register definitions.
 * 
 * (#) $id: cpu_defines.h 03-05-2015 s_pinto & j_pereira $
*/

#ifndef __ARMV7_CPU_DEFINES_H__
#define __ARMV7_CPU_DEFINES_H__

/** CPU Operation Modes */
#define  USER_MODE		0x10
#define  FIQ_MODE		0x11
#define  IRQ_MODE		0x12
#define  SUPERVISOR_MODE	0x13
#define  MONITOR_MODE		0x16
#define  ABORT_MODE   		0x17
#define  HYPERVISOR_MODE   	0x1A	// Not Used
#define  UNDEFINED_MODE		0x1B
#define  SYSTEM_MODE		0x1F

/** CPSR FIQ & IRQ Bits*/
#define	FIQ_BIT          	0x40
#define	IRQ_BIT          	0x80

#define STACK_SIZE 8192 
#define STACK_SIZE_SHIFT 12 

/** SCR Bits*/
#define  SCR_NS_BIT     	0x1
#define  SCR_FIQ_BIT        	0x4
#define  SCR_IRQ_BIT        	0x2
#define  SCR_HCR_BIT		0x100

/** SCTLR Bits*/
#define	SCTLR_MMU_BIT		0x1
#define SCTLR_DCACHE_BIT	(1 << 2)
#define SCTLR_BRANCH_PRED_BIT	(1 << 11)
#define SCTLR_ICACHE_BIT	(1 << 12)

#define AUXREG_SMP         	0x41
#define AUXREG_UP		0x0

#endif /* __ARMV7_CPU_DEFINES_H__ */
