/******************************************************************************












*****************************************************************************/

#include <iom128.h>
//#include "functions.h"
#include <intrinsics.h>
#include <avr_macros.h>
#include "lcd_dog_driver.h"

//states in the fsm
typedef enum {aut, man, limit} state;

//keys on the encoder
typedef enum {ocw, occw, icw, iccw, pb, eol} key;

//fucntions to implement and to be called by fsm
extern void auto_dsp();
extern void man_dsp();
extern void incr_channel();
extern void decr_channel();
extern void incr_10();
extern void decr_10();
extern void incr_1();
extern void decr_1();
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

const transition limit_transitions [] = 
{
//input   next state   task
  {ocw,    limit,        incr_10},
  {occw,   limit,        decr_10},
  {icw,    limit,        incr_1},
  {iccw,   limit,        decr_1},
  {pb,     man,          man_dsp},
  {eol,    limit,        null_fcn}
};

const transition * ps_transitions_ptr[] = 
{
    auto_transitions,
    man_transitions,
    limit_transitions
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
	
	
	key keypressed = pb;		
	present_state = man;
	
	while(1)
	{
		for(char i = 0; i < 8; i++)
		{
			DG528_driver(i); 	//BACKGROUND TASK 
			__delay_cycles(16000);	//10 conv/s
		}
		fsm(present_state, keypressed);
	}
}
