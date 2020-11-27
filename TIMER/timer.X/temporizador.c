/*!
\file   temporizador.c
\date   2020-11-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example temporizador.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "fuses.h"

#define _XTAL_FREQ 1000000L

unsigned char count = 0;

int main(void) {
    INTCONbits.GIE = 0;
    T0CONbits.T0CS = 0; // temporizador
    T0CONbits.PSA = 0; // prescaler enable
    T0CONbits.T0PS = 0b001; // prescaler 4
    T0CONbits.T08BIT = 0; // 16 bits
    TMR0L = 0xDA; //3034
    TMR0H = 0x0B;
    T0CONbits.TMR0ON = 1;
    TRISD = 0x00;
    LATD = 0x00;
    TRISAbits.RA4 = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    while (1) {
        //LATD = ((count / 10) << 4) + (count % 10);
        LATD = (1 << 4) + (count % 10);
        __delay_ms(20);
        LATD = (1 << 5) + (count / 10);
        __delay_ms(20);
        
        
        if (!PORTAbits.RA4) {
            __delay_ms(50);
            count = 0;
            TMR0L = 0xDA;
            TMR0H = 0x0B;
            INTCONbits.TMR0IF = 0;
        }
    }
    return 1;
}

void interrupt ISR_TIMER_0(void) {
    if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
        if (++count == 100) {
            count = 0;
        }
        TMR0L = 0xDA;
        TMR0H = 0x0B;
        INTCONbits.TMR0IF = 0;
    }
}

