#include "stdafx.h"

using namespace std;

int Player::getValidCinput(string axis)
{
	int coordinate;

	cout << "\nEnter the desired " << axis << ":" << endl; //get input for one of the possible axis of coordinates.
	coordinate = getValidIntInput();

	//if the axis specifed was "row", check to see if the row number exists/is on the board. if it doesn't, loop input until it does.
	if (axis == "row")
	{
		while (coordinate > board.size()-1)
		{
			cout << "\nRow does not exist within the board, please enter a different row." << endl;
			coordinate = getValidIntInput();
		}
	}

	else if (axis == "column")
	{
		while (coordinate > board[0].size())
		{
			cout << "Column does not exist within the board, please enter a different column." << endl;
			coordinate = getValidIntInput();
		}
	}

	//if the coordinate can be verified and exists on the board, return it.
	return coordinate;
}

void Player::placeShip()
{

	unsigned int row;
	unsigned int column;

	row = getValidCinput("row");
	column = getValidCinput("column");

	while (board[row][column] == ship)
	{
		cout << "\nThere is already a ship at the given position, please enter a different set of coordinates: " << endl;
		row = getValidCinput("row");
		column = getValidCinput("column");
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