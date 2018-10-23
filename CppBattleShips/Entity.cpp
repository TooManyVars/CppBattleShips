#include "stdafx.h"
#include <random>
#include <limits> //used when handling bad input.

using namespace std;

Entity::Entity(string pName, int bCols, int bRows, string water, string ship) : playerName(pName), boardRows(bCols), boardColumns(bCols), water(water), ship(ship)
{

	//initialise the board(max 15x15 grid).
	for (int i = 0; i < bCols; i++)//determines the amount of columns.
	{
		vector<string>temp; //a temporary holding place to put our desired amount of "~"s per row.

		for (int x = 0; x < bRows; x++)//determines the number of rows.
		{
			temp.push_back(water); //created row
		}

		board.push_back(temp); //append created row to the board.
	}


	//note that all of this logic is in light of the fact that the boards will all have the same height and width in order to make calculations easier.

	/* Percentage hit logic
	set the number of ships remaining, depending on the board size.
	5*5 boards or higher: 52-44% chance of hitting a boat.
	10*10 boards or higher: 44-33% chance of hitting a boat
	15*15 boards: 32% chance.
	*/

	initialShips = bCols * 0.8; //multiply the grid dimensions by 0.8 to make them smaller.

	/* Additional ships: additional logic
	5*5(min)-9*9: add 9 onto the amount of initialShips.
	10*10-14*14: add 35 onto the number of initialShips.
	15*15(Max): add 60 onto the number of initialShips.
	*/

	if (bCols >= 15)
	{
		initialShips += 60;
	}

	else if (bCols >= 10)
	{
		initialShips += 35;
	}

	else if (bCols >= 5)
	{
		initialShips += 9;
	}

	shipsLeft = initialShips; //initially set the remaining ships and initalShips to the same value.

}

string Entity::getPlayerName()
{
	return playerName;
}

int Entity::getScore()
{
	return score;
}

int Entity::shipsRemaining()
{
	return shipsLeft;
}

vector<vector<string> >Entity::getBoard()
{
	return board;
}

int Entity::getBoardSize()
{
	return boardColumns;
}

//note that unsigned integer variabes can only store positive whole values
void Entity::drawBoard()
{
	cout << playerName << "'s board:" << endl;
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

int Entity::getRN(unsigned int min, unsigned int max)
{
	//min: this number can be generated.
	//max: everything up until this number can be generated.

	random_device rd;
	uniform_int_distribution<int>dist(min, max);

	return dist(rd);
}


void Entity::destroyShip(vector<int>coordinates)
{
	//coordinates[0] is the X axis or the rows, and coordinates[1] is the y axis/column.
	if (board[coordinates[0]][coordinates[1]] == ship)
	{
		cout << "Hit!" << endl;
		board[coordinates[0]][coordinates[1]] = water;//the "ship" has been sunken; make the position water again.
		shipsLeft -= 1;
		
	}

	else
	{
		cout << "Miss" << endl;
	}
	
}

int Entity::getValidIntInput()
{
	int value;
	cin >> value;

	while (cin.fail()) //when the user gives anything other than a string:
	{
		//clear bad input flag
		cin.clear();
		//discard inputs
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//give error message.
		cout << "Value cannot be an integer, Please re-enter:" << endl;

		//get input again
		cin >> value;

	}

	return value;
}

string Entity::getWater()
{
	return water;
}

string Entity::getShip()
{
	return ship;
}