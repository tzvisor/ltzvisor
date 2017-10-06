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
 * [ltzvisor_nsguest_config.c]
 *
 * This file contains the LTZVisor NS Guest configuration.
 * 
 * (#) $id: ltzvisor_nsguest_config.c 10-10-2015 s_pinto & j_pereira $
 * (#) $id: ltzvisor_nsguest_config.c 18-09-2017 s_pinto (modified)$
*/

#include <ltzvisor_nsguest_config.h>

/** Info from ltzvisor_nsguest.S */
extern uint32_t GPOS0_start, GPOS0_end;

/** Config structure according to NS Guest */
struct nsguest_conf_entry nsguest_config[] ={
	{
		.gce_name = "Linux 3.3 (vanilla)",
		.gce_id = 0,
		/* No ram disk needed */
		.gce_trd_init = 0,
		/* Binary image size */
		.gce_bin_start = (uint32_t) &GPOS0_start,
		.gce_bin_end = (uint32_t) &GPOS0_end,
		/* Load address */
		.gce_bin_load = 0x00100000,

	}
};
