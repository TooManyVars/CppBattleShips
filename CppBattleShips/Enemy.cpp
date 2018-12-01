#include "stdafx.h"

using namespace std;

vector<int> Enemy::guessShip(int boardSize) //guess where the player has positioned their ships, perhaps using some math.
{
	int guessedRow = getRN(0, boardSize - 1);
	int guessedColumn = getRN(0, boardSize - 1);

	return { guessedRow, guessedColumn };
}

void Enemy::destroyShip(vector<int> coordinates, string destroyer)
{
	//coordinates[0] is the X axis or the rows, and coordinates[1] is the y axis/column.
	if (board[coordinates[0]][coordinates[1]] == ship)
	{
		cout << centerText() << flush;
		cout << "Hit!" << endl; //we need a better way of formatting text here.
		cout << centerText() << flush;
		printf("%s hit a ship at coordinates %i,%i!\n", destroyer.c_str(), coordinates[0]+1, coordinates[1]+1);
		board[coordinates[0]][coordinates[1]] = water;//the "ship" has been sunken; make the position water again.
		shipsLeft -= 1;
	}

	else
	{
		printf("\n%s%s missed!\n", centerText().c_str(),destroyer.c_str());
	}
}

//enemy variation of the drawBoard method should only show the detection board instead of the real board.
void Enemy::drawBoard()
{
	printf("\n%s's board: ", playerName.c_str());
	cout << endl;
	for (unsigned int i = 0; i < board.size(); i++)//iterate through the board's outer vector
	{
		for (unsigned int x = 0; x < board[i].size(); x++) //iterate through each index's inner vector
		{
			cout << board[i][x] << "  "; //output it's contents
		}
		cout << endl; //end the line.
	}

	cout << "  " << endl;
}
