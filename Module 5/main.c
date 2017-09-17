#include <iom128.h>
#include <intrinsics.h>
#include <avr_macros.h>
#include "lcd_dog_driver.h"

unsigned int channel_voltage[8];
unsigned char channel_display = 0;
unsigned int channel_limit[] = {0,0,0,0,0,0,0,0};
unsigned char channel_limit_flags[] = {0,0,0,0,0,0,0,0};

void auto_dsp(void)
{
	clear_dsp();
        dsp_buff_1[0] = 'C';
	dsp_buff_1[1] = 'h';
	dsp_buff_1[2] = 'n';
	dsp_buff_1[3] = 'l';
	dsp_buff_1[4] = ' ';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
	
	double vout;
	int value;
        double c1;
        double remain;
          
          channel_display = 0;
	  for(int i = 0; i < 8; i++)
	  {
            dsp_buff_1[5] = channel_display + '1';
	    c1 = channel_voltage[i];
	    vout = (2 * c1 / 65535)* 4096;
	    value = vout;
	    remain = value % 1000;
	    value = value / 1000;
	    dsp_buff_1[8] =  value + '0';
	    value = remain;       
	    dsp_buff_1[9] = '.';
	    remain = value %100;
	    value = value / 100;                
	    dsp_buff_1[10] =  value + '0';
	    value = remain;
	    remain = value %10;
	    value = value / 10;                
	    dsp_buff_1[11] =  value + '0';
	    value = remain;              
	    dsp_buff_1[12] =  value + '0';
	    update_lcd_dog();
	    __delay_cycles(1600000);	//one sec delay
	    __delay_cycles(1600000);
	    __delay_cycles(1600000);
            channel_display++;
	  }
	return;
}

void man_dsp(void)
{
	clear_dsp();

        dsp_buff_1[0] = 'C';
	dsp_buff_1[1] = 'h';
	dsp_buff_1[2] = 'n';
	dsp_buff_1[3] = 'l';
	dsp_buff_1[4] = ' ';
	
	dsp_buff_1[5] = channel_display + '1';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
	
	  double vout;
	  int value;
          double c1;
          double remain;
	
	  c1= channel_voltage[channel_display];
	  vout = (2*c1 / 65535) * 4096;
	  value = vout;
	  remain = value %1000;
	  value = value / 1000;
	  dsp_buff_1[8] =  value + '0';
	  value = remain;       
	  dsp_buff_1[9] = '.';
	  remain = value %100;
	  value = value / 100;                
	  dsp_buff_1[10] =  value + '0';
	  value = remain;
	  remain = value %10;
	  value = value / 10;                
	  dsp_buff_1[11] =  value + '0';
	  value = remain;              
	  dsp_buff_1[12] =  value + '0';
	  update_lcd_dog();
	  __delay_cycles(160000);	//one sec delay
	return;
}

void incr_channel(void)
{
	if(channel_display == 7)
	  channel_display = 0;
	else
	  channel_display++;
	return;
}

void decr_channel(void)
{
  	if(channel_display == 0)
	  channel_display = 7;
	else
	  channel_display--;
	
	return;
}

void DG528_driver(unsigned char channel)
{
  SETBIT(DDRA, 5);
  SETBIT(DDRA, 4);
  SETBIT(DDRA, 3);
  switch (channel)
  {
	case 0: 
	  PORTA_Bit5 = 0;
	  PORTA_Bit4 = 0;
	  PORTA_Bit3 = 0;
	  channel_voltage[0] = ADC161_conv();
	  break;
	  
	 case 1: 
	  PORTA_Bit5 = 0;
	  PORTA_Bit4 = 0;
	  PORTA_Bit3 = 1;
	  channel_voltage[1] = ADC161_conv();
	  break;
	  
	 case 2: 
	  PORTA_Bit5 = 0;
	  PORTA_Bit4 = 1;
	  PORTA_Bit3 = 0;
	  channel_voltage[2] = ADC161_conv();
	  break;
	  
	case 3: 
	  PORTA_Bit5 = 0;
	  PORTA_Bit4 = 1;
	  PORTA_Bit3 = 1;
	  channel_voltage[3] = ADC161_conv();
	  break;
	  
	case 4: 
	  PORTA_Bit5 = 1;
	  PORTA_Bit4 = 0;
	  PORTA_Bit3 = 0;
	  channel_voltage[4] = ADC161_conv();
	  break;
	  
	case 5: 
	  PORTA_Bit5 = 1;
	  PORTA_Bit4 = 0;
	  PORTA_Bit3 = 1;
	  channel_voltage[5] = ADC161_conv();
	  break;
	  
	case 6: 
	  PORTA_Bit5 = 1;
	  PORTA_Bit4 = 1;
	  PORTA_Bit3 = 0;
	  channel_voltage[6] = ADC161_conv();
	  break;
	 
	 case 7: 
	  PORTA_Bit5 = 1;
	  PORTA_Bit4 = 1;
	  PORTA_Bit3 = 1;
	  channel_voltage[7] = ADC161_conv();
	  break;
  }
  return;
}

