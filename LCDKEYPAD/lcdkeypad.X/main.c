

#include <xc.h>
#include <pic18f4550.h>
#include "LCD_20x4_H_file.h"
#include "keypad.h"
#include "fuses.h"

char key = '0';
#define BAUD  9600

unsigned char var = '0';

void main() {

    //Configura Fosc = 8Mhz interno
    OSCCONbits.IRCF = 0b111; //Configura oscilador interno (FOSC = 8Mhz)
    OSCCONbits.SCS = 0b10; // Fuente de Fosc del sistema = interno
    
    //Puerto C como Salida
    //TRISC = 0;
    //TRISD = 0;
    //PORTC = 0; //Limpia Puerto C

    //TRISD = 0x07; //First 3 pins of PORTD are input
    //LATD = 0x00;

    
    LCD_Init(); //Inicializa el LCD
    LCD_String_xy(1,0,"KEY: password");
    keypad_init();

    //Configura UART a 9600 baudios
    TRISCbits.RC6 = 0; //  Pin RC6 como salida digital para TX.
    
    TXSTAbits.TX9 = 0; //  Modo-8bits.
    TXSTAbits.TXEN = 1; //  Habilita Transmisión.
    TXSTAbits.SYNC = 0; //  Modo-Asíncrono.
    TXSTAbits.BRGH = 0; //  Modo-Baja Velocidad de Baudios.
    BAUDCONbits.BRG16 = 0; //  Baudios modo-8bits.
    RCSTAbits.SPEN = 1; //  Hbilita el Módulo SSP como UART.
    //  Escribe el valor necesario para configurar los Baudios a 9600.
    SPBRG = (unsigned char) (((_XTAL_FREQ / BAUD) / 64) - 1);
    
    //  espera a que el registro de transmisión este disponible o vacio.
    while (!TXSTAbits.TRMT) {
    }
    //  escribe el dato que se enviará a través de TX.
    TXREG = 'f';
        
    while (1) {
        
        //key = keypad_getkey();
        //key = keyfind();  /* find a pressed key */

        //short kp = readKeypad(); //Read Keypad
        //key = decodeCharacter(kp); //Convert Keypad to Character

        
        if (key) {
            LCD_String_xy(2,0,"KEY: ");
            LCD_String((char)key);
            LCD_String(" TE");
        }
        //  espera a que el registro de transmisión este disponible o vacio.
        while (!TXSTAbits.TRMT) {
        }
        //  escribe el dato que se enviará a través de TX.
        TXREG = key;
        __delay_ms(100);
         
    }
}
