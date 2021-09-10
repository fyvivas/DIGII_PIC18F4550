/*!
\file   pinout.h
\date   2021-09-10
\author Fulvio Vivas <fulvio.vivas@unicauca.edu.co>
\brief  configuration pines application.

\par Copyright
Information contained herein is proprietary to and constitutes valuable
confidential trade secrets of unicauca, and
is subject to restrictions on use and disclosure.

\par
Copyright (c) unicauca 2020. All rights reserved.

\par
The copyright notices above do not evidence any actual or
intended publication of this material.
******************************************************************************
*/


#include <xc.h>
#include <pic18f4550.h>  /*Header file PIC18f4550 definitions*/


#ifndef PINOUT_H
#define	PINOUT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define LED_POWER LATB0
#define CFG_LED_POWER TRISB0

#define BTN_BLINK PORTBbits.RB7
#define CFG_BTN_BLINK TRISB7

#ifdef	__cplusplus
}
#endif

#endif	/* PINOUT_H */

