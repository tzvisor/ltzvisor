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
 * [xilinx_uart.h]
 *
 * This file contains the Zynq UART driver (header).
 * 
 * (#) $id: xilinx_uart.h 20-10-2015 s_pinto$
 * (#) $id: xilinx_uart.h 19-09-2017 s_pinto (modified)$
*/

#ifndef __UART_ZYNQ_H
#define __UART_ZYNQ_H

#include <types.h>
#include <platform_zynq.h>

/** UART Interrupts */
#define UART_0_INTERRUPT      	(59)
#define UART_1_INTERRUPT      	(82)

/** Number of available UARTs */
#define NUM_UART 		(2)

/** UART Control register configurations */
#define UART_CONTROL_STPBRK 	(0b1 << 8) // Stop transmitter break
#define UART_CONTROL_STTBRK 	(0b1 << 7) // Start transmitter break
#define UART_CONTROL_RSTTO 	(0b1 << 6) // Restart receiver timeout counter
#define UART_CONTROL_TXDIS 	(0b1 << 5) // Transmit disable
#define UART_CONTROL_TXEN 	(0b1 << 4) // Transmit enable
#define UART_CONTROL_RXDIS 	(0b1 << 3) // Receive disable
#define UART_CONTROL_RXEN 	(0b1 << 2) // Receive enable
#define UART_CONTROL_TXRES 	(0b1 << 1) // Software reset for Tx data path
#define UART_CONTROL_RXRES 	(0b1 << 0) // Software reset for Rx data path

/** UART Mode Register configuration */
#define UART_MODE_CHMODE_N 	(0b00 << 8) // Channel mode (Normal)
#define UART_MODE_CHMODE_AE 	(0b01 << 8) // Channel mode (Automatic Echo)
#define UART_MODE_CHMODE_LL 	(0b10 << 8) // Channel mode (Local Loopback)
#define UART_MODE_CHMODE_RL 	(0b11 << 8) // Channel mode (Remote Loopback)
#define UART_MODE_NBSTOP_1 	(0b00 << 6) // Number of stop bits (1)
#define UART_MODE_NBSTOP_1_5 	(0b01 << 6) // Number of stop bits (1.5)
#define UART_MODE_NBSTOP_2 	(0b10 << 6) // Number of stop bits (2)
#define UART_MODE_PAR_EP 	(0b000 << 3) // Parity type select (Even Parity)
#define UART_MODE_PAR_OP 	(0b001 << 3) // Parity type select (Odd Parity)
#define UART_MODE_PAR_F0P 	(0b010 << 3) // Parity type select (forced to 0 Parity)
#define UART_MODE_PAR_F1P 	(0b011 << 3) // Parity type select (forced to 1 Parity)
#define UART_MODE_PAR_NP 	(0b100 << 3) // Parity type select (No Parity)
#define UART_MODE_CHRL_6 	(0b11 << 1) // Character length select (6 bits)
#define UART_MODE_CHRL_7 	(0b10 << 1) // Character length select (7 bits)
#define UART_MODE_CHRL_8 	(0b00 << 1) // Character length select (8 bits)
#define UART_MODE_CHRL_REF 	(0b0 << 0) // Clock source select (clock source is uart_ref_clk)
#define UART_MODE_CLKS_REF_8 	(0b1 << 0) // Clock source select (clock source is uart_ref_clk/8)

/** UART Interrupt Enable Register configurations */
#define UART_ISR_EN_TOVR 	(0b1 << 12) // Transmitter FIFO Overflow interrupt (enable, clears mask=0)
#define UART_ISR_EN_TNFUL 	(0b1 << 11) // Transmitter FIFO Nearly Full interrupt (enable, clears mask=0)
#define UART_ISR_EN_TTRIG 	(0b1 << 10) // Transmitter FIFO Trigger interrupt (enable, clears mask=0)
#define UART_ISR_EN_DMSI 	(0b1 << 9) // Delta Modem Status Indicator interrupt (enable, clears mask=0)
#define UART_ISR_EN_TIMEOUT 	(0b1 << 8) // Receiver Timeout Error interrupt (enable, clears mask=0)
#define UART_ISR_EN_PARE 	(0b1 << 7) // Receiver Parity Error interrupt (enable, clears mask=0)
#define UART_ISR_EN_FRAME 	(0b1 << 6) // Receiver Framing Error interrupt (enable, clears mask=0)
#define UART_ISR_EN_ROVR 	(0b1 << 5) // Receiver Overflow Error interrupt (enable, clears mask=0)
#define UART_ISR_EN_TFUL 	(0b1 << 4) // Transmitter FIFO Full interrupt (enable, clears mask=0)
#define UART_ISR_EN_TEMPTY 	(0b1 << 3) // Transmitter FIFO Empty interrupt (enable, clears mask=0)
#define UART_ISR_EN_RFUL 	(0b1 << 2) // Receiver FIFO Full interrupt (enable, clears mask=0)
#define UART_ISR_EN_REMPTY 	(0b1 << 1) // Receiver FIFO Empty interrupt (enable, clears mask=0)
#define UART_ISR_EN_RTRIG 	(0b1 << 0) // Receiver FIFO Trigger interrupt (enable, clears mask=0)

/** UART Interrupt Disable Register configurations */
#define UART_ISR_DIS_TOVR 	(0b1 << 12) // Transmitter FIFO Overflow interrupt (disable, sets mask=1)
#define UART_ISR_DIS_TNFUL 	(0b1 << 11) // Transmitter FIFO Nearly Full interrupt (disable, sets mask=1)
#define UART_ISR_DIS_TTRIG 	(0b1 << 10) // Transmitter FIFO Trigger interrupt (disable, sets mask=1)
#define UART_ISR_DIS_DMSI 	(0b1 << 9) // Delta Modem Status Indicator interrupt (disable, sets mask=1)
#define UART_ISR_DIS_TIMEOUT 	(0b1 << 8) // Receiver Timeout Error interrupt (disable, sets mask=1)
#define UART_ISR_DIS_PARE 	(0b1 << 7) // Receiver Parity Error interrupt (disable, sets mask=1)
#define UART_ISR_DIS_FRAME 	(0b1 << 6) // Receiver Framing Error interrupt (disable, sets mask=1)
#define UART_ISR_DIS_ROVR 	(0b1 << 5) // Receiver Overflow Error interrupt (disable, sets mask=1)
#define UART_ISR_DIS_TFUL 	(0b1 << 4) // Transmitter FIFO Full interrupt (disable, sets mask=1)
#define UART_ISR_DIS_TEMPTY 	(0b1 << 3) // Transmitter FIFO Empty interrupt (disable, sets mask=1)
#define UART_ISR_DIS_RFUL 	(0b1 << 2) // Receiver FIFO Full interrupt (disable, sets mask=1)
#define UART_ISR_DIS_REMPTY 	(0b1 << 1) // Receiver FIFO Empty interrupt (disable, sets mask=1)
#define UART_ISR_DIS_RTRIG 	(0b1 << 0) // Receiver FIFO Trigger interrupt (disable, sets mask=1)

/** UART Interrupt Mask Register configurations */
#define UART_ISR_MASK_TOVR 	(0b1 << 12) // Transmitter FIFO Overflow interrupt (enabled)
#define UART_ISR_MASK_TNFUL 	(0b1 << 11) // Transmitter FIFO Nearly Full interrupt (enabled)
#define UART_ISR_MASK_TTRIG 	(0b1 << 10) // Transmitter FIFO Trigger interrupt (enabled)
#define UART_ISR_MASK_DMSI 	(0b1 << 9) // Delta Modem Status Indicator interrupt (enabled)
#define UART_ISR_MASK_TIMEOUT 	(0b1 << 8) // Receiver Timeout Error interrupt (enabled)
#define UART_ISR_MASK_PARE 	(0b1 << 7) // Receiver Parity Error interrupt (enabled)
#define UART_ISR_MASK_FRAME 	(0b1 << 6) // Receiver Framing Error interrupt (enabled)
#define UART_ISR_MASK_ROVR 	(0b1 << 5) // Receiver Overflow Error interrupt (enabled)
#define UART_ISR_MASK_TFUL 	(0b1 << 4) // Transmitter FIFO Full interrupt (enabled)
#define UART_ISR_MASK_TEMPTY 	(0b1 << 3) // Transmitter FIFO Empty interrupt (enabled)
#define UART_ISR_MASK_RFUL 	(0b1 << 2) // Receiver FIFO Full interrupt (enabled)
#define UART_ISR_MASK_REMPTY 	(0b1 << 1) // Receiver FIFO Empty interrupt (enabled)
#define UART_ISR_MASK_RTRIG 	(0b1 << 0) // Receiver FIFO Trigger interrupt (enabled)

/** UART Channel Interrupt Status Register configurations */
#define UART_ISR_STATUS_TOVR 	(0b1 << 12) // Transmitter FIFO Overflow interrupt (interrupt occurred)
#define UART_ISR_STATUS_TNFUL 	(0b1 << 11) // Transmitter FIFO Nearly Full interrupt (interrupt occurred)
#define UART_ISR_STATUS_TTRIG 	(0b1 << 10) // Transmitter FIFO Trigger interrupt (interrupt occurred)
#define UART_ISR_STATUS_DMSI 	(0b1 << 9) // Delta Modem Status Indicator interrupt (interrupt occurred)
#define UART_ISR_STATUS_TIMEOUT (0b1 << 8) // Receiver Timeout Error interrupt (interrupt occurred)
#define UART_ISR_STATUS_PARE 	(0b1 << 7) // Receiver Parity Error interrupt (interrupt occurred)
#define UART_ISR_STATUS_FRAME 	(0b1 << 6) // Receiver Framing Error interrupt (interrupt occurred)
#define UART_ISR_STATUS_ROVR 	(0b1 << 5) // Receiver Overflow Error interrupt (interrupt occurred)
#define UART_ISR_STATUS_TFUL 	(0b1 << 4) // Transmitter FIFO Full interrupt (interrupt occurred)
#define UART_ISR_STATUS_TEMPTY 	(0b1 << 3) // Transmitter FIFO Empty interrupt (interrupt occurred)
#define UART_ISR_STATUS_RFUL 	(0b1 << 2) // Receiver FIFO Full interrupt (interrupt occurred)
#define UART_ISR_STATUS_REMPTY 	(0b1 << 1) // Receiver FIFO Empty interrupt (interrupt occurred)
#define UART_ISR_STATUS_RTRIG 	(0b1 << 0) // Receiver FIFO Trigger interrupt (interrupt occurred)

/** UART Baud Rate Generator Register */
#define UART_BR_GEN_DIS		(0) // Baud Rate Clock Divisor Value (Disables baud_sample)
#define UART_BR_GEN_BYPASS	(1) // Baud Rate Clock Divisor Value (Clock divisor bypass)

/** UART Receiver Timeout Register */
#define UART_RX_TIMEOUT_DIS	(0) // Receiver timeout value (Disables receiver timeout counter)

/** UART Receiver FIFO Trigger Level Register */
#define UART_RX_FIFO_TRIG_DIS	(0) // RX FIFO trigger level value (Disables RX FIFO trigger level function)

/** UART Modem Control Register */
#define UART_MODEM_CTRL_FCM 	(0b1 << 5) // Automatic flow control mode (enable)
#define UART_MODEM_CTRL_RTS_FL1	(0b0 << 1) // Request to send output control (EMIOUARTxRTSN output forced to logic 1)
#define UART_MODEM_CTRL_RTS_FL0	(0b1 << 1) // Request to send output control (EMIOUARTxRTSN output forced to logic 0)
#define UART_MODEM_CTRL_DTR_FL1 (0b0 << 0) // Data Terminal Ready (EMIOUARTxDTRN output forced to logic 1)
#define UART_MODEM_CTRL_DTR_FL0 (0b1 << 0) // Data Terminal Ready (EMIOUARTxDTRN output forced to logic 0)

/** UART Modem Status Register */
#define UART_MODEM_STATUS_FCMS 	(0b1 << 8) // Flow control mode (enabled)
#define UART_MODEM_STATUS_DCD_H	(0b0 << 7) // Data Carrier Detect (DCD) input signal from PL(EMIOUARTxDCDN) status (input is high)
#define UART_MODEM_STATUS_DCD_L	(0b1 << 7) // Data Carrier Detect (DCD) input signal from PL(EMIOUARTxDCDN) status (input is low)
#define UART_MODEM_STATUS_RI_H	(0b0 << 6) // Ring Indicator (RI) input signal from PL(EMIOUARTxRIN) status (input is high)
#define UART_MODEM_STATUS_RI_L	(0b1 << 6) // Ring Indicator (RI) input signal from PL(EMIOUARTxRIN) status (input is low)
#define UART_MODEM_STATUS_DSR_H	(0b0 << 5) // Data Set Ready (DSR) input signal from PL(EMIOUARTxDSRN) status (input is high)
#define UART_MODEM_STATUS_DSR_L	(0b1 << 5) // Data Set Ready (DSR) input signal from PL(EMIOUARTxDSRN) status (input is low)
#define UART_MODEM_STATUS_CTS_H	(0b0 << 4) // Clear to Send (CTS) input signal from PL(EMIOUARTxCTSN) status (input is high)
#define UART_MODEM_STATUS_CTS_L	(0b1 << 4) // Clear to Send (CTS) input signal from PL(EMIOUARTxCTSN) status (input is low)
#define UART_MODEM_STATUS_DDCD	(0b1 << 3) // Delta Data Carrier Detect status (change has occurred)
#define UART_MODEM_STATUS_TERI	(0b1 << 2) // Trailing Edge Ring Indicator status (Trailing edge has occurred)
#define UART_MODEM_STATUS_DDSR	(0b1 << 1) // Delta Data Set Ready status (change has occurred)
#define UART_MODEM_STATUS_DCTS	(0b1 << 1) // Delta Clear To Send status (change has occurred)

/** UART Channel Status Register */
#define UART_CH_STATUS_RTRIG    (1 << 0)
#define UART_CH_STATUS_REMPTY   (1 << 1)
#define UART_CH_STATUS_RFUL     (1 << 2)
#define UART_CH_STATUS_TEMPTY	(1 << 3)
#define UART_CH_STATUS_TFUL     (1 << 4)

/** UART Baud Rate Divider Register */
#define UART_BR_DIV_DIS		(0) // Baud rate divider value (0-3 ignored)

/** UART Flow Control Delay Register */
#define UART_FLOW_CTRL_DL_DIS	(0) // RxFIFO trigger level for Ready To Send (RTS)output signal (EMIOUARTxRTSN) de-assertion (0-3 disable)

/** UART Transmitter FIFO Trigger Level Register */
#define UART_TX_FIFO_TRIG_DIS	(0) // TX FIFO trigger level value (Disables TX FIFO trigger level function)

/** UART Configs (Zynq 7000) */
#define UART_BAUD_RATE		115200 //115.2kbps
#define UART_FREQ_CLK		50000000 //50MHz
#define UART_MAX_ERROR		5 // 0.5% acceptable error (error%/10)
#define UART_RX_TRIGGER_LVL	1 //

/** UART Configs for 115200 */
#define UART_BDIV_115200	5
#define UART_CD_115200		72

/** For printk */
#define serial_puts(str_buffer) uart_puts(1,(const int8_t *)str_buffer)

/** Zynq UART register structure */
typedef struct{
	/* UART Control register */
	volatile uint32_t control;
	/* UART Mode Register */       
	volatile uint32_t mode;
	/* UART Interrupt Enable Register */          
	volatile uint32_t isr_en;   
	/* UART Interrupt Disable Register */     
	volatile uint32_t isr_dis;  
	/* UART Interrupt Mask Register */     
	volatile uint32_t isr_mask; 
	/* UART Channel Interrupt Status Register */     
	volatile uint32_t isr_status;  
	/* UART Baud Rate Generator Register */  
	volatile uint32_t br_gen; 
	/* UART Receiver Time out Register */       
	volatile uint32_t rx_timeout;
	/* UART Receiver FIFO Trigger Level Register */    
	volatile uint32_t rx_fifo_trig;
	/* UART Modem Control Register */  
	volatile uint32_t modem_ctrl;
	/* UART Modem Status Register */    
	volatile uint32_t modem_status; 
	/* UART Channel Status Register */ 
	volatile uint32_t ch_status; 
	/* UART Transmit and Receive FIFO */    
	volatile uint32_t tx_rx_fifo; 
	/* UART Baud Rate Divider Register */   
	volatile uint32_t br_div; 
	/* UART Flow Control Delay Register */       
	volatile uint32_t flow_ctrl_dl;
		/* Reserved: 2(0x2) bytes */  
	const uint32_t reserved[2];  
	/* UART Transmitter FIFO Trigger Level Register */    	
	volatile uint32_t tx_fifo_trig;  
} Uart_Zynq;

/**
 * UART initialization
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	TRUE in sucess; FALSE in case error	
 */
uint32_t uart_init(uint8_t uart_id);

/**
 * UART enable
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	
 */
void uart_enable(uint8_t uart_id);

/**
 * UART disable
 *
 * @param 	uart_id = ID uart	
 *
 * @retval	
 */
void uart_disable(uint8_t uart_id);

/**
 * UART baudrate set
 *
 * @param 	uart_id = ID uart
 *		baud_rate = baudrate speed of the uart	
 *
 * @retval	TRUE in sucess; FALSE in case error	
 */
uint32_t uart_set_baud_rate(uint8_t uart_id, uint32_t baud_rate);

/**
 * UART get character
 *
 * @param 	uart_id = ID uart
 *
 * @retval	Received character	
 */
uint32_t uart_getc(uint8_t uart_id);

/**
 * UART send character
 *
 * @param 	uart_id = ID uart
 *		c = Character to be sent 
 *
 * @retval		
 */
void uart_putc(uint8_t uart_id,int8_t c);

/**
 * UART send string
 *
 * @param 	uart_id = ID uart
 *		c = String to be sent 
 *
 * @retval		
 */
void uart_puts(uint8_t uart_id,const int8_t *s);

#endif /* __UART_ZYNQ_H */
