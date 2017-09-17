//***************************************************************************
//
// File Name            : lcd_dog_driver.h
// Title                : Header file for LCD module
// Date                 : 02/26/2013
// Version              : 1.0
// Target MCU           : ATmega128 @  16MHz (default)
// Target Hardware      ; 
// Author               : Suphasith Usdonvudhikai
// DESCRIPTION
// This file includes all the declaration the compiler needs to 
// reference the functions and variables written in the file lcd_dog_driver.h.
// Configurations can be made below in order to swtich displays. 
//
// Warnings             : none
// Restrictions         : none
// Algorithms           : none
// References           : none
//
// Revision History     : Initial version
/*****************CONFIGURATION FOR DIFFERENT LCDs*****************************/
/*                 Default at 3 lines with 16 characters                      */
#define clk_speed 16  	     //clock speed in MHz
#define NUMCHARS 16          //define how many numbers of characters per line
#define LINE_2_ON            //this can be commented to turn the second line off
#define LINE_3_ON            //this can be commented to turn the third line off
/***********************END OF CONFIGURATION***********************************/


/*********************************START OF DELCARATIONS************************/

#define	SCK     1       //Pin Numbers
#define	MISO    3
#define	MOSI    2
#define	SS_bar  0
#define	RS      4
#define	BLC     5

extern char dsp_buff_1[NUMCHARS];      //buffers are stored externally. 

#ifdef LINE_2_ON
extern char dsp_buff_2[NUMCHARS];
#endif

#ifdef LINE_3_ON
extern char dsp_buff_3[NUMCHARS];
#endif

extern void init_lcd_dog(void);         //function declarations 
extern void update_lcd_dog(void);
extern void load_msg(char buffer[], char message[]);
extern void clear_dsp(void);
extern int putchar(int);
