/*************************************************************************
NAME: RotaryEncoder
AUTHOR: Suphasith Usdonvudhikai
DATE: 3/3/2015
DESCRIPION: This file contains the main function to process the rotary 
	encoder. Ports have been configured and outputs will be to lcd_dog.
	An algorithm was used in orde to convert the integer to ascii 
	characters. 

Warnings             : none
Restrictions         : none
Algorithms           : integer to ascii
References           : none
Memory: Stack size must be at least 0x40.
Revision History: initial version.
**************************************************************************/
#include <iom128.h>
#include "lcd_dog_driver.h"
#include <avr_macros.h>
#include <intrinsics.h>

char keycode;         // Holds keycode
char inner_count = 0;
char outer_count = 0;
char center_count = 0;

int main(void)
{
  DDRB = 0xFF;             // Set PortB to outputs(SPI interface)
  SETBIT(PORTB, 0);       // unassert slave select
  
  DDRC = 0xF0;            // High nibble outputs, low nibble inputs 
  PORTC = 0x0F;
  
  DDRD = 0xC0;          //set PORTD for rotary encoder  
  //PORTD = 0x3f
  
  EICRA = 0x5F;   //INT 0(any change in logical signals all others on rising
  EIMSK = 0x0F;      //enable interupt[3:0]
  
  init_lcd_dog();       //init spi in lcd dog
  clear_dsp();          //clear all the buffers
  update_lcd_dog();     //show strings on display
  
    __enable_interrupt();           //Enable global interrupts.
    
    char text1[NUMCHARS] = {'I', 'N', 'N', 'E', 'R', ' ', 'C', 'O', 'U', 'N', 'T'};
    char text2[NUMCHARS] = {'O', 'U', 'T', 'E', 'R', ' ', 'C', 'O', 'U', 'N', 'T'};
    char text3[NUMCHARS] = {'C', 'E', 'N', 'T', 'E', 'R', ' ', 'C', 'O', 'U', 'N', 'T'};
    
    while(1)
    { 
        text1[12] = inner_count / 10 + '0';
        text1[13] = inner_count % 10 + '0';
        text2[12] = outer_count / 10 + '0';
        text2[13] = outer_count % 10 + '0';
        text3[13] = center_count / 10 + '0';
        text3[14] = center_count % 10 + '0';
        load_msg(dsp_buff_1, text1);
	load_msg(dsp_buff_2, text2);
	load_msg(dsp_buff_3, text3);     
        update_lcd_dog(); 
      }
    } 