/*!
\file   uart.c
\date   2020-11-23
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  Example uart.

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
#include "adc_header.h"

#define _XTAL_FREQ  8000000L

char buffer_TX[] = "Temp: xxx grados\r";
int value_adc;
double temp;
char lm35;

void main(void) {
    //Configura Fosc = 8Mhz interno
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Fuente de Fosc del sistema = interno

    //Configura UART a 9600 baudios
    TRISCbits.RC6 = 0; //  Pin RC6 como salida digital para TX.
    TXSTAbits.TX9 = 0; //  Modo-8bits.
    TXSTAbits.TXEN = 1; //  Habilita Transmisi�n.
    TXSTAbits.SYNC = 0; //  Modo-As�ncrono.
    TXSTAbits.BRGH = 0; //  Modo-Baja Velocidad de Baudios.
    BAUDCONbits.BRG16 = 0; //  Baudios modo-8bits.
    RCSTAbits.SPEN = 1; //  Hbilita el M�dulo SSP como UART.
    SPBRG = (unsigned char) (((_XTAL_FREQ / 9600) / 64) - 1); //baudios  = 9600


    ADC_Init();
    
    //ADC = 10bits, Tad = 1us, Tacq = 4us, Vref = 5v-0v, RA=ANALOG
    /*
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Anal�gica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisici�n 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversi�n Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificaci�n derecha (modo-10bits).
    ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.
    */
    while (1) {
        //Inicia el proceso de conversi�n ADC.
        value_adc = ADC_Read(0);
        /*
        ADCON0bits.GO_DONE = 1; //Inicia la COnversi� AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        */
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        lm35 = (char) temp;
        buffer_TX[6] = (lm35 / 100) + '0';
        buffer_TX[7] = (lm35 % 100) / 10 + '0';
        buffer_TX[8] = (lm35 % 100) % 10 + '0';
        //Inicia el proceso de transmisi�n TX.
        for (int i = 0; i < 17; i++) {
            //  espera a que el registro de transmisi�n este disponible o vacio.
            while (!TXSTAbits.TRMT) {
            }
            //  escribe el dato que se enviar� a trav�s de TX.
            TXREG = buffer_TX[i];
        }
        __delay_ms(100);
    }
}
