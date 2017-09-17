//***************************************************************************
//
// File Name            : ADC161S626_display_main.c
// Title                : C file for ADC161S626 module
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// 	this file contains the main file in order to test the 16 bit resolution
//	after the conversion of the ADC, the value is stored into a 16bit 
//	variable and then outputted in binary to the LCD. 
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
#include "lcd_dog_driver.h"

int main(void)
{
 	DDRB = 0xFF;		//setup PORTB as outputs for LCD
	SETBIT(PORTB, SS_bar);	//unassert the LCD 
	init_lcd_dog();		//initialize the LCD
	clear_dsp();		//clear all the buffers
		
	int ch;			//16bit value for ADC_read
	
	while(1)
	{ 
		ch = ADC161_conv();		//conversion
		printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",	//print values
		       (ch&0x8000)?'1':'0',			//in binary
		       (ch&0x4000)?'1':'0',
		       (ch&0x2000)?'1':'0',
		       (ch&0x1000)?'1':'0',
		       (ch&0x0800)?'1':'0',
		       (ch&0x0400)?'1':'0',
		       (ch&0x0200)?'1':'0',
		       (ch&0x0100)?'1':'0',
		       (ch&0x0080)?'1':'0',
		       (ch&0x0040)?'1':'0',
		       (ch&0x0020)?'1':'0',
		       (ch&0x0010)?'1':'0',
		       (ch&0x0008)?'1':'0',
		       (ch&0x0004)?'1':'0',
		       (ch&0x0002)?'1':'0',
		       (ch&0x0001)?'1':'0'
			); 
		update_lcd_dog();		//display on lcd;
		__delay_cycles(8000000);	//delay cycles for 2 conv/sec	
	}
}