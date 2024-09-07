#ifndef UART_H_

#define UART_H_



void UART0_Init(void);
void UART0_Handler(void);

void UART0_ClearScreen(void);
void UART0_WriteString(unsigned char *str);
void UART0_WriteChar(char c);



#endif