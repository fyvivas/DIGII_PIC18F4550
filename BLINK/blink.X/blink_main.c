/*!
\file   Blink.c
\date   2020-11-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example blink.

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


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1L
//#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
//#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
//#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)


// 'C' source line config statements
//#include "osc_config.h"  /*Header file for Configuration Bits*/
#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "config.h"
#include "utils.h"


#define __USER__

#ifdef __USER__
#define DELAY(a) MSdelay (a);
#else
#define DELAY(a) __delay_ms(500);
#endif

#define LED_RED LATB7
#define CFG_LED_RED TRISB7
#define LED_GREEN LATA

#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0

void main()
{
    OSCCON=0x72;        /* Use internal oscillator of 8MHz Frequency */
    //TRISB=0x00;         /* Set direction of PORTB as OUTPUT to which LED is connected */
    CFG_LED_RED = OUTPUT;
    
    while(1)
    {
        LED_RED = ON;     /* Turn ON LED for 500 ms */
        DELAY(2000);
        LED_RED = OFF;        /* Turn OFF LED for 500 ms */
        DELAY(1000);
    }
}

//__delay_us(10);
//__delay_ms(500);