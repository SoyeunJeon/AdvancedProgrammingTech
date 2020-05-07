/******************************************************************************
** Student name: 	Soyeun Jeon	
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "game.h"

#define INSTRUCTION "You can use the following commands to play the game:\nload <g>\n	g: number of the game board to load\ninit <x>,<y>,<direction>\n	x: horizontal position of the car on the board (between 0 & 9)\n	y: vertical position of the car on the board (between 0 & 9)\n	direction: direction of the car's movement (north, east, south, west)\nforward (or f)\nturn_left (or l)\nturn_right (or r)\nquit\n"

#define DISPLAYBOARD "At this stage of the program, only two commands are acceptable:\nload <g>\nquit\n\n"

#define GAMEBOARDINIT "At this stage of the program, only three commands are acceptable:\nload <g>\ninit <x>,<y>,<direction>\nquit\n\n"

#define PLAYGAME "At this stage of the program, only four commands are acceptable:\nforward\nturn_left(or l)\nturn_right(or r)\nquit\n"


void playGame()/* initialize board */
{
	Cell board[BOARD_HEIGHT][BOARD_WIDTH];
	char option[10];
	
	printf("\n%s", INSTRUCTION);
	initialiseBoard(board); /* initialize board before load board */
	displayBoard(board, NULL);
		
	printf("%s", DISPLAYBOARD);
	while(fgets(option, 10, stdin)) {

		if (option[strlen(option)-1]!='\n') {
			readRestOfLine();
		}
		option[strlen(option)-1] = '\0';
		
		/* load board based on user input 1 or 2 */
		if (strcmp(option, "load 1")==0) {
			loadBoard(board, BOARD_1);
			displayBoard(board, NULL);
			printf("%s", GAMEBOARDINIT);
			boardGame(board);
			break;
		} else if (strcmp(option, "load 2")==0) {
			loadBoard(board, BOARD_2);
			displayBoard(board, NULL);
			printf("%s", GAMEBOARDINIT);
			boardGame(board);
			break;
		} else if (strcmp(option, COMMAND_QUIT)==0) {
			printf("To main manu...\n");
			break;
		} else {
			printf("\nInvalid input. Please try again.\n");
			initialiseBoard(board);
			displayBoard(board, NULL);	
			printf("%s", DISPLAYBOARD);

			continue;
		}
	}
}


void boardGame(Cell board[BOARD_HEIGHT][BOARD_WIDTH]) /* place player */
{
	char option[50];
	char *row, *column, *direc, *inst;
	Player mainplayer;
	Position position;
	Direction direction;

	while (fgets(option, 50, stdin)) {		
		if (option[strlen(option)-1]!='\n') {
			readRestOfLine();
		} 
		option[strlen(option)-1] = '\0';

		inst = strtok(option, " ");
		row = strtok(NULL, ",");
		column = strtok(NULL, ",");
		direc = strtok(NULL, ",");

		if (inst == NULL) { /* first token should not always be null */
			printf("\nInvalid input. Please try again.\n");
			displayBoard(board, NULL);
			printf("%s", GAMEBOARDINIT);
			continue;
		}
		if (strcmp(inst, COMMAND_LOAD) == 0 && row != NULL && atoi(row)<3 && atoi(row)>0 ) { 
		/* second token should not be a null and meet initializing requirements */
			if (strcmp(row, "1")==0) {
				loadBoard(board, BOARD_1);
			} else if (strcmp(row, "2")==0) {
				loadBoard(board, BOARD_2);
			}
			displayBoard(board, NULL);
			printf("%s", GAMEBOARDINIT);
			continue;
		} else if (strcmp(option, COMMAND_QUIT) == 0){
			printf("To main manu...\n");
			break;
		} else if (strcmp(inst, COMMAND_INIT)==0 && column != NULL && direc != NULL && atoi(column) >= 0 && atoi(column) < BOARD_HEIGHT && atoi(row) >= 0 && atoi(row) < BOARD_WIDTH ) {
			/* position x, y should be not null, between 0 and 9, and direction should be not null */
			position.x = atoi(column);
			position.y = atoi(row);
			 /* user cannot put player on blocked place */
        	if (strcmp(direc, DIRECTION_NORTH)==0 || strcmp(direc, DIRECTION_SOUTH)==0 || strcmp(direc, DIRECTION_WEST)==0 || strcmp(direc, DIRECTION_EAST)==0) {
        		if (strcmp(direc, DIRECTION_NORTH)==0){ direction = NORTH;}
				else if (strcmp(direc, DIRECTION_SOUTH)==0) { direction = SOUTH;} 
				else if (strcmp(direc, DIRECTION_WEST)==0) { direction = WEST;}
				else if (strcmp(direc, DIRECTION_EAST)==0) { direction = EAST;}
				
				if (placePlayer(board, position) == TRUE) {
    	        	initialisePlayer(&mainplayer, &position, direction);
    	        	displayBoard(board, &mainplayer);
    	        	movePlayer(board, &mainplayer);
					break;
        		} else {
					printf("\nInvalid input. Place Blocked.\n\n");
					displayBoard(board, NULL);
					printf("%s", GAMEBOARDINIT);
				}			
			} else {
				printf("\nInvalid input. Wrong direction.\n\n");
				displayBoard(board, NULL);
				printf("%s", GAMEBOARDINIT);
			}
		} else {
			printf("\nInvalid input. Position not available.\n\n");
			displayBoard(board, NULL);
			printf("%s", GAMEBOARDINIT);
		}
	}
}

void movePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player *player) { /* move player, play game */
	
	char movement[10];

	printf("%s\n", PLAYGAME);
	while (fgets(movement, 10, stdin)) {
		if (movement[strlen(movement)-1]!='\n') {
			readRestOfLine();
		}
		movement[strlen(movement)-1] = '\0';

		if (strcmp(movement, COMMAND_FORWARD)==0 || strcmp(movement, COMMAND_FORWARD_SHORTCUT)==0) {
			movePlayerForward(board, player);
			displayBoard(board,player);
			printf("%s\n", PLAYGAME);	
			continue;		
		} else if (strcmp(movement, COMMAND_TURN_LEFT)==0 || strcmp(movement, COMMAND_TURN_LEFT_SHORTCUT)==0) {
			turnDirection(player, TURN_LEFT);
			displayBoard(board,player);
			printf("%s\n", PLAYGAME);
			continue;
		} else if (strcmp(movement, COMMAND_TURN_RIGHT)==0 || strcmp(movement, COMMAND_TURN_RIGHT_SHORTCUT)==0) {
			turnDirection(player, TURN_RIGHT);
			displayBoard(board,player);
			printf("%s\n", PLAYGAME);
			continue;
		} else if (strcmp(movement, COMMAND_QUIT)==0) {
			printf("Total player moves: %d\n", player->moves);
			printf("To main manu...\n");
			break;
		}
		printf("Invalid Input. Please try again.\n");
		displayBoard(board,player);
		printf("%s\n", PLAYGAME);
	}	
}