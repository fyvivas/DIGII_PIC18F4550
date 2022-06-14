#include <xc.h>
#include <pic18f4550.h>
#include "config.h"

unsigned int value_adc = 0;
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

void main(void) {

    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno

    TRISD = 0x00;    
    TRISA = 0xFF;
    
    //ADC = 10bits, Tad = 1us, Tacq = 4us, Vref = 5v-0v, RA=ANALOG
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Anal�gica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisici�n 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversi�n Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificaci�n derecha (modo-10bits).
    ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.

    while (1) {
        ADCON0bits.GO_DONE = 1; //Inicia la COnversi� AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        lm35 = (char) temp;
        LATD = (1 << 4) + (lm35 % 10);
        __delay_ms(50);
        LATD = (1 << 5) + (lm35 / 10);
        __delay_ms(50);
    }
}