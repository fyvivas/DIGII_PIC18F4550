/*!
\file   keypad_lcd_main.c
\date   2021-09-13
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  keypad 4x4 and LCD 16X2 4BITS.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2021. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/

#include <xc.h>
#include <pic18f4550.h>
#include "Config.h"
#include "LCD.h"

unsigned char keyfind();            /* function to find pressed key*/

#define write_port LATB             /* latch register to write data on port */
#define read_port PORTB             /* PORT register to read data of port */
#define Direction_Port TRISB

#define KEYPAD_WRITE LATB             /* latch register to write data on port */
#define KEYPAD_READ PORTB             /* PORT register to read data of port */
#define KEYPAD_PORT TRISB

unsigned char col_loc,rowloc,temp_col;

unsigned char keypad[4][4]= {'7','8','9','/',
                             '4','5','6','*',
                             '1','2','3','-',
                             ' ','0','=','+'};

unsigned char password[5] ={'2','0','2','1',0};

unsigned char pass_user[5];
unsigned char idx = 0;

void main() 
{
    char key;
    OSCCON = 0x72;

    RBPU=0;                             /* activate pull-up resistor */
    LCD_Init();                         /* initialize LCD16x2 in 4-bit mode */
    LCD_String_xy(0,0,"Press a Key");
    LCD_Command(0xC0);                  /* display pressed key on 2nd line of LCD */
    while(1)
    {
        do{
            key = keyfind();              /* find a pressed key */
            LCD_Char('*');/* display pressed key on LCD16x2 */
            pass_user[idx++] = key;
        }while(idx < 5);
        //__delay_ms(2000);
        //if(strncmp(&password, &pass_user,4)){
        //LCD_String_xy(2,5,"P");
            
        
    }
    
}

unsigned char Keypad_Key_Press(void)
{
 const unsigned char keypad_deco[17]=   
 {'7', '8', '9', '/', '4', '5', '6', '*', '1', '2', '3', '-', 13, '0', '=', '+', 0};
 
    unsigned int tec = 0, fila;
 
    
    for (fila = 0b00000001; fila < 0b00010000; fila <<= 1)
    {
        LATD =fila<<4;  //lo traslada 4  posicones para sacar por las filas
        if (PORTDbits.RD0== 1) break; tec++;
        if (PORTDbits.RD1 == 1) break; tec++;
        if (PORTDbits.RD2 == 1) break; tec++;
        if (PORTDbits.RD3 == 1) break; tec++;
    }
    PORTD = 0x00;
    return keypad_deco[tec];//retorna el codigo deseao de la tecla
}


unsigned char keyfind()
{      
    
    Direction_Port = 0xf0;              /*TRISB = 0B 1111 0000*/
    unsigned char temp1;
   
        write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
      do
      {
        do
        {
          
            col_loc = read_port & 0xf0; /*mask port with f0 and copy it to col_loc variable*/   
        
        }while(col_loc!=0xf0);          /*Check initially at the start there is any key pressed*/ 
         col_loc = read_port & 0xf0;    /*mask port with f0 and copy it to col_loc variable*/  
      }while(col_loc!=0xf0);
      
      __delay_ms(50);
        write_port = 0xf0;              /*Make lower nibble as low(Gnd) and Higher nibble as High(Vcc)*/
        do
        { do
            
            {
               
                col_loc = read_port & 0xf0;
            }while(col_loc==0xf0);      /*Wait for key press*/
         col_loc = read_port & 0xf0;
        }while(col_loc==0xf0);          /*Wait for key press*/
               
        __delay_ms(20);
         
        col_loc = read_port & 0xf0;
               
   
    
    while(1)
    {
        write_port  = 0xfe;                 /*make Row0(D0) Gnd and keep other row(D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=0;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/    
            }
            break;
        }
        
        write_port = 0xfd;                  /*make Row1(D1) Gnd and keep other row(D0-D2-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=1;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Monitor the status of Port and Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xfb;                  /*make Row0(D2) Gnd and keep other row(D0-D1-D3) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=2;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
        write_port = 0xf7;                  /*make Row0(D3) Gnd and keep other row(D0-D2) high*/
        col_loc = read_port & 0xf0;         /*Read Status of PORT for finding Row*/
        temp_col=col_loc;
        if(col_loc!=0xf0)
        {
            rowloc=3;                       /*If condition satisfied get Row no. of key pressed*/
            while(temp_col!=0xf0)           /*Wait for key to release*/
            {
                temp_col = read_port & 0xf0;/*Read Status of PORT for checking key release or not*/
            }
            break;
        }
        
    }

    
    
    while(1)
    {
        
        if(col_loc==0xe0)
        {
             return keypad[rowloc][0];      /*Return key pressed value to calling function*/            
        }
        else 
            if(col_loc==0xd0)
        {
            return keypad[rowloc][1];       /*Return key pressed value to calling function*/   
        }
        else
            if(col_loc==0xb0)
        {
            return keypad[rowloc][2];       /*Return key pressed value to calling function*/
        }
        else
            
        {
            return keypad[rowloc][3];       /*Return key pressed value to calling function*/           
        }    
    }
    
   __delay_ms(300);     
 
}

