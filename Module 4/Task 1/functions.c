//***************************************************************************
//
// File Name            : finite state machine functions
// Title                : functions.c
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// This file includes all the functions the compiler needs to use to chech the 
//	states of the finite state machines. It outputs the mode onto the console
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//*****************************************************************************

void auto_dsp(void)
{
	printf("auto mode\n");
	return;
}

void man_dsp(void)
{
	printf("man mode\n");
	return;
}

void incr_channel(void)
{
	printf("incr channel\n");
	return;
}

void decr_channel(void)
{
	printf("decr channel\n");
	return;
}