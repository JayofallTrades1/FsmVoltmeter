
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
	dsp_buff_1[6] = ':';
	dsp_buff_1[13] = ' ';
	dsp_buff_1[14] = 'V';
	
	  double vout;
	  int value;
          double c1;
          double remain;
	  for(char i = 0; i < 8; i++)
	  {
	    dsp_buff_1[5] = i + '0';
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
	  vout = (2*c1 / 65535) * 4096;
	  value = vout;
	  
	  if(((channel_limit_flags[channel_display] == 1) && 
	      value > channel_limit[channel_display]))
	  {
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
	    
	    dsp_buff_2[0] = 'L';
	    dsp_buff_2[1] = 'I';
	    dsp_buff_2[2] = 'M';
	    dsp_buff_2[3] = 'I';
	    dsp_buff_2[4] = 'T';	
	    dsp_buff_2[5] = ' ';
	    
	    dsp_buff_2[6] = 'E';
	    dsp_buff_2[7] = 'X';
	    dsp_buff_2[8] = 'C';
	    dsp_buff_2[9] = 'E';	
	    dsp_buff_2[10] = 'E';
	    dsp_buff_2[11] = 'D';
	    dsp_buff_2[12] = 'E';
	    dsp_buff_2[12] = 'D';
	    dsp_buff_2[14] = '!';	
	    dsp_buff_2[55] = '!';
	    
	    update_lcd_dog();
	  __delay_cycles(160000);	//one sec delay
	  }
	  else
	  {
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
	  }
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
  char thousands, hundreds, tens, ones, rem;
  thousands = channel_limit[channel_display] / 1000 + '0';
  rem = thousands % 1000;
  hundreds = rem / 100 + '0';
  rem = rem % 100;
  tens = rem / 10 + '0';
  ones = rem % 10 + '0';
  
  dsp_buff_1[0] = 'C';
  dsp_buff_1[1] = 'h';
  dsp_buff_1[2] = 'n';
  dsp_buff_1[3] = 'l';
  dsp_buff_1[4] = ' ';
  dsp_buff_1[5] = channel_display + '0';
  
  dsp_buff_2[0] = 'L';
  dsp_buff_2[1] = 'i';
  dsp_buff_2[2] = 'm';
  dsp_buff_2[3] = 'i';
  dsp_buff_2[4] = 't';
  dsp_buff_2[5] = ' ';
  dsp_buff_2[6] = '=';
  dsp_buff_2[7] = ' ';
  dsp_buff_2[8] = thousands;
  dsp_buff_2[9] = '.';
  dsp_buff_2[10] = hundreds;
  dsp_buff_2[11] = tens;
  dsp_buff_2[12] = ones;
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
  char thousands, hundreds, tens, ones, rem;
  thousands = channel_limit[channel_display] / 1000 + '0';
  rem = thousands % 1000;
  hundreds = rem / 100 + '0';
  rem = rem % 100;
  tens = rem / 10 + '0';
  ones = rem % 10 + '0';
  
  dsp_buff_1[0] = 'C';
  dsp_buff_1[1] = 'h';
  dsp_buff_1[2] = 'n';
  dsp_buff_1[3] = 'l';
  dsp_buff_1[4] = ' ';
  dsp_buff_1[5] = channel_display + '0';

  dsp_buff_2[0] = 'L';
  dsp_buff_2[1] = 'i';
  dsp_buff_2[2] = 'm';
  dsp_buff_2[3] = 'i';
  dsp_buff_2[4] = 't';
  dsp_buff_2[5] = ' ';
  dsp_buff_2[6] = '=';
  dsp_buff_2[7] = ' ';
  dsp_buff_2[8] = thousands;
  dsp_buff_2[9] = '.';
  dsp_buff_2[10] = hundreds;
  dsp_buff_2[11] = tens;
  dsp_buff_2[12] = ones;
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
  char thousands, hundreds, tens, ones, rem;
  thousands = channel_limit[channel_display] / 1000 + '0';
  rem = thousands % 1000;
  hundreds = rem / 100 + '0';
  rem = rem % 100;
  tens = rem / 10 + '0';
  ones = rem % 10 + '0';
  
  dsp_buff_1[0] = 'C';
  dsp_buff_1[1] = 'h';
  dsp_buff_1[2] = 'n';
  dsp_buff_1[3] = 'l';
  dsp_buff_1[4] = ' ';
  dsp_buff_1[5] = channel_display + '0';
  
  dsp_buff_2[0] = 'L';
  dsp_buff_2[1] = 'i';
  dsp_buff_2[2] = 'm';
  dsp_buff_2[3] = 'i';
  dsp_buff_2[4] = 't';
  dsp_buff_2[5] = ' ';
  dsp_buff_2[6] = '=';
  dsp_buff_2[7] = ' ';
  dsp_buff_2[8] = thousands;
  dsp_buff_2[9] = '.';
  dsp_buff_2[10] = hundreds;
  dsp_buff_2[11] = tens;
  dsp_buff_2[12] = ones;
  update_lcd_dog();
  return;
}

void decr_1(void)
{
  channel_limit_flags[channel_display] = 1;
  if(channel_limit[channel_display] == 0)
  	channel_limit[channel_display] = 0;
  else
  	channel_limit[channel_display]--;
  
  clear_dsp();
  char thousands, hundreds, tens, ones, rem;
  thousands = channel_limit[channel_display] / 1000 + '0';
  rem = thousands % 1000;
  hundreds = rem / 100 + '0';
  rem = rem % 100;
  tens = rem / 10 + '0';
  ones = rem % 10 + '0';
  
  dsp_buff_1[0] = 'C';
  dsp_buff_1[1] = 'h';
  dsp_buff_1[2] = 'n';
  dsp_buff_1[3] = 'l';
  dsp_buff_1[4] = ' ';
  dsp_buff_1[5] = channel_display + '0';
  
  dsp_buff_2[0] = 'L';
  dsp_buff_2[1] = 'i';
  dsp_buff_2[2] = 'm';
  dsp_buff_2[3] = 'i';
  dsp_buff_2[4] = 't';
  dsp_buff_2[5] = ' ';
  dsp_buff_2[6] = '=';
  dsp_buff_2[7] = ' ';
  dsp_buff_2[8] = thousands;
  dsp_buff_2[9] = '.';
  dsp_buff_2[10] = hundreds;
  dsp_buff_2[11] = tens;
  dsp_buff_2[12] = ones;
  update_lcd_dog();
  return;
}
