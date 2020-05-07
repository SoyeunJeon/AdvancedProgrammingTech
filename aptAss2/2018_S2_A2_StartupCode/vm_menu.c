/******************************************************************************
** Student name: 	Soyeun Jeon	
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm_menu.h"

/**
 * vm_menu.c handles the initialisation and management of the menu array.
 **/

/**
 * In this function you need to initialise the array of menu items
 * according to the text to be displayed for the menu. This array is
 * an array of MenuItem with text and a pointer to the function
 * that will be called.
 **/
void initMenu(MenuItem * menu)
{ 
    strcpy(menu[0].text, "1. Display Items");
    strcpy(menu[1].text, "2. Purchase Items");
    strcpy(menu[2].text, "3. Save and Exit");
    strcpy(menu[3].text, "4. Add Items");
    strcpy(menu[4].text, "5. Remove Items");
    strcpy(menu[5].text, "6. Display Conins");
    strcpy(menu[6].text, "7. Reset Stock");
    strcpy(menu[7].text, "8. Reset Coins");
    strcpy(menu[8].text, "9. Abort Program");
    menu->function = NULL;
}

/**
 * Gets input from the user and returns a pointer to the MenuFunction
 * that defines how to perform the user's selection. NULL is returned
 * if an invalid option is entered.
 **/
MenuFunction getMenuChoice(MenuItem * menu)
{
	char choice[USER_CHOICE+EXTRA_SPACES];
	MenuFunction function;
	fgets(choice, sizeof(choice), stdin);
	checkString(choice);
	if (strcmp(choice, "1")==0) {
		menu->function=displayItems;
	} 
	else if (strcmp(choice, "2")==0) {
		menu->function=purchaseItem;
	} 
	else if (strcmp(choice, "3")==0) {
		menu->function=saveAndExit;
	} 
	else if (strcmp(choice, "4")==0) {
		menu->function=addItem;
	} 
	else if (strcmp(choice, "5")==0) {
		menu->function=removeItem;
	} 
	else if (strcmp(choice, "6")==0) {
		menu->function=displayCoins;
:q
	} 
	else if (strcmp(choice, "7")==0) {
		menu->function=resetStock;
	} 
	else if (strcmp(choice, "8")==0) {
		menu->function=resetCoins;
	} 
	else if (strcmp(choice, "9")==0) {
		menu->function=abortProgram;
	} 
	else {
		printf("Invalid option.\n");
		return NULL;
	}

	function = menu->function;
	return function;
}
