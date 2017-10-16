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
 * [zynq_ttc.c]
 *
 * This file contains the Zynq Triple Timer Counter driver.
 * 
 * (#) $id: zynq_ttc.c 20-05-2015 s_pinto$
 * (#) $id: zynq_ttc.c 19-09-2017 s_pinto (modified)$
*/

#include"zynq_ttc.h"

/** */
Zynq_Ttc * const Ptr_Ttc[NUM_TTC] = {(Zynq_Ttc *)TTC0_BASE, (Zynq_Ttc *)TTC1_BASE};


/**
 * TTC initialization
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 * 		mode = timer mode 	
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_init(uint32_t ttc_num, uint32_t timer_num, uint32_t mode){

	Zynq_Ttc * ptr_ttc = NULL;
	uint32_t clk_cntrl = 0;

	/**  Check Arguments  */
	if( (ttc_num > TTC1) || (timer_num > TTCx_2) || (mode > FREE_RUNNING) ){
		/* Invalid Argument */
		return (FALSE); 
	}

	ptr_ttc = Ptr_Ttc[ttc_num];

	/** Reset Configuration Value */
	ptr_ttc->cnt_cntrl[timer_num] = TTC_RESET_CONFIG; // Reset Configs

	/** Set clock input source */
	clk_cntrl = ptr_ttc->clk_cntrl[timer_num];
	/* Prescale disable -> F = 111MHz (1us = 111ticks) */
	clk_cntrl &= (~(TTC_CLK_CNTRL_PS_EN));
	ptr_ttc->clk_cntrl[timer_num] = clk_cntrl;

	/** Set Configurations */
	switch (mode){
		case INTERVAL:
			/* Reset and Set to Interval mode */
			ptr_ttc->cnt_cntrl[timer_num] = (TTC_RESET_CONFIG) | (TTC_CNT_CNTRL_RST | TTC_CNT_CNTRL_INT | TTC_CNT_CNTRL_DIS);
			/* Set interval value (default) */ 
			ptr_ttc->interv_cnt[timer_num] = TTC_INT_VALUE; 
			/* Set interval interrupt */
			ptr_ttc->interrupt_en[timer_num] = TTC_INT_EN_INTERVAL; 
			break;
		case MATCH:
			/* Reset and Set to Match mode */
			ptr_ttc->cnt_cntrl[timer_num] = (TTC_CNT_CNTRL_RST | TTC_CNT_CNTRL_MATCH | TTC_CNT_CNTRL_DIS);
			/* Set match1 value (default) */
			ptr_ttc->match1_cnt[timer_num] = TTC_MATCH1_VALUE;
			/* Set match1 interrupt */ 
			ptr_ttc->interrupt_en[timer_num] = TTC_INT_EN_MATCH1; 
			break;
		case FREE_RUNNING:
			/* Nothing to do */
			break;
	}

	return TRUE;
}

/**
 * TTC enable
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_enable(uint32_t ttc_num, uint32_t timer_num){

	Zynq_Ttc * ptr_ttc = NULL;
	uint32_t cnt_cntrl = 0;

	/**  Check Arguments  */
	if( (ttc_num > TTC1) || (timer_num > TTCx_2)){
		/* Invalid Argument */
		return (FALSE); 
	}

	ptr_ttc = Ptr_Ttc[ttc_num];

	cnt_cntrl = ptr_ttc->cnt_cntrl[timer_num]; 
	/* Reset counter value and restarts counting */
	cnt_cntrl |= TTC_CNT_CNTRL_RST;
	/* Enable Timer */ 
	cnt_cntrl &= ~TTC_CNT_CNTRL_DIS; 
	ptr_ttc->cnt_cntrl[timer_num] = cnt_cntrl;

	return TRUE;
}

/**
 * TTC disable
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_disable(uint32_t ttc_num, uint32_t timer_num){

	Zynq_Ttc * ptr_ttc = NULL;
	uint32_t cnt_cntrl = 0;

	/**  Check Arguments  */
	if( (ttc_num > TTC1) || (timer_num > TTCx_2)){
		/* Invalid Argument */
		return (FALSE); 
	}

	ptr_ttc = Ptr_Ttc[ttc_num];

	cnt_cntrl = ptr_ttc->cnt_cntrl[timer_num];
	/* Disable Timer */
	cnt_cntrl |= TTC_CNT_CNTRL_DIS; 
	ptr_ttc->cnt_cntrl[timer_num] = cnt_cntrl;

	return TRUE;
}

