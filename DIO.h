// DIO.h

#ifndef DIO_H
#define DIO_H



// Function prototypes
void DIO_Init(int port, int pin, int direction);

void DIO_WritePort(int port, unsigned int value);

unsigned int DIO_ReadPort(int port);

int DIO_ReadPin(int port, int pin);

void DIO_WritePin(int port, int pin, int value);

void DIO_TogglePin(int port, int pin);

#endif // DIO_H