int ADC161_conv(void)
{
 /*****************CONFIGURATION FOR DIFFERENT LCDs****************************/
/*                 Define the Pins to be used                                 */
#define SS_bar  PORTA_Bit0
#define SCLK    PORTA_Bit1
#define MISO    PINA_Bit2
/***********************END OF CONFIGURATION***********************************/
  	
        unsigned int ADC_read;	//default value for the 16bits
	
	DDRA |= 0x03;	//PORTA will be used. PA0-PA1 are outputs PA2 is input
	//PORTA = 0xF8;	//logic levels at '0' with out pullsup on used pins
        SPCR = 0x00;
        
        SCLK = 1;	//clock CPOL = 1
	SS_bar = 1;
        SS_bar = 0;	//assert 
        
	
	SCLK = 0;	//create pulse
  	SCLK = 1;	//because DOUT is high impedance for a cc
	
	SCLK = 0;	//first bit is 0
	SCLK = 1;	//we do not need to sample
	
	//we start sampling here on the 3rd cc
	for(signed char i = 0; i < 16; i++) 
	{
	  	SCLK = 0;		//sample on falling edge
		SCLK = 1;		//change on rising edge
                ADC_read = ADC_read << 1;
	        if(MISO == 1)
		{       
		  ADC_read|= 0x0001;
                }
	}
	SS_bar = 1; 	//unassert 
	return ADC_read;
}

void null_fcn(void)
{
	return;
}

void incr_10(void)
{
  
  channel_limit_flags[channel_display] = 1;
  if(channel_limit[channel_display] > 4086)
  	channel_limit[channel_display] = 4096;
  else
  	channel_limit[channel_display] += 10;
  
          clear_dsp();
          channel_display = 0;
	  int value = (int)channel_limit[channel_display];

        dsp_buff_1[0] = 'L';
	dsp_buff_1[1] = 'm';
	dsp_buff_1[2] = 't';
	dsp_buff_1[3] = 'c';
	dsp_buff_1[4] = 'h';
	
	dsp_buff_1[5] = channel_display + '1';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
          
          
          
          
          double remain;
          remain = value %1000;
	  value = value / 1000;
	  dsp_buff_1[8] =  value + '0';
	  value = remain;       
	  dsp_buff_1[9] = '.';
	  remain = value %100;
	  value = value / 100;                
	  dsp_buff_1[10] =  value + '0';
	  value = remain;
	  remain = value %10;
	  value = value / 10;                
	  dsp_buff_1[11] =  value + '0';
	  value = remain;              
	  dsp_buff_1[12] =  value + '0';
  	  update_lcd_dog();
  	  return;
}

void decr_10(void)
{
  channel_limit_flags[channel_display] = 1;
  if(channel_limit[channel_display] < 10)
  	channel_limit[channel_display] = 0;
  else
  	channel_limit[channel_display] -= 10;
  
  clear_dsp();
 
        dsp_buff_1[0] = 'L';
	dsp_buff_1[1] = 'm';
	dsp_buff_1[2] = 't';
	dsp_buff_1[3] = 'c';
	dsp_buff_1[4] = 'h';
	
	dsp_buff_1[5] = channel_display + '1';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
          
          int value = (int)channel_limit[channel_display];
          
          
          double remain;
          remain = value %1000;
	  value = value / 1000;
	  dsp_buff_1[8] =  value + '0';
	  value = remain;       
	  dsp_buff_1[9] = '.';
	  remain = value %100;
	  value = value / 100;                
	  dsp_buff_1[10] =  value + '0';
	  value = remain;
	  remain = value %10;
	  value = value / 10;                
	  dsp_buff_1[11] =  value + '0';
	  value = remain;              
	  dsp_buff_1[12] =  value + '0';

  	  update_lcd_dog();
  return;
}

