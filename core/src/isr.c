#include <xc.h>
#include "main.h"
#include "uart_banging.h"
#include "isr.h"

extern volatile uint8_t uart_status;

void __interrupt() t0_interrupt(void){
    
    if(INTCON3bits.INT2IF == 1){ /*------( External Interrupt 2 ISR)------*/ 
        
        INTCON3bits.INT2IF = DISABLE;
        INTCON3bits.INT2IE = DISABLE;
        uart_wait_halfbit();
    }
    
    if(INTCONbits.TMR0IF == 1){ /*------( Timer0 ISR)------*/ 
        
        T0CONbits.TMR0ON = DISABLE;
        INTCONbits.TMR0IF = DISABLE;
        
             if(uart_status == TRANSMIT ) uart_tx();
        else if(uart_status == RECIEVE  ) uart_rx();
    }
}
