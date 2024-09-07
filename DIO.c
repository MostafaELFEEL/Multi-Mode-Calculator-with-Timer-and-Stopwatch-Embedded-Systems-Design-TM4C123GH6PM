//DIO.c
#include "bitwise_operation.h"
#include "tm4c.h"
#include "DIO.h"




volatile unsigned long *GPIO_PORT_LOCK_R[] = {
        &GPIO_PORTA_LOCK_R,
        &GPIO_PORTB_LOCK_R,
        &GPIO_PORTC_LOCK_R,
        &GPIO_PORTD_LOCK_R,
        &GPIO_PORTE_LOCK_R,
        &GPIO_PORTF_LOCK_R
    };
  
   volatile unsigned long *GPIO_PORT_CR_R[] = {
        &GPIO_PORTA_CR_R,
        &GPIO_PORTB_CR_R,
        &GPIO_PORTC_CR_R,
        &GPIO_PORTD_CR_R,
        &GPIO_PORTE_CR_R,
        &GPIO_PORTF_CR_R
    };
   
   volatile unsigned long *GPIO_PORT_DIR_R[] = {
        &GPIO_PORTA_DIR_R,
        &GPIO_PORTB_DIR_R,
        &GPIO_PORTC_DIR_R,
        &GPIO_PORTD_DIR_R,
        &GPIO_PORTE_DIR_R,
        &GPIO_PORTF_DIR_R
    };
   
   volatile unsigned long *GPIO_PORT_PDR_R[] = {
        &GPIO_PORTA_PDR_R,
        &GPIO_PORTB_PDR_R,
        &GPIO_PORTC_PDR_R,
        &GPIO_PORTD_PDR_R,
        &GPIO_PORTE_PDR_R,
        &GPIO_PORTF_PDR_R
    };
   
   volatile unsigned long *GPIO_PORT_DEN_R[] = {
        &GPIO_PORTA_DEN_R,
        &GPIO_PORTB_DEN_R,
        &GPIO_PORTC_DEN_R,
        &GPIO_PORTD_DEN_R,
        &GPIO_PORTE_DEN_R,
        &GPIO_PORTF_DEN_R
    };
   
   volatile unsigned long *GPIO_PORT_DATA_R[] = {
        &GPIO_PORTA_DATA_R,
        &GPIO_PORTB_DATA_R,
        &GPIO_PORTC_DATA_R,
        &GPIO_PORTD_DATA_R,
        &GPIO_PORTE_DATA_R,
        &GPIO_PORTF_DATA_R
    };


   
   
   
void DIO_Init(int port, int pin, int direction){
 
 SET_BIT(SYSCTL_RCGCGPIO_R,port);
 
 *(GPIO_PORT_LOCK_R[port]) = 0x4C4F434B;
 
 SET_BIT(*(GPIO_PORT_CR_R[port]),pin);
 
 if (direction==1){
 SET_BIT(*(GPIO_PORT_DIR_R[port]),pin);
 }
 else{
 CLEAR_BIT(*(GPIO_PORT_DIR_R[port]), pin);
 SET_BIT(*(GPIO_PORT_PDR_R[port]),pin);
 }
 SET_BIT(*(GPIO_PORT_DEN_R[port]),pin); 
}



void DIO_WritePort(int port, unsigned int value) {
 
    // Calculate the index based on the port value

    // Write the value to the port
    *(GPIO_PORT_DATA_R[port]) = value;
}





unsigned int DIO_ReadPort(int port) {
    // Calculate the index based on the port value
    // Read the port value and return it
    return *(GPIO_PORT_DATA_R[port]);
}




int DIO_ReadPin(int port, int pin) {
    // Calculate the index based on the port value
    // Read the pin value and return it
    return (*(GPIO_PORT_DATA_R[port]) >> pin) & 1;
}




void DIO_WritePin(int port, int pin, int value) {
    // Calculate the index based on the port value
        if (value == 1) {
            SET_BIT(*GPIO_PORT_DATA_R[port], pin);
        } else {
            CLEAR_BIT(*GPIO_PORT_DATA_R[port], pin);
        }
}


void DIO_TogglePin(int port, int pin) {
    // Calculate the index based on the port value
    TOGGLE_BIT(*GPIO_PORT_DATA_R[port], pin);
}
