/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_coin.h"

/**
 * Implement functions here for managing coins and the
 * "cash register" contained in the VmSystem struct.
 **/

/**
 * Some example functions:
 * init coins array, insert coin, change coin count for Denomination,
 * convert Denomination to coin value, deducting coins from register, etc...
 **/

Denomination toDenomValue(char * value) {
	Denomination denom;

	if (strcmp(value, "1000")==0) {
		denom = TEN_DOLLARS;	
	} else if (strcmp(value, "500")==0) {
		denom = FIVE_DOLLARS;
	} else if (strcmp(value, "200")==0) {
		denom = TWO_DOLLARS;
	} else if (strcmp(value, "100")==0) {
		denom = ONE_DOLLAR;
	} else if (strcmp(value, "50")==0) {
		denom = FIFTY_CENTS;
	} else if (strcmp(value, "20")==0) {
		denom = TWENTY_CENTS;
	} else if (strcmp(value, "10")==0) {
		denom = TEN_CENTS;
	} else if (strcmp(value, "5")==0) {
		denom = FIVE_CENTS;
	}

	return denom;
}

int denomToInt(Denomination denom) {
	int value;
	if (denom == TEN_DOLLARS) {
		value = 1000;
	} else if (denom == FIVE_DOLLARS) {
		value = 500;
	} else if (denom == TWO_DOLLARS) {
		value = 200;
	} else if (denom == ONE_DOLLAR) {
		value = 100;
	} else if (denom == FIFTY_CENTS) {
		value = 50;
	} else if (denom == TWENTY_CENTS) {
		value = 20;
	} else if (denom == TEN_CENTS) {
		value = 10;
	}
	return value;
}

Price inputCoinVal(char * input, int size) {
	char * dollarTemp, * centTemp;
	Price price;
	price.dollars = -1;
	price.cents = -1;
	dollarTemp = strtok(input, ".");
	centTemp = strtok(NULL, ".");
	if (centTemp == NULL) {
		/* coin input should have decimal */
		printf("Invalid price input. Please try again.\n");
	}
	else if (strlen(dollarTemp)> size) {
		/* input size validation */
		printf("Invalid price input. Please try again.\n");
	}  
	else if (strlen(centTemp) < CENT_SIZE){
		printf("Invalid price input. Please try again.\n");
	}
	else if ((*dollarTemp >= 0x41 && *dollarTemp <= 0x7A) || \
		(*centTemp >= 0x41 && *centTemp <= 0x7A)) {
		/* coin input should be valid integer */
		printf("Invalid price input. Please try again.\n");
	}
	else {
		price.dollars = strtol(dollarTemp, NULL, 10);
		price.cents = strtol(centTemp, NULL, 10);
	}
	return price;
}

Boolean payment(Price price, char * item) {
	char paid[PRICE_LEN+EXTRA_SPACES+EXTRA_SPACES];
	int dollars = price.dollars;
	int cents = price.cents;
	int remain = dollars*100 + cents;
	while(TRUE) {
		printf("You still need to give us $%u.%02u : ", dollars, cents);
		fgets(paid, sizeof(paid), stdin);
		if (checkString(paid) == FALSE) {
			/* string validation check */
			printf("Invalid input size. Please try again. \n");
			continue;
		}
		if (strlen(paid)==0) {
			/* enter input catch */
			printf("You have canceled purchase. Returning to main menu...\n\n");
			return FALSE;
		}
		if (strtol(paid, NULL, 10)==5||strtol(paid, NULL, 10)==10||\
			strtol(paid, NULL, 10)==20||strtol(paid, NULL, 10)==50||\
			strtol(paid, NULL, 10)==100||strtol(paid, NULL, 10)==200||\
			strtol(paid, NULL, 10)==500||strtol(paid, NULL, 10)==1000) {
			/* get the user input until the input become same or excess the price */
			if (remain-strtol(paid, NULL, 10)<=0) {
				remain = strtol(paid, NULL, 10)-remain;
				break;
			}
			remain = remain - strtol(paid, NULL, 10);
			dollars = remain/100;
			cents = remain%100;
		} else {
			/* error if user input denom not in system */
			printf("Error: $%ld.%02ld is not a valid denomination of money.\n",\
			strtol(paid, NULL, 10)/100, strtol(paid, NULL, 10)%100);
			continue;
		}
	}
	
	if (remain==0) {
		/* if the amount of input is the same as the price of item */
		printf("Thank you. Here is your %s.\n", item);
	} else {
		/* if the amount of input is larger than price, changes will be returned to user */
		printf("Thank you. Here is your %s, and your change of $%u.%02u : ", \
			item, remain/100, remain%100);
		makeChanges(remain);
	}

	printf("Please come back soon.\n");
	return TRUE;
}

/* split the changes into denom nodes and coins*/
void makeChanges(int price) { 
	int denomToDivide[NUM_DENOMS] = {1000, 500, 200, 100, 50, 20, 10, 5};
	int denomCount[NUM_DENOMS];
	int denomIndex = 0, countIndex = 0;
	int count, i, j;
	char *coins[] = {"$10", "$5", "$2", "$1", "50c", "20c", "10c", "5c"};

	while (denomIndex < 8 && countIndex < 8) {
		count = price / denomToDivide[denomIndex];
		price = price % denomToDivide[denomIndex];
		/* denomCount array stores the number of each coin that need to be returned */
		denomCount[countIndex] = count;
		denomIndex++;
		countIndex++;
	}
	for (i=0;i<8;i++) {
		if (denomCount[i] != 0) {
			for (j=0;j<denomCount[i];j++) {
				printf("%s ", coins[i]);
			}
		}
	}

	printf("\n");
}
