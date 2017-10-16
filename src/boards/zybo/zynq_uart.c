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
 * [zynq_uart.c]
 *
 * This file contains the Zynq UART driver (header).
 * 
 * (#) $id: zynq_uart.c 20-10-2015 s_pinto$
 * (#) $id: zynq_uart.c 19-09-2017 s_pinto (modified)$
*/

#include <zynq_uart.h>

Uart_Zynq * const Ptr_Uart[NUM_UART] = {(Uart_Zynq *)UART_BASE_0,(Uart_Zynq *)UART_BASE_1};


/**
 * UART initialization (default 115200)
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	TRUE in sucess; FALSE in case error	
 */
uint32_t uart_init(uint8_t uart_id){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];
	uint32_t ret;
	
	ret = uart_set_baud_rate(uart_id, UART_BAUD_RATE);
	if(ret == FALSE){
		return FALSE;
	}

	/* Set the level of the RxFIFO trigger level */
	ptr_uart->rx_fifo_trig = UART_RX_TRIGGER_LVL;
	/* Program the Receiver Timeout Mechanism (Disabled) */
	ptr_uart->rx_timeout = UART_RX_TIMEOUT_DIS;

	/* Clear all the interrupts in Interrupt Status Register */
	ptr_uart->isr_status = 0xFFFFFFFF;
	/* Enable RxFIFO Trigger Interrupt */
	ptr_uart->isr_en = UART_ISR_EN_RTRIG;

	/** Enable the Controller */
	ptr_uart->control |= (UART_CONTROL_STPBRK|UART_CONTROL_RXRES|UART_CONTROL_TXRES);

	return TRUE;
}

/**
 * UART enable
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	
 */
void uart_enable(uint8_t uart_id){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];

	uint32_t ctrl_reg = ptr_uart->control;
	ctrl_reg = ( UART_CONTROL_STPBRK | UART_CONTROL_TXEN | 
			UART_CONTROL_RXEN | UART_CONTROL_RXRES | UART_CONTROL_TXRES );
	ptr_uart->control = ctrl_reg;

}

/**
 * UART disable
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	
 */
void uart_disable(uint8_t uart_id){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];

	uint32_t ctrl_reg = ptr_uart->control;
	ctrl_reg = ( UART_CONTROL_STPBRK | UART_CONTROL_TXDIS | UART_CONTROL_RXDIS );
	ptr_uart->control = ctrl_reg;
}

/**
 * UART baudrate set
 *
 * @param 	uart_id = ID uart
 *		baud_rate = baudrate speed of the uart	
 *
 * @retval	TRUE in sucess; FALSE in case error	
 */
uint32_t uart_set_baud_rate(uint8_t uart_id, uint32_t baud_rate){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];

	//uint32_t sel_clk =  UART_FREQ_CLK;
	uint8_t  bdiv = 0;
	uint16_t cd_calc = 0;

	/** Handling corner case */
	if(baud_rate == 0){
		baud_rate =  UART_BAUD_RATE;
	}

	/* baud_rate = sel_clk / (CD * (BDIV+1))
	 * baud_rate -> Baud Rate
	 * sel_clk -> Selected Clock
	 * CD -> Baud Rate Generator
	 * BDIV -> Baud Rate Divider
	 */
	/** FIXME - Handling statically 115200 */
	bdiv = UART_BDIV_115200;
	cd_calc = UART_CD_115200;
	
	/** Configure the Baud Rate */
	/* Disable the Rx and Tx path */
	ptr_uart->control = (UART_CONTROL_RXDIS|UART_CONTROL_TXDIS);
	/* Write the calculated CD value */
	ptr_uart->br_gen = cd_calc;
	/* Write the calculated BDIV value */
	ptr_uart->br_div = bdiv;
	/* Reset Tx and Rx paths */
	ptr_uart->control = (UART_CONTROL_TXRES|UART_CONTROL_RXRES);
	/* Enable the Rx and Tx path */
	ptr_uart->control = (UART_CONTROL_TXEN|UART_CONTROL_RXEN);

	return TRUE;
}

/**
 * UART get character
 *
 * @param 	uart_id = ID uart
 *		baud_rate = baudrate speed of the uart	
 *
 * @retval	Received character	
 */
uint32_t uart_getc(uint8_t uart_id){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];
	uint32_t data = 0;

	/* Wait until RxFIFO is filled up to the trigger level */
	while(!ptr_uart->ch_status & UART_CH_STATUS_RTRIG);

	data = ptr_uart->tx_rx_fifo;

	return data;
}

/**
 * UART send character
 *
 * @param 	uart_id = ID uart
 *		c = Character to be sent 
 *
 * @retval		
 */
void uart_putc(uint8_t uart_id,int8_t c){

	Uart_Zynq * ptr_uart = Ptr_Uart[uart_id];

	//wait until txFIFO is not full
	while(ptr_uart->ch_status & UART_CH_STATUS_TFUL);

	ptr_uart->tx_rx_fifo = c;

}

/**
 * UART send string
 *
 * @param 	uart_id = ID uart
 *		c = String to be sent 
 *
 * @retval		
 */
void uart_puts(uint8_t uart_id, const int8_t *s){

	 while (*s){
		uart_putc(uart_id,*s++);
	}
}
