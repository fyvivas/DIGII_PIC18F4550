


#include "USART_Header_File.h"


void USART_Init(int baud_rate)
{
    float temp;
    TRISC6=0;                       /*Make Tx pin as output*/
    TRISC7=1;                       /*Make Rx pin as input*/
    temp=(((float)(F_CPU)/(float)baud_rate)-1);     
    SPBRG=(int)temp;                /*baud rate=9600 SPBRG=(F_CPU /(64*9600))-1*/
    TXSTA=0x20;                     /*TX enable*/ 
    RCSTA=0x90;                     /*RX enable and serial port enable */
}
//*******************RECEIVE FUNCTION*****************************************//
char USART_ReceiveChar()
{

    while(RCIF==0);                 /*wait for receive interrupt flag*/
    return(RCREG);                  /*receive data is stored in RCREG register and return to main program */
}
//******************TRANSMIT FUNCTION*****************************************// 
void USART_TransmitChar(char out)
{        
        while(TXIF==0);            /*wait for transmit interrupt flag*/
        TXREG=out;                 /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/    
}

void USART_SendString(char *out)
{
   while(*out!='\0')
   {    
        while(TXIF==0);            /*wait for transmit interrupt flag to set which indicates TXREG is ready
                                    for another transmission*/
        USART_TransmitChar(*out);
        out++;
   }
}

void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<=val;i++)
     for(j=0;j<100;j++);
 }
