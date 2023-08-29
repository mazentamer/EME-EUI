/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *       Author:  Mazen Tamer
 *         File:  bitwise_operation.h
 *        Layer:  Libraries
 *       Module:  bitwise_operation
 *      Version:  1.00
 *
 *  Description:  Macro-like functions for commonly used bit operations
 *
 *********************************************************************************************************************/

#ifndef BITWISE_OPERATION_H
#define BITWISE_OPERATION_H

#define SET_BIT(REG,BIT)    (REG |= (1 << BIT))
#define CLEAR_BIT(REG,BIT)  (REG &= ~(1 << BIT))
#define GET_BIT(REG,BIT)    (REG & (1 << BIT))
#define TOGGLE_BIT(REG,BIT) (REG ^= (1 << BIT))

#endif

/**********************************************************************************************************************
 *  END OF FILE: bitwise_operation.h
 *********************************************************************************************************************/
