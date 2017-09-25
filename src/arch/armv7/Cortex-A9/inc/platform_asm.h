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
 * [platform_asm.h]
 *
 * This file contains CortexA9-specific register definitions.
 * 
 * (#) $id: platform_asm.h 01-01-2015 s_pinto & j_pereira $
*/

#ifndef __PLATFORM_ASM
#define __PLATFORM_ASM

#define  NSACR_REG_VAL		0x60C00
#define  CPACR_REG_VAL		0xF00000

#define	CACHE_LEVEL1_SET	1
#define	CACHE_LEVEL2_SET	0

/*	
 * LEVEL 1 Configuration 
 * 32KB, NumSets = 256, Ways=4,
 * Line Size = 5 (log2 line_len) and Line len = 32 bytes
 */
#define MAX_L1_CACHE_WAYS	3   	/* Ways -1 */
#define MAX_L1_SETS		255 	/* NumSets -1 */
#define MAX_L1_LINE_LEN		5

#define MAX_L2_CACHE_WAYS	0   	/* Ways -1 */
#define MAX_L2_SETS		0	/* NumSets -1 */
#define MAX_L2_LINE_LEN		0

#endif /* __PLATFORM_ASM */
