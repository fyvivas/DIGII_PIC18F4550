/*!
\file   test_main.c
\date   2020-11-17
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  example test pic18f4550.

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


// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/
#include "fuses.h"

#define LED LATB
#define ON_LED 0xFF
#define OFF_LED 0x00


void ms_delay(unsigned int);

void main()
{
    OSCCON=0x72;        /* Use internal oscillator of 8MHz Frequency */
    TRISB=0x00;         /* Set direction of PORTB as OUTPUT to which LED is connected */
    while(1)
    {
        LED = ON_LED;     /* Turn ON LED for 500 ms */
        //ms_delay(500);
        __delay_ms(500);
        LED = OFF_LED;        /* Turn OFF LED for 500 ms */
        //ms_delay(500);
        __delay_ms(500);
    }
}


/*F**************************************************************************
* NAME: MSdelay
*----------------------------------------------------------------------------
* PARAMS:
* val: delay in milliseconds
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Set a delay in milliseconds
*----------------------------------------------------------------------------
* NOTE:
* 9
*****************************************************************************/
void ms_delay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);  /*This count Provide delay of 1 ms for 8MHz Frequency */
} 
