/*************************************************************************
NAME: lcd_dog_test
AUTHOR: Suphasith Usdonvudhikai
DATE: 2/26/2015
DESCRIPION: This file tes the LCD by printing characters to all lines 

CONFIGUATIONS: This is default at 3 line display with 16 characters per line, 
  the clock speed is set at 16 mhz but can be changed in the configuration 
  file. 

Warnings             : none
Restrictions         : none
Algorithms           : none
References           : none
Memory: Stack size must be at least 0x40.
Revision History: initial version.
**************************************************************************/

#include <iom128.h>
#include "lcd_dog_driver.h"
#include <avr_macros.h>
#include <intrinsics.h>


int main(void)
{
  DDRB = 0xFF;                          //setup PORTB for lcd test
  SETBIT(PORTB, SS_bar);                //unassert slave select
  init_lcd_dog();                       //intializes the lcd spi
  clear_dsp();                          //only clears the buffers

  char message_1[] = {'T', 'e', 's', 't', ' ', 'M', 'e', 's', 's', 'a', 'g', 'e', ' ', '0', '0', '1'};
  
#ifdef LINE_2_ON
  char message_2[] = {'T', 'e', 's', 't', ' ', 'M', 'e', 's', 's', 'a', 'g', 'e', ' ', '0', '0', '2'};
#endif
  
#ifdef LINE_3_ON
  char message_3[] = {'T', 'e', 's', 't', ' ', 'M', 'e', 's', 's', 'a', 'g', 'e', ' ', '0', '0', '3'};
#endif
  
  load_msg(dsp_buff_1, message_1);      //loads the values of the string message into the buffers

#ifdef LINE_2_ON
  load_msg(dsp_buff_2, message_2);
#endif

#ifdef LINE_3_ON
  load_msg(dsp_buff_3, message_3);
#endif 

  update_lcd_dog();                     //updates and shows the strings on display
  while(1){};                           //infinite loop
}
