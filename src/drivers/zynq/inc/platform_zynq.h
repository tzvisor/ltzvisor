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
 * [platform_zynq.h]
 *
 * This file contains board-specific register definitions (header).
 * 
 * (#) $id: platform_zynq.h 15-10-2015 s_pinto & j_pereira $
 * (#) $id: platform_zynq.h 20-09-2017 s_pinto (modified)$
*/

#ifndef __PLATF_ZYNQ_H
#define __PLATF_ZYNQ_H

#define XSCU_BASE 	0xF8F00000

#define GICC_OFFSET	0x0100
#define GICD_OFFSET	0x1000
#define MPIC_BASE	(XSCU_BASE + GICC_OFFSET)
#define MPID_BASE	(XSCU_BASE + GICD_OFFSET)

#define MPTW_BASE	(XSCU_BASE + 0x0600)

#define UART_BASE_0 	0xE0000000
#define UART_BASE_1 	0xE0001000

#define TTC0_BASE	0xF8001000
#define TTC1_BASE 	0xF8002000

#endif /* __PLATF_ZYNQ_H */
