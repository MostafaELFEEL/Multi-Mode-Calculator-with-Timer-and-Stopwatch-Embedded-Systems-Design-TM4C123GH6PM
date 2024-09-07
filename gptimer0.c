//GPtimers

#include "gptimer0.h"
#include "tm4c.h"

extern unsigned int counter;
unsigned int flag_timer=0;

extern int min;
extern int sec;
extern unsigned char timer[6];



void gptimer0_Init(void){


 SYSCTL_RCGCTIMER_R |=(1<<TIMER0);
  
  TIMER0_CTL_R &= ~(1<<TIMER0);
  
  TIMER0_CFG_R =4;  // set to 4 for prescale
  
  TIMER0_TAMR_R=2;  //periodic
  
  TIMER0_TAPR_R=250; //prescale 250 clock cycle/tick
  
  TIMER0_TAILR_R=64000U;  //number of ticks
  
  TIMER0_IMR_R |=(1<<TIMER0);   // Interrupt musk register on timer0
  
  NVIC_EN0_R |=(1<<19);     //interrupt on timer0A
  
  
  }
  
  
  
  void Timer0AIntHandler(void){
  
  TIMER0_ICR_R |=(1<<TIMER0);
  
  if(sec==0 && min==0){
    sec=0;
    min=0;
    TIMER0_CTL_R &= ~(1<<TIMER0);
    GPIO_PORTF_DATA_R |= (1<<RED_LED);
    counter=0;
  }
  else{
  
  sec--;
  
  if (sec==-1){
    sec=59;
    min--;
  }
  
  
  
  }
  timer[0] = (min / 10) + '0';
  timer[1] = (min % 10) + '0';
  timer[3] = (sec / 10) + '0';
  timer[4] = (sec % 10) + '0';
  
  flag_timer=1;
  
  }

void gptimer0_Enable (void){
  
  TIMER0_CTL_R |= (1<<TIMER0);   //start timer0A
}

void gptimer0_Disable(void){
  
   TIMER0_CTL_R &= ~(1<<TIMER0);
  
}