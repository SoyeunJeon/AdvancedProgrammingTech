/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef VM_H
#define VM_H

#include "vm_menu.h"

#define COMMAND_EXE 1
#define STOCKFILE 1
#define COINFILE 1

/* the number of menu */
#define MENU_LIST 9
#define FIRST_FILE 1
#define SECOND_FILE 2

/* print the menu option */
void printMenu(MenuItem * menu);

#endif
