/* 
 * File:   main.h
 * Author: Saklen
 *
 * Created on 9 December, 2025, 4:14 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#define _XTAL_FREQ 20000000

#define _8_BIT_MODE       (1)
#define INSTRUCTION_CLK   (0)
#define PRESCALER_ENABLE  (0)
#define ENABLE            (1)
#define DISABLE           (0)
#define OUTPUT            (0)
#define INPUT             (1)
#define HIGH              (1)
#define LOW               (0)
#define FALLING           (0)
#define IT_TRUE           (1)
#define IT_FALSE          (0)
#define BIT_PERIOD       (0xA1)
#define HALF_BIT_PERIOD  (0x60)
#define NEUTRAL           (2)
#define RECIEVE           (1)
#define TRANSMIT          (0)

void timer0_init(void);
void gpio_init(void);
void exint2_init(void);

#endif	/* MAIN_H */

