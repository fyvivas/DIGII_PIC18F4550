
/*
 * PIC18F4550 I2C Master Header File
 * http://www.electronicwings.com
 */ 

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef I2C_Master_H
#define	I2C_Master_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define F_OSC 8000000                       /* define F_OSC for finding bit rate 
                                               here oscillator frequency is 8 MHz so define as 800000 */
#define I2C_CLOCK 100000                    /* I2C clock frequency is 100 kHz*/
#define BITRATE ((F_OSC/(4*I2C_CLOCK))-1)  /* find bit rate to assign this value to SSPADD register*/

void I2C_Ready();                           /* check and wait weather I2C is ready or not */
void I2C_Init();                            /* initialize I2C register configuration*/
char I2C_Start(char);                       /* send start pulse along with slave device address */
void I2C_Start_Wait(char);                  /* send start pulse along with slave device address 
                                             * and wait if not work */
char I2C_Repeated_Start(char);              /* send repeated start pulse along with device write address*/
char I2C_Stop();                            /* send stop pulse*/
char I2C_Write(unsigned char);              /* transmit/write data/address to slave device */
void I2C_Ack();                             /* send acknowledge from master for another read */
void I2C_Nack();                            /* send negative acknowledge from master for stop reading */
char I2C_Read(char flag);                   /* read data from slave devices*/




#endif	/* I2C_Master_H */

