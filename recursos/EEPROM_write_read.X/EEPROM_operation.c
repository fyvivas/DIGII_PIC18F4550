#include <stdio.h>
#include <stdlib.h>
#include <p18f4550.h>
#include "eeprom_osc.h"
#include "USART_Header_File.h"


void EEPROM_Write(int,char);        /* Write byte to EEPROM data memory */
char EEPROM_Read(int);              /* Read Byte From EEPROM data memory */
void EEPROM_WriteString(int,char*); /* Write byte to EEPROM data memory */

void main()
{
    int i;
    i=0;
    char Data_read;
    OSCCON=0x72;              /* Use internal Oscillator with 8 Mhz Frequency */
    USART_Init(9600);         /* initialize USART operation with 9600 baud rate */ 
    
    EEPROM_WriteString(0,"electronicWings");
    /* As EEPROM memory location set to 0xff default
     So while reading data from EEPROM memory we are comparing it with 0xff*/
    while(Data_read!=0xff)    
    {    
        Data_read=EEPROM_Read(i);
        USART_TransmitChar(Data_read);  /*transmit read data serially to the serial monitor*/
        i++;
    }

    while(1);
    
}


void EEPROM_Write(int address,char data)
{
    /*Write Operation*/
    EEADR=address;               /*Write address to the EEADR register*/
    EEDATA=data;                 /*copy data to the EEDATA register for write to EEPROM location*/
    EECON1bits.EEPGD=0;          /*Access data EEPROM memory*/
    EECON1bits.CFGS=0;           /*Access flash program or data memory*/
    EECON1bits.WREN=1;           /*Allow write to the memory*/
    INTCONbits.GIE=0;            /*Disable global interrupt*/
    
    /*below sequence in EECON2 Register is necessary to write data to EEPROM memory*/
    EECON2=0x55;
    EECON2=0xaa;
    
    EECON1bits.WR=1;             /*Start writing data to EEPROM memory*/
    INTCONbits.GIE=1;            /*Enable interrupt*/
    
    while(PIR2bits.EEIF==0);     /*EEIF bit is set when write operation is completed*/
                                 /*monitor this bit for write operation*/  
    PIR2bits.EEIF=0;             /*Reset EEIF for further write operation*/
    
}

void EEPROM_WriteString(int address,char *data)
{
    /*Write Operation for String*/
    while(*data!=0)
    {
        EEPROM_Write(address,*data);
        address++;
        *data++;
    }    
}

char EEPROM_Read(int address)
{
    /*Read operation*/
    EEADR=address;               /*Read data at location 0x00*/
    EECON1bits.WREN=0;           /*WREN bit is clear for Read operation*/  
    EECON1bits.EEPGD=0;          /*Access data EEPROM memory*/
    EECON1bits.RD=1;             /*To Read data of EEPROM memory set RD=1*/
    return(EEDATA);
}