void incr_1(void)
{
  channel_limit_flags[channel_display] = 1;
  if(channel_limit[channel_display] == 4096)
  	channel_limit[channel_display] = 4096;
  else
  	channel_limit[channel_display]++;
  
  	clear_dsp();
 
        dsp_buff_1[0] = 'L';
	dsp_buff_1[1] = 'm';
	dsp_buff_1[2] = 't';
	dsp_buff_1[3] = 'c';
	dsp_buff_1[4] = 'h';
	
	dsp_buff_1[5] = channel_display + '1';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
          
          
          
          int value = (int)channel_limit[channel_display];
          double remain;
          remain = value %1000;
	  value = value / 1000;
	  dsp_buff_1[8] =  value + '0';
	  value = remain;       
	  dsp_buff_1[9] = '.';
	  remain = value %100;
	  value = value / 100;                
	  dsp_buff_1[10] =  value + '0';
	  value = remain;
	  remain = value %10;
	  value = value / 10;                
	  dsp_buff_1[11] =  value + '0';
	  value = remain;              
	  dsp_buff_1[12] =  value + '0';

  	  update_lcd_dog();
  return;
}
/*
void limit_selected(){
    channel_limit_flags[channel_display] = 1;
   int value = (int)channel_limit[channel_display];
   
  
}
*/
void decr_1(void)
{
  channel_limit_flags[channel_display] = 1;
  if(channel_limit[channel_display] == 0)
  	channel_limit[channel_display] = 0;
  else
  	channel_limit[channel_display]--;
  
  clear_dsp();
  
        dsp_buff_1[0] = 'L';
	dsp_buff_1[1] = 'm';
	dsp_buff_1[2] = 't';
	dsp_buff_1[3] = 'c';
	dsp_buff_1[4] = 'h';
	
	dsp_buff_1[5] = channel_display + '1';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
          
          
          int value = (int)channel_limit[channel_display];
          
          double remain;
          remain = value %1000;
	  value = value / 1000;
	  dsp_buff_1[8] =  value + '0';
	  value = remain;       
	  dsp_buff_1[9] = '.';
	  remain = value %100;
	  value = value / 100;                
	  dsp_buff_1[10] =  value + '0';
	  value = remain;
	  remain = value %10;
	  value = value / 10;                
	  dsp_buff_1[11] =  value + '0';
	  value = remain;              
	  dsp_buff_1[12] =  value + '0';

  	  update_lcd_dog();
  return;
}

//****************************************************************************
//states in the fsm
typedef enum {aut, man, limit} state;

//keys on the encoder
typedef enum {ocw, occw, icw, iccw, pb, eol} key;

state present_state;
key keypressed;

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

//*****************************************************************************

#pragma vector = INT1_vect          // Declare vector location.  //CENTER
__interrupt void ISR_INT1(void)   // Declare interrupt function
{
  if(present_state == man)
  {
    keypressed = pb;
    fsm(present_state, keypressed);
  }
}

#pragma vector = INT2_vect          // Declare vector location. //INNER
__interrupt void ISR_INT2(void)     // Declare interrupt function
{
        if(PIND_Bit2 != PIND_Bit4)
        {
          keypressed = icw;
          fsm(present_state, keypressed);
        }
        else
        {
          keypressed = iccw;
          fsm(present_state, keypressed);
        }
}

#pragma vector = INT3_vect          // Declare vector location. //OUTTER
__interrupt void ISR_INT3(void)     // Declare interrupt function
{
  if(PIND_Bit3 != PIND_Bit5)
  {
       keypressed = ocw;
       fsm(present_state, keypressed);
  }
   else
   {
       keypressed = occw;
       fsm(present_state, keypressed);
   }
}


void main(void)
{
  	//change from here
  DDRC = 0xF0;            // High nibble outputs, low nibble inputs 
  PORTC = 0x0F;
  
  DDRD = 0xC0;          //set PORTD for rotary encoder  
  //PORTD = 0x3f
  
  EICRA = 0x5F;   //INT 0(any change in logical signals all others on rising
  EIMSK = 0x0F;      //enable interupt[3:0]
  //stop here
    
  __enable_interrupt();
	
  	DDRB = 0xFF;		//PORTB for LCD
	SETBIT(PORTB, 0);       // unassert slave select
	init_lcd_dog();		//intialize the LCD
	clear_dsp();		//clear all buffers
	
	dsp_buff_1[0] = 'C';
	dsp_buff_1[1] = 'h';
	dsp_buff_1[2] = 'n';
	dsp_buff_1[3] = 'l';
	dsp_buff_1[4] = ' ';
	update_lcd_dog();	
	present_state = aut;
	keypressed = eol;
        fsm(present_state, keypressed);
        
	while(1)
	{
		for(char i = 0; i < 8; i++)
		{
			DG528_driver(i); 	//BACKGROUND TASK 
			__delay_cycles(160000);	//10 conv/s
                        fsm(present_state, eol);
		}
	}
}
