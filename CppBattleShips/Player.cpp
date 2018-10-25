#include "stdafx.h"

using namespace std;

int Player::getValidCinput(string axis)
{
	int coordinate;

	cout << "\nEnter the desired " << axis << ":" << endl; //Get input for one half of one of the set of coordinates.
	coordinate = getValidIntInput();	

	while (!moreThanZero(coordinate)) //while loop to validate input of numbers which are less than 1(we do this because we want the user to give coordinates starting from 1.
	{
		cout << "\n" << axis << " coordinate cannot be less than 1, please re-enter: " << endl;
		coordinate = getValidIntInput();
	}

	//decrement AFTER checking if the input is below 1, as 1 is decremented to 0 and caught by the loop, ruling out placement of ships on row 1.
	coordinate -= 1; //decrement by 1 so that the user can give a row and column number starting from 1.

	//if the axis specifed was "row", check to see if the row number exists/is on the board. if it doesn't, loop input until it does.
	if (axis == "row")
	{
		
		//make sure the player can't reference a row that doesn't exist on the row(which could either be above the size of the row/column or below 0.
		while (coordinate > board.size()-1)
		{
			cout << "\nRow does not exist within the board, please enter a different row." << endl;
			coordinate = getValidIntInput();
			coordinate-=1; //decrement player input again so that they can always enter coordinates starting from 1.
		}
	}

	//we could easily reference the number of  rows, as they are the same, but to be more specific we reference the amount of columns in each row.
	//similar algorithim for validation of "row"
	else if (axis == "column") 
	{
		while (coordinate > board[0].size()-1)
		{
			cout << "Column does not exist within the board, please enter a different column." << endl;
			coordinate = getValidIntInput();
			coordinate-=1;
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

//check whether this function works efficently or not.
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