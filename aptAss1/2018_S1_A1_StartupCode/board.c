/******************************************************************************
** Student name: 	Soyeun Jeon	
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "board.h"

Cell BOARD_1[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED }
};

Cell BOARD_2[BOARD_HEIGHT][BOARD_WIDTH] =
{
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};


void initialiseBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i,j;
	for (i=0;i<BOARD_HEIGHT;i++) {
		for (j=0;j<BOARD_WIDTH;j++) {
			board[i][j] = EMPTY; /* set all the properties of board into EMPTY */
		}
	}
}

void loadBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH],
               Cell boardToLoad[BOARD_HEIGHT][BOARD_WIDTH])
{
	int i,j;

	/* copy properties of boardToLoad into a board */
	for (i=0;i<BOARD_HEIGHT;i++) {
		for (j=0;j<BOARD_WIDTH;j++) {
			if (boardToLoad[i][j] == EMPTY) {
				board[i][j] = EMPTY;
			}
			if (boardToLoad[i][j] == BLOCKED) {
				board[i][j] = BLOCKED;
			}		
			if (boardToLoad[i][j] == PLAYER) {
				board[i][j] = PLAYER;
			}
		}
	}
}

Boolean placePlayer(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Position position)
{
	
	int col = position.x;
	int row = position.y;

	/* if the board is filled with blocked, return False so that player cannot go through the block. */
	if (board[col][row] == BLOCKED) {
		return FALSE;
	} else {
		board[col][row] = PLAYER;
		return TRUE; 
	}	 
}

PlayerMove movePlayerForward(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
	Position prePos = player->position;
	Position newPos = getNextForwardPosition(player);

	/* possible position input range is 0 to 9 */
	if (newPos.x < 0 || newPos.y < 0 || newPos.x > BOARD_WIDTH - 1 || newPos.y > BOARD_HEIGHT - 1) {
		printf("\nThe car is at the edge of the board and cannot move further in that direction.\n");
		return OUTSIDE_BOUNDS;
	}
	/* user cant place a player on the blocked place */
	if (board[newPos.x][newPos.y] == BLOCKED) {
		printf("\nError: cannot move forward because the road is blocked.\n");
		return CELL_BLOCKED;
	}
	/* if user choose right place, change previous player place to empty and put player in a new position */
	board[prePos.x][prePos.y] = EMPTY;
	updatePosition(player, newPos);
	board[player->position.x][player->position.y] = PLAYER;
	return PLAYER_MOVED; 
}

void displayBoard(Cell board[BOARD_HEIGHT][BOARD_WIDTH], Player * player)
{
	if (player != NULL) {	/* if player is not NULL, player will be printed based on the direction. */
		int i,j,k;
		Direction direction = player -> direction;

		/* first row of the board with column number */
		printf("| |");
		for (i=0;i<BOARD_WIDTH;i++) {
			printf("%d|",i);
		}

		/* print out character based on board properties */
		for (j=0;j<BOARD_HEIGHT;j++) {
			printf("\n|%d|",j);
			for (k=0;k<BOARD_WIDTH;k++) {
				if ( board[j][k] == EMPTY) {
					printf("%s|", EMPTY_OUTPUT);
				}
				else if (board[j][k] == BLOCKED) {
					printf("%s|", BLOCKED_OUTPUT);
				}
				else if(board[j][k] == PLAYER) {
					displayDirection(direction);
				}
				
			}
			
		}
	} else {
		int i,j,k;
		printf("\n| |");
		for (i=0;i<BOARD_WIDTH;i++) {
			printf("%d|",i);
		}
		for (j=0;j<BOARD_HEIGHT;j++) {
			printf("\n|%d|",j);
			for (k=0;k<BOARD_WIDTH;k++) {
				if ( board[j][k] == EMPTY)
				printf("%s|", EMPTY_OUTPUT);
				if (board[j][k] == BLOCKED)
				printf("%s|", BLOCKED_OUTPUT);
			}
		}
	}
	printf("\n\n");
}
