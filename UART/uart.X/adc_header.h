/* 
 * File:   adc_header.h
 * Author: ASUS
 *
 * Created on 1 de octubre de 2021, 11:26 AM
 */

#ifndef ADC_HEADER_H
#define	ADC_HEADER_H

#ifdef	__cplusplus
extern "C" {
#endif

#include<pic18f4550.h>
#include<xc.h>

void ADC_Init();
int ADC_Read(int);


#ifdef	__cplusplus
}
#endif

#endif	/* ADC_HEADER_H */

