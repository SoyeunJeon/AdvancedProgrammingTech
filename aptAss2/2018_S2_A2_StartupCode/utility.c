/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "utility.h"

/**
 * Function required to be used when clearing the buffer. It simply reads
 * each char from the buffer until the buffer is empty again. Please refer
 * to the materials on string and buffer handling in the course for more
 * information.
 **/
void readRestOfLine()
{
    int ch;
    while(ch = getc(stdin), ch != EOF && ch != '\n')
    { } /* Gobble each character. */

    /* Reset the error status of the stream. */
    clearerr(stdin);
}

Boolean checkString(char * string) {
	if (string[strlen(string)-1]!='\n') {
		readRestOfLine();
		return FALSE;
	}
	string[strlen(string)-1] = '\0';
	return TRUE;
}

void addSpace(int numString, int needSpace) {
	int i;
	for (i=0; i<needSpace-numString;i++) {
		printf(" ");
	}
	printf(STOCK_DELIM);
}

void calculateSpace(int digit, int needSpace) {
	int count=0, i;
	while (digit != 0) {
		count++;
		digit /= 10;
	}

	for (i=0; i<needSpace-count; i++) {
		printf(" ");
	}
	printf(STOCK_DELIM);
}
