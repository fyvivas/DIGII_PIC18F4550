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

#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include "pinout.h"

void delay_ms(unsigned int delay_val);
void blink(unsigned int val);

#define ON 1
#define OFF 0

#define INPUT 1
#define OUTPUT 0



void main(){
    OSCCON = 0x72; //frec ( Mhz, oscilador interno)
    CFG_LED_POWER = OUTPUT;
    CFG_BTN_BLINK = INPUT;
       
    while(1){
        unsigned char btn_val = BTN_BLINK;
        /*
        for(int i=0;i<5;i++){
            blink(500);
        }
        blink(1000);
        blink(1000);
        */
        LED_POWER = btn_val;
        __delay_ms(500);
    }
    
}

void blink(unsigned int val){
    LED_POWER = ON; 
    delay_ms(val);
    LED_POWER = OFF;
    delay_ms(val);
}



void delay_ms(unsigned int delay_val){
    unsigned int i, j;
    for(i=0;i<delay_val;i++){
        for(j=0;j<204;j++);
    }
}