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
 * [printk.c]
 *
 * This file contains PRINTK implementation.
 * 
 * (#) $id: printk.c 01-09-2015 s_pinto & j_pereira $
 * (#) $id: printk.c 18-09-2017 s_pinto (modified)$
*/
#include <printk.h>

uint32_t vsprintk(char *buf, const char *fmt, va_list args){

	char *str;
	str = buf;
	uint32_t len = strnlen(buf,PRINT_TEXT_LEN);
	for(; *fmt ; ++fmt){
		if((*fmt != '%') && (*fmt != '\n') && (*fmt != '\t')){
			*str++ = *fmt;
			continue;
		}

		if(*fmt == '%'){
			/* skip % */
			++fmt;
			uint32_t is_unsigned = 0;
			uint32_t zero_padding = 1;

			if(*fmt == '0'){
				/* zero padding!*/
				/* skip 0 */
				++fmt;
				zero_padding = *fmt++;
				if((zero_padding < 0x31) || (zero_padding > 0x38)){
					/* serial_puts("invalid padding bits.\0"); */
				}
				zero_padding -= 0x30;
			}

			switch(*fmt){
				case 'l':
					{
						++fmt;
						break;
					}
			}

			switch(*fmt){
				case 'x':
					{
						uint32_t number = va_arg(args, int);
						int length = 8;
						int length_in_bits = 32;
						int byte = 0;
						int i = 0;
						uint8_t keep_zeros = FALSE;

						for(i = 0; i < length; i++){
							byte = number >> (length_in_bits - ((i+1) * 4));
							byte = byte & 0xF;
							if(byte != 0){
								keep_zeros = TRUE;
							}
							if(keep_zeros || i >= (7-(zero_padding-1))){
								if((byte >= 0) && (byte <= 9)){
									byte = byte + 0x30;
								}
								else{
									switch(byte){
										case 0xa:
											byte = 0x61;
											break;
										case 0xb:
											byte = 0x62;
											break;
										case 0xc:
											byte = 0x63;
											break;
										case 0xd:
											byte = 0x64;
											break;
										case 0xe:
											byte = 0x65;
											break;
										case 0xf:
											byte = 0x66;
											break;
									} /* switch ends */
								} /* else ends */
								*str++ = byte;
							}
						} /* for ends - whole number is now done */
						break;
					}
				case 'u':
					is_unsigned = 1;
				case 'i':
				case 'd':
					{
						uint32_t i,j,max_num_zeros,num_of_digits_uint32_t,
								number_uint32_t,divisor_value_uint32_t,
								new_div_val = 1,sw_quotient_value = 0;
						uint8_t keep_zeros = FALSE;

						if(!is_unsigned){
							int signed_num_32 = va_arg(args,int);
							if(signed_num_32 < 0){
								*str++ = 0x2d;
								signed_num_32 = -(signed_num_32);
							}
							number_uint32_t = (uint32_t)signed_num_32;
						}
						else{
							uint32_t unsigned_value_32 = va_arg(args,
									unsigned int);
							number_uint32_t = unsigned_value_32;
						}

						divisor_value_uint32_t = 1000000000;
						num_of_digits_uint32_t = 10;
						max_num_zeros = num_of_digits_uint32_t - 1;

						for(i = 0; i < max_num_zeros; i++){
							while(number_uint32_t >= divisor_value_uint32_t){
								number_uint32_t -= divisor_value_uint32_t;
								++sw_quotient_value;
							}
							if(sw_quotient_value != 0)
								keep_zeros = TRUE;
							if(keep_zeros || i > ((max_num_zeros-1)-
										(zero_padding-1))){
								sw_quotient_value += 0x30;
								*str++ = sw_quotient_value;
							}
							j = i;
							while(j < (max_num_zeros-1)){
								new_div_val *= 10;
								j++;
							}
							sw_quotient_value = 0;
							divisor_value_uint32_t = new_div_val;
							new_div_val = 1;
						}
						*str++ = (number_uint32_t + 0x30);
						break;
					}
				case 'o':
					{
						uint32_t number,length = 10,length_in_bits = 32,
								byte = 0,i = 0;
						uint8_t keep_zeros = FALSE;

						number = va_arg(args, int);
						byte = number >> 30;
						byte &= 0x3;
						if(byte != 0){
							keep_zeros = TRUE;
						}
						if(keep_zeros || zero_padding > length){
							byte = byte + 0x30;
							*str++ = byte;
						}

						number <<= 2;
						for(i = 0; i < length; i++){
							byte = number >> (length_in_bits - ((i+1) * 3));
							byte &= 0x7;
							if(byte != 0){
								keep_zeros = TRUE;
							}
							if(keep_zeros || i >= (9-(zero_padding-1))){
								byte = byte + 0x30;
								*str++ = byte;
							}
						}
						break;
					}
				case 's':
					{
						char *arg_string = va_arg(args, char *);
						while(((*str = *arg_string++ ) &&
									(len < PRINT_TEXT_LEN))){
							++str;
							len++;
						}
						break;
					}
				case 'c':
					{
						char character = va_arg(args, char);
						*str++ = character;
						break;
					}
				case '%':
					{
						*str++ = *fmt;
						break;
					}
				case '\t':
					{
						*str++ = '%';
						*str++ = *fmt;
						break;
					}
				case '\n':
					{
						*str++ = '%';
						*str++ = '\r';
						*str++ = '\n';
						break;
					}
				default:
					{

					}
			} /* switch ends             */
		} /* if % character found      */

		if(*fmt == '\n'){
			*str++ = '\r';
			*str++ = '\n';
		}
		if(*fmt == '\t')
			*str++ = *fmt;
	} /* for ends */
	*str = '\0';
	return strnlen(buf,PRINT_TEXT_LEN);
}

uint32_t printk(const char *fmt, ...){

	va_list args;
	uint32_t i;
	char print_buffer[256];
	va_start(args, fmt);

	i = vsprintk(print_buffer, fmt, args);
	va_end(args);

	/* Print the string */
	serial_puts(print_buffer);
	return i;
}
