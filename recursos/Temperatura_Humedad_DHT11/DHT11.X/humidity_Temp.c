/*
 * DHT11 Interfacing with PIC18F4550
 * http://www.electronicwings.com
 */


#include <pic18f4550.h>
#include <xc.h>
#include <stdio.h>
#include "Configuration_Header_File.h"
#include "LCD_16x2_8-bit_Header_File.h"

#define Data_Out LATA0              /* assign Port pin for data*/
#define Data_In PORTAbits.RA0       /* read data from Port pin*/
#define Data_Dir TRISAbits.RA0      /* Port direction */
#define _XTAL_FREQ 8000000          /* define _XTAL_FREQ for using internal delay */

void DHT11_Start();
void DHT11_CheckResponse();
char DHT11_ReadData();

void main() 
{
    char RH_Decimal,RH_Integral,T_Decimal,T_Integral;
    char Checksum;
    char value[10];    
    OSCCON = 0x72;      /* set internal oscillator with frequency 8 MHz*/

    LCD_Init();         /* initialize LCD16x2 */
    ADCON1=0x0F;        /* this makes all pins as a digital I/O pins */    
    while(1)
{   
    DHT11_Start();                  /* send start pulse to DHT11 module */
    DHT11_CheckResponse();          /* wait for response from DHT11 module */
    
    /* read 40-bit data from DHT11 module */
    RH_Integral = DHT11_ReadData(); /* read Relative Humidity's integral value */
    RH_Decimal = DHT11_ReadData();  /* read Relative Humidity's decimal value */
    T_Integral = DHT11_ReadData();  /* read Temperature's integral value */
    T_Decimal = DHT11_ReadData();   /* read Relative Temperature's decimal value */
    Checksum = DHT11_ReadData();    /* read 8-bit checksum value */
    
    /* convert humidity value to ascii and send it to display*/    
    sprintf(value,"%d",RH_Integral);
    LCD_String_xy(0,0,value);
    sprintf(value,".%d ",RH_Decimal);
    LCD_String(value);
    LCD_Char('%');
    
    /* convert temperature value to ascii and send it to display*/
    sprintf(value,"%d",T_Integral);
    LCD_String_xy(1,0,value);
    sprintf(value,".%d",T_Decimal);
    LCD_String(value);
    LCD_Char(0xdf);
    LCD_Char('C');
    
    sprintf(value,"%d  ",Checksum);
    LCD_String_xy(1,8,value);
    
    /* check addition of humidity and temperature value equals to checksum */
    if(Checksum != (RH_Integral + RH_Decimal + T_Integral + T_Decimal))
        LCD_String_xy(0,8,"Error");
    else
        LCD_String_xy(0,8,"No Error");
    
    MSdelay(500);
    
}   
    
}

char DHT11_ReadData()
{
  char i,data = 0;  
    for(i=0;i<8;i++)
    {
        while(!(Data_In & 1));      /* wait till 0 pulse, this is start of data pulse */
        __delay_us(30);         
        if(Data_In & 1)             /* check whether data is 1 or 0 */    
          data = ((data<<1) | 1); 
        else
          data = (data<<1);  
        while(Data_In & 1);
    }
  return data;
}

void DHT11_Start()
{    
    Data_Dir = 0;       /* set as output port */
    Data_Out = 0;       /* send low pulse of min. 18 ms width */
    __delay_ms(18);
    Data_Out = 1;       /* pull data bus high */
    __delay_us(20);
    Data_Dir = 1;       /* set as input port */    
//    LED = 14;
}

void DHT11_CheckResponse()
{
    while(Data_In & 1);     /* wait till bus is High */     
    while(!(Data_In & 1));  /* wait till bus is Low */
    while(Data_In & 1);     /* wait till bus is High */
}