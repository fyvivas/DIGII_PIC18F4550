/*!
\file   delay_1ms_irq.c
\date   2020-11-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Generating a delay of 1 ms in PIC18F4550 using Timer1 with Interrupt Service Routine ISR.

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


void Timer1_start();

#define Pulse LATB

void main()
{ 
    OSCCON=0x72;    /* Configure oscillator frequency to 8MHz */
    TRISB = 0;      /* Set as output Port */
    Pulse = 0xff;   /* send high on PortB */
    Timer1_start();
    
    while(1);
    
}
/*********************Interrupt Service Routine for Timer1************************/
void interrupt Timer1_ISR()
{
    
    TMR1=0xF856;
    Pulse = ~Pulse;    /* Toggle Value at PortB to generate waveform of 500 Hz */   
    PIR1bits.TMR1IF=0; /* Make Timer1 Overflow Flag to '0' */
}

void Timer1_start()
{
    GIE=1;              /* Enable Global Interrupt */
    PEIE=1;             /* Enable Peripheral Interrupt */
    TMR1IE=1;           /* Enable Timer1 Overflow Interrupt */
    TMR1IF=0;
    T1CON=0x80;         /* Enable 16-bit TMR1 Register,No pre-scale,use internal clock,Timer OFF */
    TMR1=0xF856;        /* Load Count for generating delay of 1ms */
    TMR1ON=1;           /* Turn-On Timer1 */
}
