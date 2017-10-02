/*
 * LTZVisor, a Lightweight TrustZone-assisted Hypervisor
 *
 * Copyright (c) TZVisor Project (www.tzvisor.org), 2017-
 *
 * Authors:
 *  Sandro Pinto <sandro@tzvisor.org>
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
 * [blink.c]
 *
 * This file contains a bare-metal Blink application.
 * 
 * (#) $id: blink.c 27-09-2017 s_pinto$
*/

#include<hw_zynq.h>
#include<printk.h>

void led_blink( void * pvParameters );

int main() {

	/** Initialize hardware */
	hw_init();

	printk(" * Secure bare metal VM: running ... \n\t");

	/** Generate tick every 1s */
	tick_set(1000000);

	/* Calling Blinking Task (LED blink at 1s) */
	led_blink((void*)0);

	/* This point will never be reached */
	for( ;; );

}

/**
 * Blink LED "Task"
 *
 * @param  	
 *
 * @retval 	
 */
void led_blink( void * parameters ){

	static uint32_t toggle;
	/** 4GPIO (LED) in FPGA fabric */
	static uint32_t *ptr = (uint32_t *) 0x41200000;

	for( ;; ){
		toggle ^=0xFF;
		*ptr = toggle;
		YIELD()
	}
}
