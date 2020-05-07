/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

typedef enum boolean
{
    FALSE = 0,
    TRUE
} Boolean;

#define NEW_LINE_SPACE 1
#define NULL_SPACE 1
#define EMPTY_SPACE 1
#define DELIM_SPACE 1

/**
 * This is used to compensate for the extra character spaces taken up by
 * the '\n' and '\0' when input is read through fgets().
 **/
#define EXTRA_SPACES (NEW_LINE_SPACE + NULL_SPACE)

#define EMPTY_STRING ""

#define STOCK_DELIM "|"
/**
 * Call this function whenever you detect buffer overflow.
 **/
void readRestOfLine();

/*make set of char into string*/
Boolean checkString(char * string);

/* print space as much as the parameter that is passed after string is printed*/
void addSpace(int numString, int needSpace);

/* print space as much as the parameter that is passed after integer is printed*/
void calculateSpace(int digit, int needSpace);

#endif
