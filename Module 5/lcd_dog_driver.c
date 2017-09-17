/*************************************************************************
NAME: lcd_dog_driver
AUTHOR: Suphasith Usdonvudhikai
DATE: 2/26/2015
DESCRIPION: This file contains all the necessary drivers in order to 
  initialize the SPI interface from the LCD to the MCU. This driver will 
  work for any ST7036 drivers. Configurations must be made for the different
  displays in the header file (lcd_dog_driver.h). 

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

//Include ATmega128 definitions
#include <iom128.h>
#include "lcd_dog_driver.h"
#include <avr_macros.h>
#include <intrinsics.h>

static char index = 0;           // index into display buffer

char dsp_buff_1[NUMCHARS];       //initialize the buffers 
#ifdef LINE_2_ON
char dsp_buff_2[NUMCHARS];
#endif
#ifdef LINE_3_ON
char dsp_buff_3[NUMCHARS];
#endif

//*********************************************
// Function             : void clear_dsp(void)
// Date and version     : 02/26/2015, version 2.0
// Target MCU           : ATmega128
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// Clears the display buffer. Treats each character array separately.
// NOTE: update_dsp must be called after to see results
//
// Modified: to be used with different configurations
//******************************************************************************
void clear_dsp(void)
{
  // assuming buffers might not be contiguous
  for(char i = 0; i < NUMCHARS; i++)
    dsp_buff_1[i] = ' ';
 
#ifdef LINE_2_ON
  for(char i = 0; i < NUMCHARS; i++)
    dsp_buff_2[i] = ' ';
#endif 
  
#ifdef LINE_3_ON
  for(char i = 0; i < NUMCHARS; i++)
    dsp_buff_3[i] = ' ';  
#endif
  
  index = 0;
  return;
}


//*************************************************
// Function             : int putchar(int c)
// Date and version     : 02/26/2015, version 2.0
// Target MCU           : ATmega128
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// This function displays a single ascii chararacter c on the lcd at the
// position specified by the global variable index
// NOTE: update_dsp must be called after to see results
// 
//
// Modified: to be used with different configurations
//******************************************************************************
int putchar(int c)
{
  if (index < NUMCHARS) 
    dsp_buff_1[index++] = (char)c;
  
#ifdef LINE_2_ON
  else if (index < NUMCHARS * 2)
    dsp_buff_2[index++ - NUMCHARS] = (char)c;
#endif
  
 #ifdef LINE_3_ON
  else if (index < NUMCHARS * 3)
    dsp_buff_3[index++ - NUMCHARS * 2] = (char)c;
#endif
  
  else
  {
    index = 0;
    dsp_buff_1[index++] = (char)c;
  }
  return c;
}

//************************
//NAME:       init_spi_lcd
//ASSUMES:    IMPORTANT: PortB set as output (during program init)
//RETURNS:    nothing
//MODIFIES:   DDRB, SPCR
//CALLED BY:  init_dsp, update
//DESCRITION: init SPI port for command and data writes to LCD via SPI
//********************************************************************
void init_spi_lcd(void)
{
  volatile char IOReg;
  SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA)|(1<<SPR1)|(1<<SPR0); //setup spi
  IOReg = SPSR;                         //kill spurious data
  IOReg = SPDR;                         
  return;
}

/********************************
;NAME:       lcd_spi_transmit_CMD
;ASSUMES:    char temp = byte for LCD.
;            SPI port is configured.
;RETURNS:    nothing
;MODIFIES:   nothing 
;CALLED BY:  init_dsp, update
;DESCRITION: outputs a byte passed in r16 via SPI port. Waits for data
;            to be written by spi port before continuing.
;*********************************************************************/
void lcd_spi_transmit_CMD(unsigned char temp)
{
  volatile char IOReg;          
  
  CLEARBIT(PORTB, RS);          //RS = 0 Command
  CLEARBIT(PORTB, SS_bar);      //SS_bar = selected 
  
  SPDR = temp;                  //write data to SPI port
  
  while (!(SPSR & (1<<SPIF))){} //wait until transmission is complete(busy flag)
  IOReg = SPDR;                  //kill spurious data
  SETBIT(PORTB, SS_bar);        //SS_bar deselect         
  return;
}

