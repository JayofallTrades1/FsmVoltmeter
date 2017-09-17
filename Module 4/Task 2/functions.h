//***************************************************************************
//
// File Name            : finite state machine functions (header)
// Title                : functions.h
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// This file includes all the functions the compiler needs to use to chech the 
//	states of the finite state machines. It outputs the mode onto the console
//	this is only the header file. This file also include the global variables
//	needed by all files
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//*****************************************************************************
unsigned int channel_voltage[8];
unsigned char channel_conv;
unsigned char channel_display = 0;

	
void auto_dsp();
void man_dsp();
void incr_channel();
void decr_channel();
void null_fcn();

void DG528_driver(unsigned char channel);
unsigned int ADC161_conv(void);
