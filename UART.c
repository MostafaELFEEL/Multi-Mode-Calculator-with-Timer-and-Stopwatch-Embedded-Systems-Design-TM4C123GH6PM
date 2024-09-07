#include "tm4c.h"
#include "UART.h"


extern unsigned int mode;
volatile char receivedChar;

void UART0_Init(void) {
    SYSCTL_RCGCUART_R |= (1<<UART0);  // Enable UART0
    SYSCTL_RCGCGPIO_R |= (1<<PORTA);  // Enable Port A

    UART0_CTL_R &= ~(1<<UART0);       // Disable UART0
    UART0_IBRD_R = 104;         // Set baud rate to 9600 (assuming 16 MHz clock)
    UART0_FBRD_R = 11;
    UART0_LCRH_R = 0x60;        // 8-bit, no parity, 1-stop bit, FIFO enabled
    UART0_CTL_R = 0x301;        // Enable UART0, TXE, RXE

    GPIO_PORTA_AFSEL_R |= 0x03; // Enable alt function on PA0, PA1
    GPIO_PORTA_DEN_R |= 0x03;   // Enable digital I/O on PA0, PA1
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;

    UART0_IM_R |= 0x10;         // Enable RX interrupt
    NVIC_EN0_R |= (1<<5);         // Enable interrupt 5 in NVIC
}

void UART0_Handler(void) {
    if (UART0_MIS_R & 0x10) {   // Check if RX interrupt
        UART0_ICR_R = 0x10;     // Clear interrupt flag
        receivedChar = UART0_DR_R; // Read received character

        if (receivedChar >= '0' && receivedChar <= '3') {
          
          mode=receivedChar-'0';
        }

       // while ((UART0_FR_R & 0x20) != 0); // Wait until TXFF is empty
        
       // UART0_DR_R = receivedChar;        // Send character
    }
}


void UART0_WriteChar(char c) {
    while ((UART0_FR_R & UART_FR_TXFF) != 0); // Wait until the transmit FIFO is not full
    UART0_DR_R = c;
}


void UART0_WriteString(unsigned char *str) {
    while (*str) {
        if (*str == '\n') {
            UART0_WriteChar('\r'); // Add carriage return before newline
        }
        UART0_WriteChar(*str++);
    }
}




void UART0_ClearScreen(void) {
    UART0_WriteString("\033[2J\033[H");
}