/*********************************
;NAME:       lcd_spi_transmit_DATA
;ASSUMES:    char temp = data to be sent to DRAM
;            SPI port is configured.
;RETURNS:    nothing
;MODIFIES:   nothing
;CALLED BY:  init_dsp, update
;DESCRITION: outputs a byte passed in r16 via SPI port. Waits for
;            data to be written by spi port before continuing.
;*****************************************************************/
void lcd_spi_transmit_DATA(unsigned char temp)
{
  volatile char IOReg; 
  
  SETBIT(PORTB, RS);            //RS = 1 = data 
  CLEARBIT(PORTB, SS_bar);      //SS_bar = selected
  
  IOReg = SPSR;                 //kill spurious data and clear SPIF bit
  IOReg = SPDR;
  SPDR = temp;                  //send byte to SPI port
  
  while (!(SPSR & (1<<SPIF))){} //wait for transmission to complete
  IOReg = SPDR;                 //clears SPIF flag and kills data
  SETBIT(PORTB, SS_bar);        //SS_bar = deselected
  return;
}

/************************
;NAME:       init_lcd_dog
;ASSUMES:    nothing
;RETURNS:    nothing
;MODIFIES:   R16, R17
;CALLED BY:  main application
;DESCRITION: inits DOG module LCD display for SPI (serial) operation.
;NOTE:  Can be used as is with MCU clock speeds of 4MHz or less.
;********************************************************************/
void init_lcd_dog(void)
{
  init_spi_lcd();                       //init SPI PORT
  __delay_cycles(400000 * clk_speed);    //startup delay
  
  lcd_spi_transmit_CMD(0x39);           //send function set #1
  __delay_cycles(300 * clk_speed);
  
  lcd_spi_transmit_CMD(0x39);           //send function set #2
  __delay_cycles(300 * clk_speed);
  
  lcd_spi_transmit_CMD(0x1E);           //set bias value
  __delay_cycles(300 * clk_speed);
  
  lcd_spi_transmit_CMD(0x50);           //0x50 nominal (delicate adjustment).
  __delay_cycles(300 * clk_speed);       //power control

  lcd_spi_transmit_CMD(0x6C);           //follower mode
  __delay_cycles(400000 * clk_speed);     
  
  lcd_spi_transmit_CMD(0x77);           //contrast set
  __delay_cycles(300 * clk_speed);
  
   lcd_spi_transmit_CMD(0x0C);           //display on, cursor off, blink off
  __delay_cycles(300 * clk_speed);
  
   lcd_spi_transmit_CMD(0x01);           //clear display cursor home
  __delay_cycles(300 * clk_speed);
  
   lcd_spi_transmit_CMD(0x06);           //clear display cursor home
  __delay_cycles(300 * clk_speed);
  
  return;
}

/************************
;NAME:       update_lcd_dog
;ASSUMES:    nothing
;RETURNS:    nothing
;MODIFIES:   nothing
;CALLED BY:  main application
;DESCRITION: inits DOG module LCD display for SPI (serial) operation.
;NOTE:  Can be used as is with MCU clock speeds of 4MHz or less.
;********************************************************************/
void update_lcd_dog(void)
{
  init_spi_lcd();                       //init SPI port for LCD
  
  lcd_spi_transmit_CMD(0x80);           //init DDRAM addr-ctr 
  __delay_cycles(300 * clk_speed);
  for(int i = 0; i < NUMCHARS; i++)     
  {
    lcd_spi_transmit_DATA(dsp_buff_1[i]);   //loop construct to send characters
    __delay_cycles(clk_speed * 300);
  }
  
#ifdef LINE_2_ON
  lcd_spi_transmit_CMD(0x90);              
  __delay_cycles(300 * clk_speed);
  for(int i = 0; i < NUMCHARS; i++)
  {
    lcd_spi_transmit_DATA(dsp_buff_2[i]);
    __delay_cycles(300 * clk_speed);
  }
#endif
  
#ifdef LINE_3_ON
  lcd_spi_transmit_CMD(0xA0);
  __delay_cycles(300 * clk_speed);
  for(int i = 0; i < NUMCHARS; i++)
  {
    lcd_spi_transmit_DATA(dsp_buff_3[i]);
    __delay_cycles(300 * clk_speed);
  }
#endif
  
  return;
}

/****************************************
;NAME:       load_msg
;ASSUMES:    nothing
;RETURNS:    nothing
;MODIFIES:   R16, R17
;CALLED BY:  main application
;DESCRITION: inits DOG module LCD display for SPI (serial) operation.
;NOTE:  Can be used as is with MCU clock speeds of 4MHz or less.
;********************************************************************/
void load_msg(char buffer[], char message[])
{
    for(int i = 0; i < NUMCHARS; i++) //oads the message string into the buffer
    {
      buffer[i] = message[i];
    }
    return;
}
