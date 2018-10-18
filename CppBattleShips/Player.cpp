#include "stdafx.h"

using namespace std;

void Player::placeShip()
{

	unsigned int row;
	unsigned int column;

	cout << "Enter the desired row:" << endl;
	row = getValidIntInput();

	while (row > board.size() - 1) //loop input to ensure the player does not enter a row number that doeesn't exist.
	{
		cout << "Row does not exist within the board, please enter a different row." << endl;
		row = getValidIntInput();
	}
	
	cout << "Enter the desired column:" << endl;
	column = getValidIntInput();


	//loop input to ensure the player does not enter a column number that doeesn't exist.
	//all columns will be the same size, so we can just reference the first one by default.
	while (column > board[0].size())
	{
		cout << "Column does not exist within the board, please enter a different column." << endl;
		column = getValidIntInput();
	}

	board[row][column] = ship;

	drawBoard();


}

vector<int>Player::guessShip(int boardSize)
{

	unsigned int row;
	unsigned int column;

	cout << "Enter the row where you think an enemy ship may be:" << endl;
	row = getValidIntInput();

	while (row > boardSize - 1)
	{
		cout << "Row does not exist, please re-enter:" << endl;
		row = getValidIntInput();
	}

	cout << "Enter a possible column:" << endl;
	column = getValidIntInput();

	while (column > boardSize - 1)
	{
		cout << "Column does not exist, please re-enter:" << endl;
		column = getValidIntInput();
	}

	//cast back to signed before returning as vector coordinates(i have no clue why???)
	return { (signed int)row, (signed int)column };
}