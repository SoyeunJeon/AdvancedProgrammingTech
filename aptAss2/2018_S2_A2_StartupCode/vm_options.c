/******************************************************************************
** Student name: 	Soyeun Jeon	
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_options.h"
/**
 * vm_options.c this is where you need to implement the system handling
 * functions (e.g., init, free, load, save) and the main options for
 * your program. You may however have some of the actual work done
 * in functions defined elsewhere.
 **/

/**
 * Initialise the system to a known safe state. Look at the structure
 * defined in vm_system.h.
 **/
Boolean systemInit(VmSystem * system)
{
	system->cashRegister->denom = ZERO_CASH;
	system->cashRegister->count = ZERO_CASH;

	system->itemList=NULL;
	system->stockFileName=NULL;
	system->coinFileName=NULL;

    return TRUE;
}

/**
 * Free all memory that has been allocated. If you are struggling to
 * find all your memory leaks, compile your program with the -g flag
 * and run it through valgrind.
 **/
void systemFree(VmSystem * system)
{ 
	freeList(system->itemList);
}

/**
 * Loads the stock and coin data into the system. You will also need to assign
 * the char pointers to the stock and coin file names in the system here so
 * that the same files will be used for saving. A key part of this function is
 * validation. A substantial number of marks are allocated to this function.
 **/
Boolean loadData(
    VmSystem * system, const char * stockFileName, const char * coinsFileName)
{
	if (loadStock(system, stockFileName) && loadCoins(system, coinsFileName))
    	return TRUE;
    else 
    	return FALSE;
}

/**
 * Loads the stock file data into the system.
 **/
Boolean loadStock(VmSystem * system, const char * fileName)
{
    char buff[ID_LEN+NAME_LEN+DESC_LEN+PRICE_LEN+ONHAND_LEN+DELIM_SPACE*4+EXTRA_SPACES];
    Stock data;
    FILE * file;

    system->itemList = initList();

    /* check the file open status */
    file = fopen(fileName, "r");
    if (file == NULL) {
    	return FALSE;
    }
    /* read the file line by line */
    while (fgets(buff, sizeof(buff), file) != NULL) 
    {
    	if (checkString(buff) == FALSE) { return FALSE; }
    	strcpy(data.id, strtok(buff, STOCK_DELIM));
    	strcpy(data.name, strtok(NULL, STOCK_DELIM));
    	strcpy(data.desc, strtok(NULL, STOCK_DELIM));
    	data.price.dollars = strtol(strtok(NULL, "."), NULL, 10);
    	data.price.cents = strtol(strtok(NULL, STOCK_DELIM), NULL, 10);
    	data.onHand = strtol(strtok(NULL, "\0"), NULL, 10);
    	addToList(system->itemList, &data);
    }
    fclose(file);
    return TRUE;
}

/**
 * Loads the coin file data into the system.
 **/
Boolean loadCoins(VmSystem * system, const char * fileName)
{
	char buff[NUM_DENOMS+ONHAND_LEN+DELIM_SPACE+EXTRA_SPACES];
	Coin coin;
	int i=0;

	/* open file and null check */
	FILE * file = fopen(fileName, "r");
	if (file == NULL) {
		return FALSE;
	}
	while (fgets(buff, sizeof(buff), file) != NULL) {
		if (checkString(buff) == FALSE) { return FALSE; }
		coin.denom = toDenomValue(strtok(buff, COIN_DELIM));
		coin.count = strtol(strtok(NULL, "\0"), NULL, 10);

		system->cashRegister[i] = coin;
		i++;
	}
	fclose(file);
	return TRUE;
}

/**
 * Saves all the stock back to the stock file.
 **/
Boolean saveStock(VmSystem * system)
{
	Node * node = system->itemList->head;
	FILE * file = fopen(system->stockFileName, "w");

	if (file == NULL) {
		printf("Failed to save the changes.\n");
		return FALSE;
	}

	/* write the data from the system to the file opened */
	while(node != NULL) {
		fprintf(file, "%s|%s|%s|%u.%02u|%u\n", \
			node->data->id, node->data->name, node->data->desc, \
			node->data->price.dollars, node->data->price.cents, node->data->onHand);
		node = node->next;
	}

	printf("All the stock changes saved.\n");
	fclose(file);
    return TRUE;
}

/**
 * Saves all the coins back to the coins file.
 **/
