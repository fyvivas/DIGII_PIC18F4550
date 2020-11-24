/*!
\file   contador.c
\date   2020-11-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example contador.

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

unsigned char count = 0;

int main(void) {
    INTCONbits.GIE = 0;
    T0CONbits.T0CS = 1;
    T0CONbits.T0SE = 1;
    T0CONbits.T08BIT = 1;
    T0CONbits.TMR0ON = 1;
    TMR0L = 0;
    TRISD = 0x00;
    LATD = 0x00;
    TRISAbits.RA4 = 1;
    while (1) {
        if (TMR0L == 10) {
            TMR0L = 0;
            count = 0;
        }
        count = TMR0L;
        LATD = (1 << 4) | count;
    }
    return 1;
}
