/******************************************************************************
** Student name: 	Soyeun Jeon	
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "vm.h"

int main(int argc, char ** argv)
{
	VmSystem system;
	MenuItem menu[MENU_LIST];
	MenuFunction function;
	char * stockFile, * coinFile;

	if (systemInit(&system) == FALSE) {
		printf("System initialisation fail.\n");
		return EXIT_FAILURE;
	}

	/* execute argurment should be size 3 with 2 files and a execute command */
	if (argc < COMMAND_EXE + STOCKFILE + COINFILE) {
		printf("Wrong file input.\n");
		return EXIT_FAILURE;
	}
	
	stockFile=argv[FIRST_FILE];
	coinFile=argv[SECOND_FILE];
	if (loadData(&system, stockFile, coinFile) == FALSE) {
		return EXIT_FAILURE;
	}
	system.stockFileName = stockFile;
	system.coinFileName = coinFile;

	initMenu(menu);

	while(TRUE) {
		printMenu(menu);
		
		function = getMenuChoice(menu);
		if (function == NULL) {
			continue;
		} else if (function == saveAndExit || function == abortProgram) {
			(function)(&system);
			printf("\nGood bye.\n");
			break;			
		} else {
			(function)(&system);
		}
	}
    return EXIT_SUCCESS;
}

void printMenu(MenuItem * menu) {
	printf("\nMain Menu : \n");
	printf("%s\n", menu[0].text);
	printf("%s\n", menu[1].text);
	printf("%s\n", menu[2].text);
	printf("Administrator-Only Menu :\n");
	printf("%s\n", menu[3].text);
	printf("%s\n", menu[4].text);
	printf("%s\n", menu[5].text);
	printf("%s\n", menu[6].text);
	printf("%s\n", menu[7].text);
	printf("%s\n", menu[8].text);
	printf("Select your option (1-9) : ");	
}