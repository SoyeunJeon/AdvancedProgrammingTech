/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "carboard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT "Welcome to Car Board\n--------------------\n1. Play game\n2. Show student's information\n3. Quit\n"
#define INPUT "Please enter your choice: "

int main(void)
{
    /* TODO */
	
	char choice[10];
	printf("\n\n%s\n%s",INIT,INPUT);
	while (fgets(choice, 3, stdin)) {
 		printf("%s\n", choice[strlen(choice)-1]);
		if (choice[strlen(choice)-1]!='\n') {
			readRestOfLine();
		}
		choice[strlen(choice)-1] = '\0';
		printf("%s\n", choice[strlen(choice)-1]);
		if (strcmp(choice, "1")==0) { 
			playGame();
			printf("\n\n%s\n%s",INIT,INPUT);
		} else if (strcmp(choice, "2")==0) {
			showStudentInformation();
			printf("\n\n%s\n%s",INIT,INPUT);
		} else if (strcmp(choice, "3")==0) {
   			printf("\n\nGood bye!\n\n");
			break;
		} else { /* if user input is either 1, 2 or 3 */
			printf("\nInvalid input. Please try again.\n");
			printf("\n%s\n%s",INIT,INPUT);
			continue;
		}
	}
    return EXIT_SUCCESS;
}

void showStudentInformation()
{
	printf("\n------------------------------\n");
	printf("Name: %s\n", STUDENT_NAME);
	printf("No: %s\n", STUDENT_ID);
	printf("EMAIL: %s\n", STUDENT_EMAIL);  
	printf("------------------------------\n");
}
