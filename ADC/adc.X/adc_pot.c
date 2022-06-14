#include <xc.h>
#include <pic18f4550.h>
#include "config.h"
#include "adc_lib.h"

#define	_LIBADC_

void main(void) {
    
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno
    
    TRISD = 0x00;// salida puerto D
    TRISA = 0xFF;

#ifdef _LIBADC_
    adc_init();
#else
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Anal�gica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Anal�gico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisici�n 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversi�n Fosc/8.
    ADCON2bits.ADFM = 0; //  Justificaci�n Izquierda (modo-8bits).
    ADCON0bits.ADON = 1; //  Habilita el M�dulo AD.
#endif    

    while (1) {

        #ifdef _LIBADC_
            LATD = adc_read(); //  Lectura de valor AD.
        #else   
            ADCON0bits.GO_DONE = 1; //  Inicia la COnversi� AD.
            while (ADCON0bits.GO_DONE); //  Espera a que termine la conversi�n AD.
            LATD = ADRESH;
        #endif 
    }
}


