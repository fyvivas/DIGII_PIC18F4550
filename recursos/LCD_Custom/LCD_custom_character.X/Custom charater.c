/*
 * File:   LCD 16x2.c
 * Interfacing 16x2 LCD with PIC18F4550 to display Custom Character
 * www.electronicwings.com
 */

#include <pic18f4550.h>
#include "Configuration_Header_File.h" /* Header file where some configuration bits need to be set */

#define RS LATD0                    /*PORTD 0 pin is used for Register Select*/
#define EN LATD1                    /*PORTD 1 pin is used for Enable*/
#define ldata LATB                  /*PORTB is used for transmitting data to LCD*/

void LCD_Init();
void LCD_Command(char );
void LCD_Char(char x);
void LCD_String(const char *);
void LCD_String_xy(char ,char ,const char*);
void LCD_Clear();
void MSdelay(unsigned int );
void LCD_Custom_Char(unsigned char,unsigned char*);


unsigned char character1[8] = {0x00, 0x1f, 0x0a, 0x0a, 0x0a, 0x0a, 0x09, 0x00}; /* Value for Pi */
unsigned char character2[8] = {0x11, 0x19, 0x1d, 0x1f, 0x1d, 0x19, 0x11, 0x00}; /* Value for Diode */
unsigned char character3[8] = {0x12, 0x14, 0x18, 0x10, 0x18, 0x15, 0x13, 0x17}; /* Value for Transistor */
unsigned char character4[8] = {0x0a, 0x0a, 0x0a, 0x1b, 0x0a, 0x0a, 0x0a,0x00};  /* Value for Capacitor */
unsigned char character5[8] = {0x00, 0x0e, 0x011, 0x11, 0x11, 0x0a, 0x1B, 0x00};/* Value for Ohm */

/*****************************Main Program*******************************/

void main(void)
{       
    char i;
    OSCCON=0x72;                         /*Use Internal Oscillator with Frequency 8MHZ*/ 
    LCD_Init();                          /*Initialize LCD*/    
    LCD_String_xy(1,0,"Pi D  T  C  ohm");/*Display string for respective symbol*/
    LCD_Custom_Char(0,character1);       /*Write custom character to CGRAM 0x00 memory location*/
    LCD_Custom_Char(1,character2);       /*Write custom character to CGRAM 0x01 memory location*/
    LCD_Custom_Char(2,character3);       /*Write custom character to CGRAM 0x02 memory location*/
    LCD_Custom_Char(3,character4);       /*Write custom character to CGRAM 0x03 memory location*/
    LCD_Custom_Char(4,character5);       /*Write custom character to CGRAM 0x04 memory location*/
    
    for(i=0;i<5;i++)
    {    
        LCD_Command(0xc0|(i*3));     /*Display characters from c0(2nd row) location */
        LCD_Char(i);                 /*To display custom character send address as data to point stored 
                                       character */
    }    
    while(1);			
}

/****************************Functions********************************/
void LCD_Init()
{
    MSdelay(15);           /*15ms,16x2 LCD Power on delay*/
   	TRISB = 0x00;          /*Set PORTB as output PORT for LCD data(D0-D7) pins*/
    TRISD = 0x00;          /*Set PORTD as output PORT LCD Control(RS,EN) Pins*/
	LCD_Command(0x38);     /*uses 2 line and initialize 5*7 matrix of LCD*/
    LCD_Command(0x0c);     /*display on cursor off*/
    LCD_Command(0x06);     /*increment cursor (shift cursor to right)*/
	LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Clear()
{
    	LCD_Command(0x01);     /*clear display screen*/
}

void LCD_Command(char cmd )
{
	ldata= cmd;            /*Send data to PORT as a command for LCD*/   
	RS = 0;                /*Command Register is selected*/
	EN = 1;                /*High-to-Low pulse on Enable pin to latch data*/ 
	NOP();
	EN = 0;
	MSdelay(3);	
}

void LCD_Char(char dat)
{
	ldata= dat;            /*Send data to LCD*/  
	RS = 1;                /*Data Register is selected*/
	EN=1;                  /*High-to-Low pulse on Enable pin to latch data*/   
	NOP();
	EN=0;
    MSdelay(1);
}


void LCD_String(const char *msg)
{
	while((*msg)!=0)
	{		
	  LCD_Char(*msg);
	  msg++;	
    }
		
}

void LCD_String_xy(char row,char pos,const char *msg)
{
    char location=0;
    if(row<=1)
    {
        location=(0x80) | ((pos) & 0x0f);      /*Print message on 1st row and desired location*/
        LCD_Command(location);
    }
    else
    {
        location=(0xC0) | ((pos) & 0x0f);      /*Print message on 2nd row and desired location*/
        LCD_Command(location);    
    }  
    

    LCD_String(msg);

}


void LCD_Custom_Char(unsigned char loc,unsigned char *msg)
{
    unsigned char i;
    if(loc<8)
    {
     LCD_Command(0x40+(loc*8));     /* Command 0x40 and onwards forces the device to point CGRAM address */
       for(i=0;i<8;i++)             /* Write 8 byte for generation of 1 character */
           LCD_Char(msg[i]);
        
    }   
}
/*********************************Delay Function********************************/
void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<val;i++)
            for(j=0;j<165;j++);      /*This count Provide delay of 1 ms for 8MHz Frequency */
 }

