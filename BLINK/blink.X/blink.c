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
    TRISD = OUTPUT; //0x00
    CFG_BTN_BLINK = INPUT;
        
    LATD = 0x03;//0b'00000001'
        
    while(1){
        unsigned char btn_val = BTN_BLINK;
        if(btn_val){
            LED_POWER = btn_val;
            LATD = 0x00;//0b'00000001'
        }
        else{
            LED_POWER = OFF;
           LATD = LATD << 2;
           if(LATD == 0x00){
                LATD = 0x03;
            }
           __delay_ms(500);
        }
        
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