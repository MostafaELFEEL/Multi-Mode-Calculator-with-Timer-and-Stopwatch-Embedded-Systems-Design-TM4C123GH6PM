#include "tm4c.h"
#include "modes.h"
#include "keypad.h"
#include "UART.h"
#include "systick.h"
#include "gptimer0.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>

extern unsigned int mode;
extern unsigned int state;
extern unsigned int counter;
extern unsigned int flag_stopwatch;
extern unsigned int flag_timer;
extern unsigned char timer[6];


void mode0(void) {//print welcome message
  GPIO_PORTF_DATA_R &= ~(1<<RED_LED);
  UART0_WriteString("***Welcome to Project-Calculator***");
  
  while(mode==0){};
  
  UART0_ClearScreen();
  
}

void mode1(void) { //calculator
  GPIO_PORTF_DATA_R &= ~(1<<RED_LED);
  UART0_WriteString("***Mode:Calculator***");
  delay_ms(2000);
  UART0_ClearScreen();
  while(mode==1){calculator();}
  UART0_ClearScreen();
}

void mode2(void) { //stopwatch
  GPIO_PORTF_DATA_R &= ~(1<<RED_LED);
  UART0_WriteString("***Mode:Stopwatch***");
  delay_ms(2000);
  UART0_ClearScreen();
  Systick_Disable();
    strcpy((char *)timer, "00:00");
    UART0_WriteString(timer);
  while(mode==2){stopwatch();
  
  
  if(flag_stopwatch==1){
    UART0_ClearScreen();
  UART0_WriteString(timer);
  flag_stopwatch=0;
  }}
  
  Systick_Disable();
  UART0_ClearScreen();
}

void mode3(void) { //timer
  GPIO_PORTF_DATA_R &= ~(1<<RED_LED);
  UART0_WriteString("***Mode:Timer***");
  delay_ms(2000);
  UART0_ClearScreen();
  gptimer0_Disable();
    strcpy((char *)timer, "00:00");
    UART0_WriteString(timer);
    while(mode==3){Timer();
    if(flag_timer==1){
    UART0_ClearScreen();
  UART0_WriteString(timer);
  flag_timer=0;
  }
    }
    
  gptimer0_Disable();
  UART0_ClearScreen();
}


