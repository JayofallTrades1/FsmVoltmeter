//***************************************************************************
//
// File Name            : ADC161S626_main.c
// Title                : C file for ADC161S626 module
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
//	This file includes only the main function and is used in order to 
//	calibrate the timing of the SPI transfer. This is necessary to ensure
//	that all 16 bits are transfer accurately and precisely.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//*****************************************************************************

#include <iom128.h>
#include <intrinsics.h>
#include <avr_macros.h>
#include "ADC161S626_driver.h"

int main(void)
{
	while(1)
	{
		ADC161_conv();		//start conversion
		__delay_cycles(256);	//small delay
	}
}