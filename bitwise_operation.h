// bitwise_operation.h

#ifndef BITWISE_OPERATION_H
#define BITWISE_OPERATION_H

// Macro to set a bit
#define SET_BIT(Register, Bit) ((Register) |= (1 << (Bit)))

// Macro to clear a bit
#define CLEAR_BIT(Register, Bit) ((Register) &= ~(1 << (Bit)))

// Macro to get the value of a bit (returns 0 or 1)
#define GET_BIT(Register, Bit) (((Register) >> (Bit)) & 1)

// Macro to toggle a bit
#define TOGGLE_BIT(Register, Bit) ((Register) ^= (1 << (Bit)))

#endif // BITWISE_OPERATION_H