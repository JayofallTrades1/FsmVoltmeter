/*
Name: Suphasith Usdonvudhikai 109219981
Class: ESE 381 Lab Sec 01 
Module 0
File: sws_alu.c
Description: implement a mode logical calculator.
  Inputs: 8-bit switches; PD7-PD6 are used for mode selections; Outputs: LED bargraph shows calculations
  00 -> AND; 01 -> OR; 10 -> EXOR; 11 -> complement
*/

#include <iom128.h>

union  
{
  unsigned char byteimage;
  struct bitimage 
  {
    unsigned char imbit0:1,
                  imbit1:1,
                  imbit2:1,
                  imbit3:1,
                  imbit4:1,
                  imbit5:1,
                  imbit6:1,
                  imbit7:1;
  } temp;
};

int main(void)
{
  
  DDRD = 0x00;                          //setup PORTD as inputs     
  PORTD = 0xFF;                         //turn on pull-ups for PORTD
  DDRB = 0xFF;                          //setup PORTB as outputs
  
  while(1)
  {
    byteimage = PIND;
    
    if(temp.imbit7 == 0 && temp.imbit6 == 0)
    {
      unsigned char temp = byteimage >> 5;
      temp = byteimage & temp;
      PORTB = ~temp;
    }
    else if(temp.imbit7 == 0 && temp.imbit6 == 1)
    {
      unsigned char temp = byteimage >> 5;
      temp = byteimage | temp;
      temp &= 0x07;
      PORTB = ~temp;
    }
    else if(temp.imbit7 == 1 && temp.imbit6 == 0)
    {
      unsigned char temp = byteimage >> 5;
      temp = byteimage ^ temp;
      temp &= 0x07;
      PORTB = ~temp;
    }
    else
    {
      byteimage &= 0x07;
      PORTB = ~byteimage;
    }
  }
}