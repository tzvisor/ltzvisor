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
 * [ltzvisor_hw.h]
 *
 * This file contains the LTZVisor hardware-specific initialization.
 * 
 * (#) $id: ltzvisor_hw.h 10-06-2015 s_pinto & j_pereira $
 * (#) $id: ltzvisor_hw.h 17-09-2017 s_pinto (modified)$
*/

#ifndef __LTZVISOR_HW_H
#define __LTZVISOR_HW_H

#include <types.h>
#include <errno.h>
#include <printk.h>
#include <gic.h>
#include <ltzvisor.h>
#include <board.h>
#include <zynq_ttc.h>

#define ARCH		"ARMv7-A"
#define CPU		"Cortex-A9"
#define PLATFORM	"Zynq-7000"

#define LTZVISOR_MON_EXIT() {\
	asm volatile("msr cpsr_c,#(0x13 | 0x80 | 0x40)");\
	asm volatile("ldr r1,=_supervisor_stack");\
	asm volatile("add r1, r1, r0, lsl #12");\
	asm volatile("add sp, r1, #4096");\
}

/**
 * LTZVisor hardware initialization
 *
 * @param  
 *
 * @retval Return TRUE if success or False if not
 */
uint32_t ltzvisor_hw_init(void);

#endif /* __LTZVISOR_HW_H */
