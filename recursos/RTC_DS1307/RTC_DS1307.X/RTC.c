/*
 * PIC18F4550 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 


#include <stdio.h>
#include "Configuration_Header_File.h"
#include "16x2_LCD_4bit_File.h"
#include <pic18f4550.h>
#include "I2C_Master_File.h"

#define device_id_write 0xD0
#define device_id_read 0xD1

int sec,min,hour;
int Day,Date,Month,Year;

void RTC_Read_Clock(char read_clock_address)
{
    I2C_Start(device_id_write);
    I2C_Write(read_clock_address);     /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    sec = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    min = I2C_Read(0);                 /*read data and send ack for continuous reading*/
    hour= I2C_Read(1);                 /*read data and send nack for indicating stop reading*/
    
}

void RTC_Read_Calendar(char read_calendar_address)
{   
    I2C_Start(device_id_write);
    I2C_Write(read_calendar_address); /* address from where time needs to be read*/
    I2C_Repeated_Start(device_id_read);
    Day = I2C_Read(0);                /*read data and send ack for continuous reading*/
    Date = I2C_Read(0);               /*read data and send ack for continuous reading*/
    Month = I2C_Read(0);              /*read data and send ack for continuous reading*/
    Year = I2C_Read(1);               /*read data and send nack for indicating stop reading*/
    I2C_Stop();
}

void main()
{
    
    char secs[10],mins[10],hours[10];
    char date[10],month[10],year[10];
    char Clock_type = 0x06;
    char AM_PM = 0x05;
    char days[7] = {'S','M','T','W','t','F','s'};
    OSCCON=0x72;                    /*Use internal oscillator and 
                                     *set frequency to 8 MHz*/ 
    I2C_Init();                     /*initialize I2C protocol*/
    LCD_Init();                     /*initialize LCD16x2*/    
    LCD_Clear();
    MSdelay(10);
    while(1)
    { 
        RTC_Read_Clock(0);              /*gives second,minute and hour*/
        I2C_Stop();
        if(hour & (1<<Clock_type)){     /* check clock is 12hr or 24hr */
            
            if(hour & (1<<AM_PM)){      /* check AM or PM */
                LCD_String_xy(1,14,"PM");
            }
            else{
                LCD_String_xy(1,14,"AM");
            }
            
            hour = hour & (0x1f);
            sprintf(secs,"%x ",sec);   /*%x for reading BCD format from RTC DS1307*/
            sprintf(mins,"%x:",min);    
            sprintf(hours,"Tim:%x:",hour);  
            LCD_String_xy(0,0,hours);            
            LCD_String(mins);
            LCD_String(secs);
        }
        else{
            
            hour = hour & (0x3f);
            sprintf(secs,"%x ",sec);   /*%x for reading BCD format from RTC DS1307*/
            sprintf(mins,"%x:",min);    
            sprintf(hours,"Tim:%x:",hour);  
            LCD_String_xy(0,0,hours);            
            LCD_String(mins);
            LCD_String(secs); 
        }
        
        RTC_Read_Calendar(3);        /*gives day, date, month, year*/        
        I2C_Stop();
        sprintf(date,"Cal %x-",Date);
        sprintf(month,"%x-",Month);
        sprintf(year,"%x ",Year);
        LCD_String_xy(2,0,date);
        LCD_String(month);
        LCD_String(year);

    /* find day */
        switch(days[Day])
        {
            case 'S':
                        LCD_String("Sun");
                        break;
            case 'M':
                        LCD_String("Mon");
                        break;                
            case 'T':
                        LCD_String("Tue");
                        break;                
            case 'W':   
                        LCD_String("Wed");
                        break;                
            case 't':
                        LCD_String("Thu");
                        break;
            case 'F':
                        LCD_String("Fri");
                        break;                
            case 's':
                        LCD_String("Sat");
                        break;
            default: 
                        break;
                        
        }
        
    }    
}
