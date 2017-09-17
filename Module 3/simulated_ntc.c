//***************************************************************************
//
// File Name            : simulated_ntc.c
// Title                : main file for ADC161S626 module
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
//	This includes the main fucntion in order to carry out the calculations
//	The function ADC161_conv is called and the value of the 16 bit ADC is
//	converted and outputted to the LCD for the user to see. The output 
//	is shown as a voltage with 1mv resolution.
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
#include "lcd_dog_driver.h"
#include "ADC161S626_driver.h"

int main(void)
{
	DDRB = 0xFF;		//PORTB for LCD
	SETBIT(PORTB, 0);       // unassert slave select
	init_lcd_dog();		//intialize the LCD
	clear_dsp();		//clear all buffers
		
	double vout;		
	int c;
	
	while(1)
	{
		c = ADC161_conv();	//store 16bit value into a variable
		vout = (c / 65535) * (4096 / 1000); //conversion of ADC reading
		printf(".3f", vout);	  //output to LCD
	}
}