/**
 * TTC timer request
 *
 * @param 	ttc_num = TTC number
 * 		timer_num = TTC's timer number
 *		useconds = time 
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_request(uint32_t ttc_num, uint32_t timer_num, uint32_t useconds){

	Zynq_Ttc * ptr_ttc = NULL;
	uint32_t cnt_cntrl = 0;
	uint32_t clk_cntrl = 0;

	/**  Check Arguments  */
	if( (ttc_num > TTC1) || (timer_num > TTCx_2)){
		/* Invalid Argument */
		return (FALSE); 
	}

	ptr_ttc = Ptr_Ttc[ttc_num];

	/** Reset counter value and restarts counting */
	cnt_cntrl = ptr_ttc->cnt_cntrl[timer_num];
	cnt_cntrl |= ( TTC_CNT_CNTRL_RST | TTC_CNT_CNTRL_DIS );
	ptr_ttc->cnt_cntrl[timer_num] = cnt_cntrl;

	/** Static handling - range [1us;1ms]*/
	/* TODO - redo */
	if( useconds>=1 && useconds<=1000 ) {
		/* Prescaler = 1 -> F = 100MHz/(2^(1+1)) (1ms = 25000 ticks) */
		clk_cntrl = ptr_ttc->clk_cntrl[timer_num];
		clk_cntrl |= ( ((2-1) << 1) | 0x1 );			/* Prescaler = 1 */
		ptr_ttc->clk_cntrl[timer_num] = clk_cntrl;

		useconds = ((useconds * 25000) / 1000);
	}
	/** Static handling - range ]1ms;1s]*/
	/* TODO - redo */
	else if (useconds>1000 && useconds<=1000000) {
		/* Prescaler = 11 -> F = 100MHz/(2^(11+1)) (10ms = 244 ticks) */
		clk_cntrl = ptr_ttc->clk_cntrl[timer_num];
		clk_cntrl |= ( ((12-1) << 1) | 0x1 );			/* Prescaler = 11 */
		ptr_ttc->clk_cntrl[timer_num] = clk_cntrl;

		useconds = ((useconds * 244) / 10000);

	} 
	else{
		return (FALSE); 
	}

	/** Set Time */
	/* Extract mode */
	cnt_cntrl &= (TTC_CNT_CNTRL_MATCH | TTC_CNT_CNTRL_INT); 
	/* Interval Mode */
	if(cnt_cntrl & TTC_CNT_CNTRL_INT){
		ptr_ttc->interv_cnt[timer_num] = useconds;
	}
	/* Match Mode */
	else if(cnt_cntrl & TTC_CNT_CNTRL_MATCH){
		ptr_ttc->match1_cnt[timer_num] = useconds;
	}
	else{
		/* Not Implemented */
		return FALSE; 
	}

	return TRUE;
}

/**
 * TTC interrupt clear
 *
 * @param 	interrupt = interrupt number 
 *
 * @retval	True for success and FALSE in case ERROR 	
 */
uint32_t ttc_interrupt_clear(uint32_t interrupt){

	Zynq_Ttc * ptr_ttc = NULL;
	uint32_t ttc_num = 0;
	uint32_t interrupt_reg = 0;
	uint32_t ttc_tim_num = 0;

	/** Check which TTC_timer generated the Interrupt */
	switch (interrupt){
		case TTC0_TTCx_1_INTERRUPT:
			ttc_num = 0;
			ttc_tim_num = 0;
			break;
		case TTC0_TTCx_2_INTERRUPT:
			ttc_num = 0;
			ttc_tim_num = 1;
			break;
		case TTC0_TTCx_3_INTERRUPT:
			ttc_num = 0;
			ttc_tim_num = 2;
			break;
		case TTC1_TTCx_1_INTERRUPT:
			ttc_num = 1;
			ttc_tim_num = 0;
			break;
		case TTC1_TTCx_2_INTERRUPT:
			ttc_num = 1;
			ttc_tim_num = 1;
			break;
		case TTC1_TTCx_3_INTERRUPT:
			ttc_num = 1;
			ttc_tim_num = 2;
			break;
		default:
			/* ERROR */
			return FALSE;
	}

	ptr_ttc = Ptr_Ttc[ttc_num];

	/** Clear Interrupt Status Flag */
	interrupt_reg = ptr_ttc->interrupt_reg[ttc_tim_num];

	return interrupt_reg;
}



