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
 * [zynq_ttc.h]
 *
 * This file contains the Zynq Triple Timer Counter driver (header).
 * 
 * (#) $id: zynq_ttc.h 20-05-2015 s_pinto$
 * (#) $id: zynq_ttc.h 19-09-2017 s_pinto (modified)$
*/

#ifndef __ZYNQ_TTC_H
#define __ZYNQ_TTC_H

#include"types.h"
#include"gic.h"
#include"platform_zynq.h"

/** TTC Interrupts IDs */
#define TTC0_TTCx_1_INTERRUPT	42
#define TTC0_TTCx_2_INTERRUPT	43
#define TTC0_TTCx_3_INTERRUPT	44
#define TTC1_TTCx_1_INTERRUPT	69
#define TTC1_TTCx_2_INTERRUPT	70
#define TTC1_TTCx_3_INTERRUPT	71

/** TTC Clock Control Register Flags */
#define TTC_CLK_CNTRL_EXT_EDGE 	(1 << 6) 
#define TTC_CLK_CNTRL_SRC     	(1 << 5) 
#define TTC_CLK_CNTRL_PS_EN  	(1 << 0)  
#define TTC_CLK_CNTRL_PS_VAL   	(4) 

/** TTC Counter Control Register Flags */
#define TTC_CNT_CNTRL_POL_WAVE	(1 << 6)        
#define TTC_CNT_CNTRL_EN_WAVE   (1 << 5)    
#define TTC_CNT_CNTRL_RST   	(1 << 4)   
#define TTC_CNT_CNTRL_MATCH 	(1 << 3) 
#define TTC_CNT_CNTRL_DEC  	(1 << 2) 
#define TTC_CNT_CNTRL_INT  	(1 << 1)   
#define TTC_CNT_CNTRL_DIS 	(1 << 0) 

/** TTC Interrupt Enable Register Flags */
#define TTC_INT_EN_EV    	(1 << 5) 
#define TTC_INT_EN_CNT_OVR 	(1 << 4)
#define TTC_INT_EN_MATCH3 	(1 << 3)  
#define TTC_INT_EN_MATCH2	(1 << 2)  
#define TTC_INT_EN_MATCH1 	(1 << 1) 
#define TTC_INT_EN_INTERVAL	(1 << 0)   

/** TTC Event Control Timer Register Flags */
#define TTC_EV_CNTRL_TIM_E_OV 	(1 << 2)
#define TTC_EV_CNTRL_TIM_E_LO	(1 << 1)
#define TTC_EV_CNTRL_TIM_E_EN 	(1 << 0)

/** TTC Reset Configuration value */
/*Output waveform enable & disable counter*/
#define TTC_RESET_CONFIG   	(0x21) 

/** TTC Values */
#define TTC_INT_VALUE    	(111)         
#define TTC_MATCH1_VALUE 	(111)     

/** Number of TTCs */
#define NUM_TTC    		2
/** Number of Timers per TTC */
#define NUM_TIM_PER_TTC  	3

/** TTC Number Definition */
#define TTC0      		0
#define TTC1        		1
/** TTC's Timer Number Definition */
#define TTCx_1      		0
#define TTCx_2      		1
#define TTCx_3      		2

/** TTC Modes */
#define INTERVAL       		0
#define MATCH          		1
#define FREE_RUNNING   		2

/** TTC registers structure */
typedef struct{
	/* Clock Control Register */
	volatile uint32_t clk_cntrl[NUM_TIM_PER_TTC];  
	/* Operational mode and reset */            
	volatile uint32_t cnt_cntrl[NUM_TIM_PER_TTC];
	/* Current counter value */              
	volatile const uint32_t cnt_value[NUM_TIM_PER_TTC]; 
	/* Interval value */       
	volatile uint32_t interv_cnt[NUM_TIM_PER_TTC]; 
	/* Match values */            
	volatile uint32_t match1_cnt[NUM_TIM_PER_TTC];             
	volatile uint32_t match2_cnt[NUM_TIM_PER_TTC];            
	volatile uint32_t match3_cnt[NUM_TIM_PER_TTC]; 
	/* Counter Interval, Match, Overflow and Event interrupts (RO) */          
	volatile const uint32_t interrupt_reg[NUM_TIM_PER_TTC];   
	/* */
	volatile uint32_t interrupt_en[NUM_TIM_PER_TTC]; 
	/* */      
	volatile uint32_t event_cntrl_tim[NUM_TIM_PER_TTC]; 
	/* */      
	volatile const uint32_t event_reg[NUM_TIM_PER_TTC]; 
} Zynq_Ttc;

/**
 * TTC initialization
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 * 		mode = timer mode 	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_init(uint32_t ttc_num, uint32_t timer_num, uint32_t mode);

/**
 * TTC enable
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_enable(uint32_t ttc_num, uint32_t timer_num);

/**
 * TTC disable
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_disable(uint32_t ttc_num, uint32_t timer_num);

/**
 * TTC timer request
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *		useconds = time 
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_request(uint32_t ttc_num, uint32_t timer_num, uint32_t useconds);

/**
 * TTC interrupt clear
 *
 * @param 	interrupt = interrupt number 
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_interrupt_clear(uint32_t interrupt);

#endif /* __ZYNQ_TTC_H */
