//***************************************************************************
//
// File Name            : finite state machine main
// Title                : fsm.c
// Date                 : 03/13/2015
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
//
// DESCRIPTION This code contains the neccesary setups in order to implement
//	a finite state machine. This project contains two state.Auto and manual.
//	The transitions from state to state with the given input an outputs
//	are also represented by the transition tables. The main function
//	at the very end contains the necesary inputs in order to test that the 
//	the states enter correct next states with given inputs.
//	
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
//*****************************************************************************

#include <iom128.h>
//#include "functions.h"
#include <intrinsics.h>
#include <avr_macros.h>
#include "lcd_dog_driver.h"

//states in the fsm
typedef enum {aut, man} state;

//keys on the encoder
typedef enum {ocw, occw, icw, iccw, eol} key;

//fucntions to implement and to be called by fsm
extern void auto_dsp();
extern void man_dsp();
extern void incr_channel();
extern void decr_channel();
extern void null_fcn();

//global variable for present state
state present_state;

//declare type task_fn_ptr as a pointer to a task function
typedef void (* task_fn_ptr)();

typedef struct {
    key keyval;
    state next_state;
    task_fn_ptr tf_ptr;
} transition;

const transition auto_transitions [] = 
{
//input   next state   task
  {ocw,    man,        man_dsp},
  {occw,   man,        man_dsp},
  {eol,    aut,        auto_dsp}
};

const transition man_transitions [] = 
{
//input   next state   task
  {ocw,    aut,        auto_dsp},
  {occw,   aut,        auto_dsp},
  {icw,    man,        incr_channel},
  {iccw,   man,        decr_channel},
  {eol,    man,        man_dsp}
};

const transition * ps_transitions_ptr[] = 
{
    auto_transitions,
    man_transitions
};

void fsm(state ps, key keyval)
{
    int j;
    for(j = 0; ((ps_transitions_ptr[ps][j].keyval != keyval)
		&& (ps_transitions_ptr[ps][j].keyval != eol)); j++){};
      
    ps_transitions_ptr[ps][j].tf_ptr();
    present_state = ps_transitions_ptr[ps][j].next_state;
}


void main(void)
{
  	
	
  	DDRB = 0xFF;		//PORTB for LCD
	SETBIT(PORTB, 0);       // unassert slave select
	init_lcd_dog();		//intialize the LCD
	clear_dsp();		//clear all buffers
	
	key keypressed = ocw;		
	present_state = aut;
	
	while(1)
	{
		for(char i = 0; i < 8; i ++)
		{
			DG528_driver(i); 	//BACKGROUND TASK 
			__delay_cycles(16000);	//10 conv/s
		}
		fsm(present_state, keypressed);
	}
}
