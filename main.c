#include "tm4c.h"
#include "modes.h"
#include "keypad.h"
#include "UART.h"
#include "systick.h"
#include "gptimer0.h"
#include "DIO.h"

void (*state_functions[])(void) = {mode0, mode1, mode2, mode3};
unsigned int mode=0;  //initial state


int main(void)
{
  KeyPad_Init();
  UART0_Init();
  SysTick_Init();
  gptimer0_Init();
  DIO_Init(PORTF,RED_LED,OUTPUT);

  while(TRUE){state_functions[mode]();}
}