/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_COIN_H
#define VM_COIN_H

#include "vm_system.h"

/**
 * The default coin level used when resetting values.
 **/
#define DEFAULT_COIN_COUNT 20
#define ZERO_CASH 0
#define CENT_SIZE 2

#define COIN_DELIM ","

/* change the numeric value into denom enum */
Denomination toDenomValue(char * value);

/* change the denomination enum to numeric value */
int denomToInt(Denomination denom);

/* validate the coin input from user */
Price inputCoinVal(char * input, int size);

/* make a payment of purchase */
Boolean payment(Price price, char * item);

/* split the changes into denom nodes and coins */
void makeChanges(int price);

#endif
