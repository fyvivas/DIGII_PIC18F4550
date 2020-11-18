/*!
\file   Gpio_Main.c
\date   2020-11-18
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example GPIO.

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

/*
#define INPUT 1
#define OUTPUT 0

#define s1 TRISBbits.TRISB7
#define s2 TRISBbits.TRISB6
#define s3 TRISBbits.TRISB5
#define s4 TRISBbits.TRISB4

#define s1_read PORTBbits.RB7
#define s2_read PORTBbits.RB6
#define s3_read PORTBbits.RB5
#define s4_read PORTBbits.RB4

#define ON_LED 1
#define OFF_LED 0
*/

int main(void) {
    OSCCON=0x72;       /* Use internal oscillator of 8MHz Frequency */
    //Configura los pines RD7-RD6-RD5-RD4 como salida digital
    TRISDbits.TRISD7 = 0;
    TRISDbits.TRISD6 = 0;
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD4 = 0;
    //Configura los pines RB7-RB6-RB5-RB4 como entrada digital
    TRISBbits.TRISB7 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB4 = 1;

    while (1) {
        if(!PORTBbits.RB4){
            LATDbits.LATD4=1;
        }
        else{
            LATDbits.LATD4=0;
        }
        if(!PORTBbits.RB5){LATDbits.LATD5=1;}else{LATDbits.LATD5=0;}
        if(!PORTBbits.RB6){LATDbits.LATD6=1;}else{LATDbits.LATD6=0;}
        if(!PORTBbits.RB7){LATDbits.LATD7=1;}else{LATDbits.LATD7=0;}
    }
    return 1;
}
