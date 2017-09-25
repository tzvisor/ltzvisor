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
 * [string.c]
 *
 * This file contains string library related code.
 * 
 * (#) $id: string.c 04-07-2015 s_pinto & j_pereira $
 * (#) $id: string.c 16-09-2017 s_pinto (modified)$
*/

#include <string.h>

/**
 * Copy block of memory
 *
 * @param	dst = pointer to the destination array 
 *		src = pointer to the source of data to be copied 
 *		count = number of bytes to copy
 *
 * @retval  destination is returned
 */
void * memcpy(void * dst, const void * src, uint32_t count)
{
	int32_t i;
	char_t *dst_tmp = dst;
	const char_t *src_tmp = src;

	if (!((uint32_t)src & 0x3) && !((uint32_t)dst & 0x3)){
		/** Word aligned - safe word copies */
		for (i=0; i < count; i+=4){
			if (i + 3 > count - 1)
				break; /* Don't copy too much */
			*(uint32_t *)dst_tmp = *(uint32_t *)src_tmp;
			dst_tmp += 4;
			src_tmp += 4;
		}
		if (i <= count - 1){
			for (; i < count; i++){
				*dst_tmp = *src_tmp;
				dst_tmp++;
				src_tmp++;
			}
		}
	}
	else{
		/* Generic version */
		for (i=0; i < count; i++)
			dst_tmp[i] = src_tmp[i];
	}
	return dst;
}

/**
 * Fill block of memory
 *
 * @param	dst = pointer to the block of memory
 *		c = value to be set
 *		count = number of bytes to be set
 *
 * @retval  pointer to the block of memory is returned
 */
void *memset(void * dest, uint32_t c, uint32_t count)
{
	/** Standard bytewise memset */
	char_t* d;
	d = (char_t*) dest;

	while(count--){
		*d = c;
		d++;
	}

	return dest;
}

/**
 * Concatenate strings
 *
 * @param	dest = pointer to the destination array
 *		src = C string to be appended
 *
 * @retval  destination is returned
 */
char_t * strcat(char_t *dest, cchar_t *src)
{
	char_t *save = dest;

	for (; *dest; ++dest) ;
	while ((*dest++ = *src++) != 0) ;

	return (save);
}

/**
 * Get string length
 *
 * @param	s = C string
 *
 * @retval  The length of string
 */
uint32_t strlen(char_t * s){

	char_t *sc;
	for (sc = s; *sc != '\0'; ++sc){
		/* Do nothing */
	}
	return sc - s;
}

/**
 * Get fixed-size string length
 *
 * @param	S = C string
 *		n = lsize
 *
 * @retval  The length of string
 */
uint32_t strnlen(char_t * s, size_t n){
	char_t *str;

	for(str = s; *str != '\0' && n-- ; ++str){
		/* Do nothing */
	}
	return str-s;
}

/**
 * Copy string
 *
 * @param	dest = pointer to the destination array
 *		src = C string to be copied
 *
 * @retval  destination is returned
 */
char_t * strcpy(char_t * dest, char_t * src)
{
	char_t *tmp = dest;

	while ((*dest++ = *src++) != '\0'){
		/* Do nothing */
	}
	return tmp;
}

