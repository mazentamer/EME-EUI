#ifndef BITWISE_OPERATION_H
#define BITWISE_OPERATION_H

#define SET_BIT(REG,BIT)    (REG |= (1 << BIT))
#define CLEAR_BIT(REG,BIT)  (REG &= ~(1 << BIT))
#define GET_BIT(REG,BIT)    (REG & (1 << BIT))
#define TOGGLE_BIT(REG,BIT) (REG ^= (1 << BIT))

#endif
