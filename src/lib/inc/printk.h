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
 * [printk.h]
 *
 * This file contains PRINTK implementation (header).
 * 
 * (#) $id: printk.h 01-09-2015 s_pinto & j_pereira $
 * (#) $id: printk.h 18-09-2017 s_pinto (modified)$
*/

/**
 * @file        stdio_functions.h
 * @author      Jorge Pereira & Sandro Pinto
 * @version     1.0
 * @date        19 October, 2015
 * @brief       Stdio functions Header File
*/

#ifndef __PRINTK_H
#define __PRINTK_H

#include <types.h>
#include <string.h>
#include <zynq_uart.h>

typedef char *va_list;

#define ALIGNBND		(sizeof (signed int) - 1)

#define bnd(X, bnd)		(((sizeof (X)) + (bnd)) & (~(bnd)))

#define va_arg(ap, T)		(*(T *)(((ap) += (bnd (T, ALIGNBND))) - (bnd (T,ALIGNBND))))

#define va_end(ap)		(void) 0

#define va_start(ap, A)		(void) ((ap) = (((char *) &(A)) + (bnd (A,ALIGNBND))))

#define PRINT_TEXT_LEN         0x100

/**
 * Print formatted data to stdout
 *
 * @param	fmt = 
 *
 * @retval  
 */
uint32_t printk(const char *fmt, ...);

#endif /* __PRINTK_H */
