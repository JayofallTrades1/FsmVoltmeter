//***************************************************************************
//
// File Name            : rotary_isr
// Title                : rotary encoder isr 
// Date                 : 02/26/2015
// Version              : 1.0
// Target MCU           : ATmega128 @ 16 MHz
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// When rotary encoder interupt happens the count is incremented and displayed
//      screen. There are three interupts. The inner, outer, and center.
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version 
// 
//
//**************************************************************************

//#define debug   //this can be uncommented to remove delays for simulation

#include <iom128.h>         //Atmega128 definitions
#include <intrinsics.h>     //Intrinsic functions.
#include <avr_macros.h>     //Useful macros.

extern char inner_count;
extern char outer_count;
extern char center_count;

#pragma vector = INT1_vect          // Declare vector location.
__interrupt void ISR_INT1(void)   // Declare interrupt function
{
    if(center_count == 99)
      center_count = 0;
    else
      center_count++;
}

#pragma vector = INT2_vect          // Declare vector location.
__interrupt void ISR_INT2(void)     // Declare interrupt function
{
  if(PIND_Bit2 != PIND_Bit4)
  {
    if(inner_count == 99)
      inner_count = 0;
    else
      inner_count++;
  }
  else
  {
    if(inner_count == 0)
      inner_count = 99;
    else
      inner_count--;
  }
}

#pragma vector = INT3_vect          // Declare vector location.
__interrupt void ISR_INT3(void)     // Declare interrupt function
{
  if(PIND_Bit3!= PIND_Bit5)
  {
    if(outer_count == 99)
      outer_count = 0;
    else
      outer_count++;
  }
  else
  {
    if(outer_count == 0)
      outer_count = 99;
    else
      outer_count--;
  }
}
