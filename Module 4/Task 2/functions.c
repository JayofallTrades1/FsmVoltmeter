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
//	states of the finite state machines. It outputs the mode onto the screen
//	of the LCD
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
#include "functions.h"
#include "lcd_dog_driver.h"

void auto_dsp(void)
{
	clear_dsp();
	dsp_buff_1[0] = 'C';
	dsp_buff_1[1] = 'h';
	dsp_buff_1[2] = 'n';
	dsp_buff_1[3] = 'l';
	dsp_buff_1[4] = ' ';
	dsp_buff_1[5] = channel_display + '0';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
	
	  double vout;
	  int value;
          double c1;
          double remain;
	  for(char i = 0; i < 8; i++)
	  {
	    c1= channel_voltage[i];
	    vout = (2*c1 / 65535)* 4096;
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
	    __delay_cycles(160000);
	    __delay_cycles(160000);
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
	dsp_buff_1[5] = channel_display + '0';
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
	
	  double vout;
	  int value;
          double c1;
          double remain;
	  
	  c1= channel_voltage[channel_display];
	  vout = (2*c1 / 65535)* 4096;
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

unsigned int ADC161_conv(void)
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
	        if(MISO == 1) {       
		  ADC_read|= 0x0001;
                }
	}
	SS_bar = 1; 	//unassert 
	return ADC_read;
}

