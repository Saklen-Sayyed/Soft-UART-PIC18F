#pragma config OSC    =  HS     // Oscillator Selection bits (HS oscillator)
#pragma config WDT    = OFF     // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)

#include <xc.h>
#include "main.h"
#include "uart_banging.h"

void main(void){
    gpio_init();
    timer0_init();
    exint2_init();
    
    while(1);
}

/*********************[    Timer0_init     ]*********************/

// Objective : Initiates Timer0 In 8 Bit Mode With Prescaler Of
//             4 & Interrupt Enabled
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void timer0_init(void){
    
    T0CONbits.T08BIT  = _8_BIT_MODE;      /*------( Timer-0 8-bit Mode       )------*/
    T0CONbits.T0CS    = INSTRUCTION_CLK;  /*------( Timer-0 Clock Select     )------*/
    T0CONbits.PSA     = PRESCALER_ENABLE; /*------( Timer-0 PreScaler Enable )------*/
    
    /******************( Timer-0 Pre-scaler Of 4  )*******************/
    T0CONbits.T0PS2   = LOW;  /*------( Timer-0 PreScaler Bit2   )------*/
    T0CONbits.T0PS1   = LOW;  /*------( Timer-0 PreScaler Bit1   )------*/
    T0CONbits.T0PS0   = HIGH; /*------( Timer-0 PreScaler Bit0   )------*/
    
    /**************( Timer-0 Interrupt Configuration  )***************/
    RCONbits.IPEN     = DISABLE; /*------( Interrupt Priority Enable    )------*/
    INTCONbits.GIE    = ENABLE;  /*------( Global Interrupt Enable      )------*/
    INTCONbits.PEIE   = ENABLE;  /*------( Peripheral Interrupt Enable  )------*/
    INTCONbits.TMR0IF = DISABLE; /*------( Timer-0 Interrupt Flag       )------*/
}

/*********************[     gpio_init      ]*********************/

// Objective : Configure GPIO Pins Keeping tx Line High
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void gpio_init(void){
    
    TRISDbits.RD0 = OUTPUT; /*------( Pin D0 = OUTPUT(UART TX)      )------*/
    LATDbits.LD0  = HIGH;   /*------( Keeping The Line High )------*/
    
    TRISBbits.RB2 = INPUT;  /*------( Pin D0 = INPUT(INT2)(UART RX) )------*/
}

/*********************[     exint2_init      ]*********************/

// Objective : Configure GPIO Pins Keeping tx Line High
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void exint2_init(void){
    
    INTCON2bits.INTEDG2 = FALLING; /*------( Falling Edge On ExtInt2      )------*/
    INTCON3bits.INT2IF  = DISABLE; /*------( External Interrupt2 Flag = 0 )------*/
    INTCON3bits.INT2IE  = ENABLE;  /*------( External Interrupt2 Enable   )------*/

}