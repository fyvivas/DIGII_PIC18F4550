

#define _XTAL_FREQ  8000000L
#include <xc.h>
#include "fuses.h"

unsigned int value_adc = 0;
unsigned char counter_digito = 0;
double temp = 0.0;
unsigned char lm35 = 0;

void main(void) {

    TRISD = 0x00;    
    TRISA = 0xFF;
    
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Oscilador del sistema = Fosc interno

    //ADC = 10bits, Tad = 1us, Tacq = 4us, Vref = 5v-0v, RA=ANALOG
    ADCON1bits.PCFG = 0b1110; //  Configura el Puerto como Entrada Analógica.
    ADCON1bits.VCFG = 0b00; //  Selecciona Voltajes de Referencia (5v-0v).
    ADCON0bits.CHS = 0b0000; //  Selecciona el Canal Analógico.
    ADCON2bits.ACQT = 0b010; //  Tiempo de Adquisición 4Tad.
    ADCON2bits.ADCS = 0b001; //  Tiempo de Conversión Fosc/8.
    ADCON2bits.ADFM = 1; //  Justificación derecha (modo-10bits).
    ADCON0bits.ADON = 1; //  Habilita el Módulo AD.

    //Configura TIMER1 = 10ms (multiplexar display 7 segmentos de 2 digitos)
    T1CON = 0b10010000;
    TMR1H = 0xD8; //Registro TMR1 =  55535
    TMR1L = 0xEF;
    T1CONbits.TMR1ON = 1; //Timer1 ON
    PIR1bits.TMR1IF = 0; //Borra flag de TIMER1
    PIE1bits.TMR1IE = 1; //Habilita interrupción TIMER1
    INTCONbits.PEIE = 1; //Habilitara interrupción periféricas
    INTCONbits.GIE = 1; //Habilita interrupción global


    while (1) {
        ADCON0bits.GO_DONE = 1; //Inicia la COnversió AD.
        while (ADCON0bits.GO_DONE); //  Espera a que termine la conversión AD.
        value_adc = ADRESH; //  Lectura de valor AD.
        value_adc = (value_adc << 8) + ADRESL;
        temp = value_adc;
        temp = (temp * 500.0) / 1023.0;
        lm35 = (char) temp;
    }
}

void interrupt ISR_TIMER_1(void) {
    if (PIE1bits.TMR1IE && PIR1bits.TMR1IF) {
        TMR1H = 0xD8;
        TMR1L = 0xEF;

        switch (counter_digito) {
            case 0:
                LATD = (counter_digito << 4) + (lm35 / 10);
                counter_digito = 1;
                break;
            case 1:
                LATD = (counter_digito << 4) + (lm35 % 10);
                counter_digito = 0;
                break;
        }
        PIR1bits.TMR1IF = 0;
    }
}