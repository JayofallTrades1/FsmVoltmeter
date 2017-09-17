/*
Name: Suphasith Usdonvudhikai 109219981
Class: ESE 381 Lab Sec 01 
Module 0 
File: sws_AND.c
Description: implement 4 2-input AND gates. Inputs: 8-bit switches (PD7-PD4 AND PD3-PD0); Outputs: LED bargraph
*/

#include <iom128.h>

int main(void)
{
  char temp0;
  
  DDRD = 0x00;                          //setup PORTD as inputs     
  PORTD = 0xFF;                         //turn on pull-ups for PORTD
  DDRB = 0xFF;                          //setup PORTB as outputs
  
  while(1)
  {
    temp0 = PIND; 
    char temp1 = temp0 >> 4;               //shifts the high nibble to the low nibble and stores it 
    temp0 = temp0 & temp1;                //AND operation
    PORTB = ~temp0;                       //outputs to PORTB active low
  }
}