Boolean saveCoins(VmSystem * system)
{
	int i, amount;
	FILE * file = fopen(system->coinFileName, "w");
	if (file == NULL) {
		printf("Failed to save the changes.\n");
		return FALSE;
	}
	for (i=0; i<NUM_DENOMS;i++) {
		amount = denomToInt(system->cashRegister[i].denom);
		fprintf(file, "%d,%u\n", amount, system->cashRegister[i].count);
	}
	fclose(file);
    return TRUE;
}

/**
 * This option allows the user to display the items in the system.
 * This is the data loaded into the linked list in the requirement 2.
 **/
void displayItems(VmSystem * system)
{
	Node * node = system->itemList->head;
	int longestName;
	int i;
	printf("\nItems Menu\n");
     
    if (node == NULL) {
    	printf("Stock is empty.\n");
    	return;
    }

    longestName = calculateLongestName(system);
    printf("ID   | Name");
    addSpace(5, longestName+EMPTY_SPACE*2);
    printf(" Available | price\n");
    for (i=0;i<longestName+30;i++) {
    	printf("-");
    }
    printf("\n");

    while(node != NULL) {
        printf("%s|", node->data->id);
        printf(" %s", node->data->name);
        addSpace(strlen(node->data->name), longestName+EMPTY_SPACE);	
        printf(" %u", node->data->onHand);
        calculateSpace(node->data->onHand, 10);
        printf(" %u.%02u\n", node->data->price.dollars, node->data->price.cents);
        node = node->next;
    }
}


/**
 * This option allows the user to purchase an item.
 * This function implements requirement 5 of the assignment specification.
 **/
void purchaseItem(VmSystem * system)
{ 
	char choice[ID_LEN + EXTRA_SPACES];
	Node * node = system->itemList->head;

	printf("\nPurchase Item\n--------------\n");
	printf("Please enter the id of the item you wish to purchase : ");
	while (fgets(choice, sizeof(choice), stdin)) {
		checkString(choice);
		if (strlen(choice) == 0) {
			printf("You have canceled purchase. Returning to main menu...\n");
			break;
		}
		while(node != NULL) {
			if (strcmp(choice, node->data->id)==0) {
				break;
			}
			node = node->next;
		}
		if (node == NULL) {
			printf("The item does not exist. Returning to main menu...\n");
			break;
		}
		printf("You have selected '%s'. This will cost you $%u.%u.\n", \
			node->data->desc, node->data->price.dollars, node->data->price.cents);
		printf("Please hand over the money - type in the value of each note/coin in cents.\n");
		printf("Press enter on a new and empty line to cancel this purchase :\n");
		/* get the payment of the user. this function is in coin.c */
		if (payment(node->data->price, node->data->name) == TRUE) {
			node->data->onHand -=1;
		}
		break;
	}
}

/**
 * You must save all data to the data files that were provided on the command
 * line when the program loaded up, display goodbye and free the system.
 * This function implements requirement 6 of the assignment specification.
 **/
void saveAndExit(VmSystem * system)
{ 
	saveStock(system);
	saveCoins(system);
	systemFree(system);
}

/**
 * This option adds an item to the system. This function implements
 * requirement 7 of of assignment specification.
 **/
void addItem(VmSystem * system)
{
	char newId[ID_LEN], newName[NAME_LEN], newDesc[DESC_LEN], newPrice[PRICE_INPUT];
	Stock data;
	int idNum = generateId(system);

	sprintf(newId, "I%04u", idNum);
   	strcpy(data.id, newId);
   	printf("This new meal item will have the Item id of %s.\n", newId);
	data.onHand = DEFAULT_STOCK_LEVEL;
	/* new item name input */
	while (TRUE) {
		printf("Enter the item name : ");
		if (fgets(newName, sizeof(newName),stdin) != NULL) {
			if (checkString(newName) == FALSE) {
				printf("Invalid item name. Please try again.\n");
				continue;
			}
			if (strlen(newName)==0) {
				printf("You have canceled add Item. Returning to main menu...\n");
				return;
			}
			strcpy(data.name, newName);
			break;
		}
	}
	/* new item description input */
	while (TRUE) {
		printf("Enter the item description : ");
		if (fgets(newDesc, sizeof(newDesc),stdin) != NULL) {
			if (checkString(newDesc) == FALSE) {
				printf("Invalid item description. Please try again.\n");
				continue;
			}
			if (strlen(newDesc)==0) {
				printf("You have canceled add Item. Returning to main menu...\n");
				return;
			}
			strcpy(data.desc, newDesc);
			break;
		}
	}
	/* new item price input */
	while (TRUE) {
		printf("Enter the price for this item : ");
		if (fgets(newPrice, sizeof(newPrice),stdin) != NULL) {
			if (checkString(newPrice) == FALSE) {
				printf("Invalid item Price. Please try again.\n");
				continue;
			}
			if (strlen(newPrice)==0) {
				printf("You have canceled add Item. Returning to main menu...\n");
				return;
			}
			data.price = inputCoinVal(newPrice, sizeof(newPrice));
			if (data.price.dollars != -1 && data.price.cents != -1) {
				break;
			} 
		}
	}
	addToList(system->itemList, &data);
	printf("\nThis item '%s - %s.' has now been added to the menu.\n", \
		data.name, data.desc);
}

