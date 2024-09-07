//Systick_timer




#include "systick.h"
#include "bitwise_operation.h"
#include "tm4c.h"
#include "UART.h"

int min=0;
int sec=0; 
extern unsigned char timer[6];//base stopwatch mode
/*state0=reset state1=start state2=stop*/
unsigned int flag_stopwatch=0;




void SysTick_Handler(void){ //base, start, pause
  
  sec++;
  
  if (sec==60){
    sec=0;
    min++;
  }
  
  if (min==100){
    min=0;
  }
  
  timer[0] = (min / 10) + '0';
  timer[1] = (min % 10) + '0';
  timer[3] = (sec / 10) + '0';
  timer[4] = (sec % 10) + '0';
flag_stopwatch=1;
}

void SysTick_Init(void){
  CLEAR_BIT(NVIC_ST_CTRL_R,0);
  CLEAR_BIT(NVIC_ST_CTRL_R,1);
  CLEAR_BIT(NVIC_ST_CTRL_R,2);
 
  NVIC_ST_RELOAD_R=16000000U-1U;  //16000000 = 1 second
  NVIC_ST_CURRENT_R=0U;
  
}

void Systick_Enable(void){
  SET_BIT(NVIC_ST_CTRL_R,0);
  SET_BIT(NVIC_ST_CTRL_R,1);
  SET_BIT(NVIC_ST_CTRL_R,2); 
  
}

void Systick_Disable(void){
  
  CLEAR_BIT(NVIC_ST_CTRL_R,0);
  CLEAR_BIT(NVIC_ST_CTRL_R,1);
  CLEAR_BIT(NVIC_ST_CTRL_R,2);
 
}