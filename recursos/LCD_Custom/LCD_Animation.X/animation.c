/*
 * File:   LCD 16x2.c
 * Interfacing 16x2 LCD with PIC18F4550 to display animation
 * www.electronicwings.com
 */

#include <pic18f4550.h>
#include "Configuration_Header_File.h" /* Header file where some sonfiguration bits need to be set */

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

unsigned char character1[8] = {0x00,0x00, 0x0e, 0x1f, 0x1f, 0x0e, 0x00, 0x00}; /* centre Ball */
unsigned char character2[8] = {0x0e, 0x1f, 0x1f, 0x0e, 0x00, 0x00,0x00,0x00};  /* top Ball */
unsigned char character3[8] = { 0x00, 0x00,0x00,0x00,0x0e, 0x1f, 0x1f, 0x0e};  /* lower Ball */

/*****************************Main Program*******************************/

void main(void)
{       
    char i;
    OSCCON=0x72;                          /*Use Internal Oscillator with Frequency 8MHZ*/ 
    LCD_Init();                           /*Initialize 16x2 LCD*/
    
    LCD_Custom_Char(0,character1);       /*Write custom character to CGRAM 0x00 memory location*/
    LCD_Custom_Char(1,character2);       /*Write custom character to CGRAM 0x01 memory location*/
    LCD_Custom_Char(2,character3);       /*Write custom character to CGRAM 0x02 memory location*/

    while(1)    
    {
        LCD_Clear();
        LCD_Command(0x80);
        LCD_Char(0);                     /* display custom character of location 0 */
        MSdelay(250);
        
        LCD_Clear();
        LCD_Command(0xc1);
        LCD_Char(1);
        MSdelay(250);
        
        LCD_Clear();
        LCD_Command(0xc2);
        LCD_Char(2);
        MSdelay(400);
        
        LCD_Clear();
        LCD_Command(0xc3);
        LCD_Char(0);
        MSdelay(400);
        
        LCD_Clear();
        LCD_Command(0xc4);
        LCD_Char(1);
        MSdelay(400);
        
        LCD_Clear();
        LCD_Command(0x85);
        LCD_Char(2);
        MSdelay(400);
        
        LCD_Clear();
        LCD_Command(0x86);
        LCD_Char(0);
        MSdelay(400);
        
        LCD_Clear();
        LCD_Command(0x87);
        LCD_Char(1);
        MSdelay(500);
        
        LCD_Clear();
        LCD_Command(0x88);
        LCD_Char(0);
        MSdelay(500);
        
        LCD_Clear();
        LCD_Command(0x89);
        LCD_Char(2);
        MSdelay(500);

        LCD_Clear();
        LCD_Command(0xca);
        LCD_Char(1);
        MSdelay(500);
        
        LCD_Clear();
        LCD_Command(0xcb);
        LCD_Char(0);
        MSdelay(500);
        
        LCD_Clear();
        LCD_Command(0xcc);
        LCD_Char(2);
        MSdelay(600);
        
        LCD_Clear();
        LCD_Command(0xcd);
        LCD_Char(1);
        MSdelay(600);
        
        LCD_Clear();
        LCD_Command(0x8e);
        LCD_Char(2);
        MSdelay(600);
        
        LCD_Clear();
        LCD_Command(0x8f);
        LCD_Char(0);
        MSdelay(600);
    }  			
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

