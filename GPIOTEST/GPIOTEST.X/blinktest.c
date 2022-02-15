/*!
\file   blinktest.h
\date   2022-02-15
\author Fulvio Vivas <fyvivas@unicauca.edu.co>
\brief  example GPIO BLINK.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2022. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/


#include <xc.h>
#include <pic18f4550.h>
#include "fuses.h"

#define LED_RED LATB7
#define PIN_LED_RED TRISB7
#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0

#define _XTAL_FREQ 8000000 //Crystal Oscillator Frequency


void delay(unsigned int val);

void main(void){
    
    OSCCON = 0b01110010;
    PIN_LED_RED = OUTPUT;
    
    while(1){
        LED_RED = ON;
        __delay_ms(500);
        LED_RED = OFF;
        delay(500);
        
    }
}

void delay(unsigned int val){
    unsigned int i, j;
    for(i=0;i<val;i++){
        for(j=0;j<204;j++);
    }
}

