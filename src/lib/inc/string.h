/*
 * LTZVisor, a Lightweight TrustZone-assisted Hypervisor
 *
 * Copyright (c) TZVisor Project (www.tzvisor.org), 2017-
 *
 * Authors:
 *  Sandro Pinto <sandro@tzvisor.org>
 *  Jorge Pereira <jorgepereira89@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of 
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301 USA.
 *
 * [string.h]
 *
 * This file contains string library related code (header).
 * 
 * (#) $id: string.h 04-07-2015 s_pinto & j_pereira $
 * (#) $id: string.h 16-09-2017 s_pinto (modified)$
*/

#ifndef __STRING_H_
#define __STRING_H_

#include <types.h>

/**
 * Copy block of memory
 *
 * @param	dst = pointer to the destination array 
 *		src = pointer to the source of data to be copied 
 *		count = number of bytes to copy
 *
 * @retval  destination is returned
 */
void *memcpy(void *dst, const void *src, uint32_t count);

/**
 * Fill block of memory
 *
 * @param	dst = pointer to the block of memory
 *		c = value to be set
 *		count = number of bytes to be set
 *
 * @retval  pointer to the block of memory is returned
 */
void *memset(void * dest, uint32_t c, uint32_t count);

/**
 * Concatenate strings
 *
 * @param	dest = pointer to the destination array
 *		src = C string to be appended
 *
 * @retval  destination is returned
 */
char_t * strcat(char_t *dest, cchar_t *src);


/**
 * Get string length
 *
 * @param	s = C string
 *
 * @retval  The length of string
 */
uint32_t strlen(char_t * s);

/**
 * Get fixed-size string length
 *
 * @param	S = C string
 *		n = lsize
 *
 * @retval  The length of string
 */
uint32_t strnlen(char_t * s, size_t n);

/**
 * Copy string
 *
 * @param	dest = pointer to the destination array
 *		src = C string to be copied
 *
 * @retval  destination is returned
 */
char_t * strcpy(char_t * dest, char_t * src);

#endif /* __STRING_H_ */
