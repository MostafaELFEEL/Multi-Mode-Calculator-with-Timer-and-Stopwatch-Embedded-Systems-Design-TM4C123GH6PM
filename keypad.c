// KeyPad.c

#include "tm4c.h"
#include "modes.h"
#include "keypad.h"
#include "UART.h"
#include "systick.h"
#include "gptimer0.h"
#include "DIO.h"
#include "delay.h"
#include <stdio.h>
#include <string.h>


//*************************calculator
float num1 = 0, num2 = 0;
float result = 0.0;
char buffer[20];
char operation = 0;
int readingNumber = 1;
int flag_newOperation=0;
int decimalFlag = 0; // Added to handle decimal input
float decimalMultiplier = 0.1; // Added to handle decimal input
//*************************stopwatch

unsigned char timer[6] = "00:00";

//*************************Timer

extern unsigned int state;
unsigned int counter=10;
extern int min;
extern int sec;






unsigned  char symbol[4][4] = {{ '1', '2',  '3', '+'},
                               { '4', '5',  '6', '-'},
                               { '7', '8',  '9', '*'},
                               { '.', '0',  '=', '/'}};


void KeyPad_Init (void) { //port B output and E input
SYSCTL_RCGCGPIO_R |= (1<<PORTB);  //PB2 to PB5: Output pins for rows.
                                  //PE0 to PE3: Input pins for columns.
GPIO_PORTB_DIR_R = 0xFF;
GPIO_PORTB_DEN_R = 0xFF;


SYSCTL_RCGCGPIO_R |= (1<<PORTE);
GPIO_PORTE_CR_R  = 0xFF;
GPIO_PORTE_DIR_R = 0x00;
GPIO_PORTE_PDR_R = 0xFF;
GPIO_PORTE_DEN_R = 0xFF;
}


unsigned char KeyPad_Read(void) {

        for (int row = 0; row < 4; row++) {
            DIO_WritePort(PORTB,(1U << row));

            for (int col = 0; col < 4; col++) {
                if (DIO_ReadPin(PORTE, col) == 1) {
                  delay_ms(2);
                  while(DIO_ReadPin(PORTE, col) == 1){};
                  delay_ms(2);
                    return symbol[row][col];
                }
            }
        }     
        return 0;
}


void calculator(void){


 unsigned char key = KeyPad_Read();
 
 if (flag_newOperation==1 && key >= '0' && key <= '9'){ 
            UART0_ClearScreen();
            flag_newOperation=0;
   
        }

        if (key >= '0' && key <= '9') {
        if (readingNumber == 1) {
            if (decimalFlag) { // Handling decimal input for num1
                num1 += (key - '0') * decimalMultiplier;
                decimalMultiplier /= 10;
            } else {
                num1 = num1 * 10 + (key - '0');
            }
        } else {
            if (decimalFlag) { // Handling decimal input for num2
                num2 += (key - '0') * decimalMultiplier;
                decimalMultiplier /= 10;
            } else {
                num2 = num2 * 10 + (key - '0');
            }
        }
        UART0_WriteChar(key);
    } else if (key == '.') { // Handling decimal point input
        decimalFlag = 1;
        UART0_WriteChar(key);
    }
         else if (key == '+' || key == '-' || key == '*' || key == '/') {
            operation = key;
        readingNumber = 2;
        decimalFlag = 0; // Resetting decimal flag
        decimalMultiplier = 0.1; // Resetting decimal multiplier
        UART0_WriteChar(key);
        } 
         else if (key == '=') {
        switch (operation) {
            case '+':
                result = num1 + num2;
                break;
            case '-':
                result = num1 - num2;
                break;
            case '*':
                result = num1 * num2;
                break;
            case '/':
                if (num2 != 0) {
                    result = num1 / num2;
                }
                break;
                
        }
       
        num1 = 0;
        num2 = 0;
        readingNumber = 1;
        decimalFlag = 0; // Resetting decimal flag
        decimalMultiplier = 0.1; // Resetting decimal multiplier
        UART0_WriteChar(key);
        sprintf(buffer, "%.4f", result);
        UART0_WriteString((unsigned char*)buffer);
        flag_newOperation = 1;
    }
}


void stopwatch(void){
 unsigned char key = KeyPad_Read();
  
  if (key == '+'){
    Systick_Disable();
    min=0;
    sec=0;
    strcpy((char *)timer, "00:00");
          UART0_ClearScreen();
    UART0_WriteString(timer);
  }
  else if  (key == '-'){
    Systick_Enable();
  }
  
  else if  (key == '*'){
    Systick_Disable();
  }
  
}


void Timer(void){
  
  unsigned char key = KeyPad_Read();   //initial mode input characters
  
  if (key == '+'){
    gptimer0_Disable();
    strcpy((char *)timer, "00:00");
    UART0_ClearScreen();
    UART0_WriteString(timer);
    counter=0;
    GPIO_PORTF_DATA_R &= ~(1<<RED_LED);
  }
  if(counter<5){
    if(key<='9' && key>='0'){ 
      timer[counter]=key;
        
        counter++;
        if (counter==2){
          counter++;
        }
      UART0_ClearScreen();
      UART0_WriteString(timer);
      
    }}
  
  else if (counter==5){
    
    sec = (timer[3] - '0') * 10 + (timer[4] - '0');
    min = (timer[0] - '0') * 10 + (timer[1] - '0');
    
    if(sec>59){
      sec=59;
    }
    

    timer[3] = (sec / 10) + '0';
    timer[4] = (sec % 10) + '0';
    
    UART0_ClearScreen();
    UART0_WriteString(timer);
    counter++;
  }
    
    if (key == '-'){   //start the timer
    gptimer0_Enable();
    UART0_ClearScreen();
    UART0_WriteString(timer);
  } 
  
  if (key == '*'){   //start the timer
    gptimer0_Disable();
  } 
  }
