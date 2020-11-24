/*!
\file   delay_1ms.c
\date   2020-11-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Generating a delay of 1 ms in PIC18F4550 using Timer1.

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

#include "fuses.h"		/* Configuration header file */
#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/


#define Pulse LATB  		/* Define Pulse as LATB to output on PORTB */

void Timer1_delay();

void main()
{
    OSCCON=0x72;  		/* Configure oscillator frequency to 8MHz */
    TRISB=0;  			/* Set as output port */
    Pulse=0xff;  		/* Send high on PortB */
    
    while(1)
    {
        Pulse=~Pulse;  		/* Toggle PortB at 500 Hz */ 
        Timer1_delay();  	/* Call delay which provide desired delay */    
    }   
}

void Timer1_delay()
{
    /* Enable 16-bit TMR1 register, No pre-scale, internal clock,timer OFF */
    T1CON=0x80;  

    TMR1=0xf830;		/* Load count for generating delay of 1ms */
    T1CONbits.TMR1ON=1;  	/* Turn ON Timer1 */
    while(PIR1bits.TMR1IF==0); 	/* Wait for Timer1 overflow interrupt flag */
    TMR1ON=0;  			/* Turn OFF timer */
    TMR1IF=0;  			/* Make Timer1 overflow flag to '0' */
}
