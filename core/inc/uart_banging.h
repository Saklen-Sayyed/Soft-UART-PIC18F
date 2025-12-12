/* 
 * File:   uart_banging.h
 * Author: Saklen
 *
 * Created on 9 December, 2025, 4:17 PM
 */

#ifndef UART_BANGING_H
#define	UART_BANGING_H

void uart_tx_start(void);
void uart_tx_frame(void);
void uart_start_bit(void);
void uart_payload(void);
void uart_stop_bit(void);
void uart_rx_frame(void);
void uart_wait_halfbit(void);
void uart_tx(void);
void uart_rx(void);

#endif	/* UART_BANGING_H */

