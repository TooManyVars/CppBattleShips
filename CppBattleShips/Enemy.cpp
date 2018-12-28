#include "stdafx.h"

using namespace std;

vector<int> Enemy::guessShip(int boardSize) //guess where the player has positioned their ships, perhaps using some math.
{
	int guessedRow = getRN(0, boardSize - 1);
	int guessedColumn = getRN(0, boardSize - 1);

	return { guessedRow, guessedColumn };
}


//The enemy class has it's own implementation so that we can introduce the concept of the detection board.
bool Enemy::destroyedShip(vector<int> coordinates, string destroyer)
{
	//coordinates[0] is the X axis or the rows, and coordinates[1] is the y axis/column.
	if (board[coordinates[0]][coordinates[1]] == ship)
	{
		cout << centerText() << flush;
		cout << "Hit!" << endl; //we need a better way of formatting text here.
		cout << centerText() << flush;
		printf("%s hit a ship at coordinates %i,%i!\n", destroyer.c_str(), coordinates[0]+1, coordinates[1]+1);
		detectionBoard[coordinates[0]][coordinates[1]] = ship;//the "ship" has been sunken; make the position known on the detection board.
		shipsLeft -= 1;

		return true;
	}

	else
	{
		printf("\n%s%s missed!\n", centerText().c_str(),destroyer.c_str());
		return false;
	}
}
