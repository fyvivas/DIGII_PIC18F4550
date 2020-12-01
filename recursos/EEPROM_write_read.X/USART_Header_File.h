
#ifndef USART_HEADER_FILE_H
#define	USART_HEADER_FILE_H

#include <pic18f4550.h>

void USART_Init(int);
void USART_TransmitChar(char);
char USART_ReceiveChar();
void USART_SendString(char *);
void MSdelay(unsigned int val);

#define F_CPU 8000000/64

#endif	/* USART_HEADER_FILE_H */

