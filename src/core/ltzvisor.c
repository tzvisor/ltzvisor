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
 * [ltzvisor.c]
 *
 * This file contains the ltzvisor main entry point.
 * 
 * (#) $id: ltzvisor.c 04-05-2015 s_pinto & j_pereira $
 * (#) $id: ltzvisor.c 16-09-2017 s_pinto (modified)$
*/

#include <ltzvisor.h>

/** Config NS_Guest struct */
extern struct nsguest_conf_entry nsguest_config;

/** NS_Guest context */
tzmachine NS_Guest __attribute__ ((aligned (4))) __attribute__ ((section (".bss")));

/**
 * LTZVisor main entry point
 *
 * @param  	
 *
 * @retval 	
 */
void ltzvisor_main(void){
	uint32_t ret;

	/** Initialize LTZVisor */
	ret = ltzvisor_init();
	if(!ret){
		/* ERROR */
		printk("ERROR: LTZVisor Init ... \n\t");
		while(1);
	}

	/** Create NS_Guest (Linux) */
	printk(" -> Guests: NS_Guest creation ... \n\t", ARCH);
	ret = ltzvisor_nsguest_create( &nsguest_config );
	if(!ret){
		/* ERROR */
		printk("Error: LTZVisor NS_Guest Create\n\t");
		while(1);
	}

	/** Kick off LTZVisor and start running Guests */
	printk(" -> LTZVisor: kicking off ... \n\t", ARCH);
	printk(" -> LTZVisor: starting S_Guest ... \n\t", ARCH);
	printk("----------------------------------------------------------\n\n\t");
	ltzvisor_kickoff();

	/** This point should never be reached */
	while (1);
}

