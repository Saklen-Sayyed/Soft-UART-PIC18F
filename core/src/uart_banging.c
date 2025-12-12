#include <xc.h>
#include "main.h"
#include "uart_banging.h"

volatile uint8_t uart_status;
static volatile uint8_t temp_rx = 0;

/*********************[   uart_tx_frame    ]*********************/

// Objective : Transmit Frame Of Uart With 1 Start, Payload & Stop
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_tx_frame(void){
    
    static uint8_t framebit = 0;
    static uint8_t payload_in = 0;
    
    switch(framebit){
        
         case 0: uart_start_bit();
                 framebit++;
                 break;
                 
         case 1: uart_payload();
                 payload_in++;
                 break;
                 
         case 2: uart_stop_bit();
                 framebit++;
                 break;
                 
        default: framebit = 0;
                 uart_status = NEUTRAL;
                 temp_rx = 0;
                 T0CONbits.TMR0ON = DISABLE;
                 INTCON3bits.INT2IE = ENABLE;
    }
    
    if(payload_in == 8){
        payload_in = 0;
        framebit++;
    }
}

/*********************[   uart_start_bit    ]*********************/

// Objective : Makes The Line Low Indicating Start Of Transmission
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_start_bit(void){
    
    LATDbits.LD0 = LOW;
}

/*********************[    uart_payload    ]*********************/

// Objective : Makes The Line High Or Low According to The Bit To 
//             Be Transferred
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_payload(void){
    
    static uint8_t nth_place = 0;
    
    LATDbits.LD0 = ((temp_rx >> nth_place) & 1U );
    
    nth_place++;
    if(nth_place == 8){
        nth_place = 0;
    }
}

/*********************[    uart_stop_bit    ]*********************/

// Objective : Makes The Line High Indicating End Of Transmission
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_stop_bit(void){
    
    LATDbits.LD0 = HIGH;
}

/*********************[    uart_rx_frame    ]*********************/

// Objective : Recieves 8Bit Data Bit by Bit After Detecting Start 
//             bit After 8bit Data Signals The Echo
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_rx_frame(void){
    
    static uint8_t nth_place = 0;
    
    if(nth_place < 8){
        
        temp_rx |= (uint8_t)((PORTBbits.RB2 << nth_place) & (1U << nth_place));
        nth_place++;
    }
    
    else{
        T0CONbits.TMR0ON = DISABLE;
        __delay_ms(1);
        uart_status = TRANSMIT;
        nth_place = 0;
    }
    
}

/*********************[    uart_rx_frame    ]*********************/

// Objective : Creates A Delay Of 1.5 Bit Period Immedietly After 
//             Detecting Start Bit ISR calls this function
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_wait_halfbit(void){
    
    T0CONbits.TMR0ON  = DISABLE; /*------( Timer0 Enable                )------*/ 
    TMR0L = HALF_BIT_PERIOD;     /*------( Creating Half Bit Delay      )------*/
    INTCONbits.TMR0IE = ENABLE;  /*------( Timer-0 Interrupt Enable     )------*/
    T0CONbits.TMR0ON  = ENABLE;  /*------( Timer0 Enable                )------*/ 
    
    uart_status = RECIEVE;
}

/*********************[       uart_tx       ]*********************/

// Objective : ISR Calls This Function If uart_status = TRANSMIT
//             It Processes The Transmission
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_tx(void){
    
    uart_tx_frame();
            
    if(uart_status != NEUTRAL){
        
        TMR0L = BIT_PERIOD;
        T0CONbits.TMR0ON  = ENABLE;
    }
}

/*********************[       uart_rx       ]*********************/

// Objective : ISR Calls This Function If uart_status = TRANSMIT
//             It Processes The Transmission
// Input     : None
// Output    : None

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
void uart_rx(void){
    
    uart_rx_frame();
       
    if(uart_status != NEUTRAL){
        
        TMR0L = BIT_PERIOD;
        T0CONbits.TMR0ON  = ENABLE;
    }
}