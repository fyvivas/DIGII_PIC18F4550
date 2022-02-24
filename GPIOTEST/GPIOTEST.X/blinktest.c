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

#define BTN_S4 PORTBbits.RB4
#define PIN_BTN_S4 TRISB4

#define LED_RED LATD4
#define PIN_LED_RED TRISD4
#define ON 1
#define OFF 0
#define HIGH 1
#define LOW 0

#define INPUT 1
#define OUTPUT 0

#define _XTAL_FREQ 8000000 //Crystal Oscillator Frequency


void delay(unsigned int val);
void blink (unsigned int val_delay);

void main(void){
    
    OSCCON = 0b01110010; //oscilador interno 8 Mhz
    
    ADCON1 = 0x0F;
    
    PIN_BTN_S4 = INPUT;
    PIN_LED_RED = OUTPUT;
    LED_RED = OFF;
          
    //PIN_LED_RED = OUTPUT;
    
    while(1){
        //blink(500);
        if(BTN_S4 == HIGH){
            LED_RED = ON;
        }
        else{
            LED_RED = OFF;
        }
        __delay_ms(500);
    }
}

/*F**************************************************************************
* NAME: blink
*----------------------------------------------------------------------------
* PARAMS:
* none: 
* return:   none
*----------------------------------------------------------------------------
* PURPOSE:
* Set a delay in milliseconds
*----------------------------------------------------------------------------
* NOTE:
* 9
*****************************************************************************/
void blink (unsigned int val_delay){
    
    LED_RED = ON;
    __delay_ms(val_delay);
    LED_RED = OFF;
    __delay_ms(val_delay); 
}

/*F**************************************************************************
* NAME: delay
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

void delay(unsigned int val){
    unsigned int i, j;
    for(i=0;i<val;i++){
        for(j=0;j<204;j++);
    }
}

