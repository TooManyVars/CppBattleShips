#include "stdafx.h"

using namespace std;

vector<int> Enemy::guessShip(int boardSize) //guess where the player has positioned their ships, perhaps using some math.
{
	int guessedRow = getRN(0, boardSize - 1);
	int guessedColumn = getRN(0, boardSize - 1);

	return { guessedRow, guessedColumn };
}