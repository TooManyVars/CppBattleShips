#include "stdafx.h"

using namespace std;

//requires completion(last edited 14/10/18 at 9:45am.
void Enemy::placeShip() //this will be random for now, but i'm thinking of adding some math in order to place the ships.
{
	//get a random column/row number between 0 and the maximum number of columns/rows
	int randomColumn = getRN(0, boardColumns-1);
	int randomRow = getRN(0, boardRows-1);

	//assign a cell in the grid to a ship using the random set of coordinates.
	//this referencing assumes that the inner vectors are the rows, and their indexes are the columns.
	board[randomRow][randomColumn] = ship;
}

void Enemy::guessShip() //guess where the player has positioned their ships, perhaps using some math.
{

}