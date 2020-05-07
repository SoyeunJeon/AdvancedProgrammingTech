/******************************************************************************
** Student name: 	Soyeun Jeon
** Student number: 	s3622567
** Course: 			Advanced Programming Techniques - S1 2018
******************************************************************************/

#include "player.h"

void initialisePlayer(Player * player, Position * position, Direction direction)
{
    /* initialise a player's first position and direction */

    player -> position.x = position->x;
    player -> position.y = position->y;
    player-> direction = direction;
    player -> moves = 0;
}

void turnDirection(Player * player, TurnDirection turnDirection)
{
    /* turn the direction based on the given rotation map*/

    if (turnDirection == TURN_LEFT) {
    	if (player->direction == NORTH) {
            player->direction = WEST;
        }
        else if (player->direction == SOUTH) {
    		player->direction = EAST;
        }
    	else if (player->direction == EAST) {
    		player->direction = NORTH;
        }
    	else if (player->direction == WEST) {
    		player->direction = SOUTH;
        }
    	
    } else if (turnDirection == TURN_RIGHT) {
    	if (player->direction == NORTH) {
    		player->direction = EAST;
        }
    	else if (player->direction == SOUTH) {
    		player->direction = WEST;
        }
    	else if (player->direction == EAST) {
    		player->direction = SOUTH;
        }
    	else if (player->direction == WEST) {
    		player->direction = NORTH;
        }	
    }
}

Position getNextForwardPosition(const Player * player)
{
    /* change the position of a player when the user input is forward */
    
	Position position;
	position.x = player->position.x;
	position.y = player->position.y;
    

    if (player->direction == EAST) {
        position.y++;
    } else if (player->direction == WEST) {
        position.y--;
    } else if (player->direction == SOUTH) {
        position.x++;
    } else if (player->direction == NORTH) {
        position.x--;
    }

    return position;
}

void updatePosition(Player * player, Position position)
{
    /* set the player's position to the position that is get by the parameter in a function */

    player->position = position;
    player->moves++;
}

void displayDirection(Direction direction)
{
    /* display the direction arrow according to the direction */

    if (direction == NORTH){
    	printf("%s|", DIRECTION_ARROW_OUTPUT_NORTH);
    } 
    else if (direction == EAST) {
    	printf("%s|", DIRECTION_ARROW_OUTPUT_EAST);
    } 
    else if (direction == WEST){
    	printf("%s|", DIRECTION_ARROW_OUTPUT_WEST);
    } 
    else if (direction == SOUTH) {
    	printf("%s|", DIRECTION_ARROW_OUTPUT_SOUTH);
    }
    
}
