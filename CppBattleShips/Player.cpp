#include "stdafx.h"

using namespace std;

//used to generate a set of coordinates where an enemy ship may be. does not actually check whether there is a ship there or not; that's destroyShip's job
vector<int>Player::guessShip(int boardSize)
{
	unsigned int row;
	unsigned int column;

	cout << "\n" << centerText() << "Enter the row(going horizontal) where you think an enemy ship may be:" << endl;
	row = getValidCinput("row");

	cout << centerText() << "Enter a possible column(going vertical):" << endl;
	column = getValidCinput("column");

	//cast back to signed before returning as vector coordinates just to clear those silly warnings(it's also good practice).
	return { (signed int)row, (signed int)column };
}

void Player::placeShip()
{
	unsigned int row;
	unsigned int column;

	cout << "\n" << centerText() << "Enter the desired row: " << endl;
	row = getValidCinput("row");

	cout << "\n" << centerText() << "Enter the desired column: " << endl;
	column = getValidCinput("column");

	while (board[row][column] == ship)
	{
		cout << "\n" << centerText() << "There is already a ship at the given position." << endl;
		cout << "\n" << centerText() << "Enter another desired row to place your ship:" << endl;
		row = getValidCinput("row");
		cout << "\n" << centerText() << "Enter another desired column to place your ship:" << endl;
		column = getValidCinput("column");
	}

	board[row][column] = ship;
}