/**
 * Remove an item from the system, including free'ing its memory.
 * This function implements requirement 8 of the assignment specification.
 **/
void removeItem(VmSystem * system)
{ 
	char choice[ID_LEN+EXTRA_SPACES];
	char idToDelete[ID_LEN+EXTRA_SPACES], descToDelete[DESC_LEN+EXTRA_SPACES];
	Node * node = system->itemList->head;

	printf("\nEnter the item id of the item to remove from the menu : ");
	while(fgets(choice, sizeof(choice), stdin)) {
		checkString(choice);
		while(node != NULL) {
			if (strcmp(choice, node->data->id)==0) {
				break;
			}
			node = node->next;
		}
		if (node == NULL) {
			printf("The item does not exist. Returning to main menu...\n");
			break;
		}

		/* copy the string before delete the node to display after */
		strcpy(idToDelete, node->data->id);
		strcpy(descToDelete, node->data->desc);

		if (removeFromList(system->itemList, node->data->id)) {
			printf("\n'%s - %s' has been removed from the system.\n", \
				idToDelete, descToDelete);
			break;
		} else {
			printf("Item does not exist or fail to remove from the machine.\n");
		}
	}
}

/**
 * This option will require you to display the coins from lowest to highest
 * value and the counts of coins should be correctly aligned.
 * This function implements part 4 of requirement 18 in the assignment
 * specifications.
 **/
void displayCoins(VmSystem * system)
{ 
	int i=0;
	printf("\nCoins Summary\n-------------\n");
	printf("Denomination | Count\n\n");
	for (i=0;i<NUM_DENOMS;i++) {
		if (system->cashRegister[i].denom == FIVE_CENTS) {
			printf("5 cents      | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == TEN_CENTS) {
			printf("10 cents     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == TWENTY_CENTS) {
			printf("20 cents     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == FIFTY_CENTS) {
			printf("50 cents     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == ONE_DOLLAR) {
			printf("1 dollar     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == TWO_DOLLARS) {
			printf("2 dollar     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == FIVE_DOLLARS) {
			printf("5 dollar     | %u\n", system->cashRegister[i].count);
		} else if (system->cashRegister[i].denom == TEN_DOLLARS) {
			printf("10 dollar    | %u\n", system->cashRegister[i].count);
		}
	}
	printf("\n");
}

/**
 * This option will require you to iterate over every stock in the
 * list and set its onHand count to the default value specified in
 * the startup code.
 * This function implements requirement 9 of the assignment specification.
 **/
void resetStock(VmSystem * system)
{
	Node * node = system->itemList->head;

	/* get the stock availability and set the value to default */
	while (node != NULL) {
		node->data->onHand = DEFAULT_STOCK_LEVEL;
		node = node->next;
	}

	printf("\nAll stocks have been reset to the default level of %d.\n\n", \
		DEFAULT_STOCK_LEVEL);
}

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code.
 * This requirement implements part 3 of requirement 18 in the
 * assignment specifications.
 **/
void resetCoins(VmSystem * system)
{
	int i=0;

	/* get the coins and set the value to default */
	for (i=0;i<NUM_DENOMS;i++) {
		system->cashRegister[i].count = DEFAULT_COIN_COUNT;
	}
	printf("\nAll coins have been reset to the default level of %d.\n\n", \
		DEFAULT_COIN_COUNT);
}

/**
 * This option will require you to display goodbye and free the system.
 * This function implements requirement 10 of the assignment specification.
 **/
void abortProgram(VmSystem * system)
{ 
	/* do not save the data in system to abort the data */
	systemFree(system);
}
