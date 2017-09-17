//***************************************************************************
//
// File Name            : ADC161S626_driver.c
// Title                : C file for ADC161S626 module
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// This file includes all the functions the compiler needs to use ADC161S626
// references of the functions and variables written in the file .
// Configurations can be made in the header files in order to switch ports. 
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//*****************************************************************************

#include "ADC161S626_driver.h"
#include <avr_macros.h>
#include <iom128.h>
#include <intrinsics.h>

signed int ADC161_conv(void)
{
 /*****************CONFIGURATION FOR DIFFERENT LCDs****************************/
/*                 Define the Pins to be used                                 */
#define SS_bar  PORTA_Bit0
#define SCLK    PORTA_Bit1
#define MISO    PINA_Bit2
/***********************END OF CONFIGURATION***********************************/
  	
  	signed int ADC_read = 0x0000;	//default value for the 16bits
	
	DDRA = 0x03;	//PORTA will be used. PA0-PA1 are outputs PA2 is input
	PORTA = 0xF8;	//logic levels at '0' with out pullsup on used pins
	
	SCLK = 1;	//clock CPOL = 1
	SS_bar = 0;	//assert 
	
	SCLK = 0;	//create pulse
	SCLK = 1;	//because DOUT is high impedance for a cc
	
	SCLK = 0;	//first bit is 0
	SCLK = 1;	//we do not need to sample
	
	//we start sampling here on the 3rd cc
	for(signed char i = 15; i >= 0; i--) 
	{
	  	SCLK = 0;		//sample on falling edge
		__delay_cycles(5);	//50 percent duty cycle
		SCLK = 1;		//change on rising edge
		if(MISO)		//if input is 1
		  SETBIT(ADC_read, i);	//set bit
		else			//else clear bit
		  CLEARBIT(ADC_read, i);
	}
	SS_bar = 1; 	//unassert 
	return ADC_read;
}