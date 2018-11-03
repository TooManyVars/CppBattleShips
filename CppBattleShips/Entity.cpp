#include "stdafx.h"
#include <random>
#include <limits> //used when handling bad input.

using namespace std;

Entity::Entity(string pName, int bCols, int bRows, string water, string ship): playerName(pName), boardRows(bCols), boardColumns(bCols), water(water), ship(ship)
{

	//initialise the board(max 15x15 grid).
	for (int i = 0; i < bCols; i++)//determines the amount of columns.
	{
		vector<string>temp; //a temporary holding place to put our desired amount of "~"s per row.

		for (int x = 0; x < bRows; x++)//determines the number of rows.
		{
			temp.push_back(water); //created row
		}

		//append created row to both the real and the detection board.
		board.push_back(temp); 
		detectionBoard.push_back(temp);
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

int Entity::getInitialShips()
{
	return initialShips;
}

int Entity::getValidCinput(string axis)
{
	int coordinate;

	coordinate = getValidIntInput();//Get input for one half of one of the set of coordinates.

	while (!moreThanZero(coordinate)) //while loop to validate input of numbers which are less than 1(we do this because we want the user to give coordinates starting from 1.
	{
		cout << setw(80) << flush;
		printf("\n %s coordinate cannot be less than 1, please re-enter:\n", axis.c_str());
		coordinate = getValidIntInput();
	}

	//decrement AFTER checking if the input is below 1, as 1 is decremented to 0 and caught by the loop, ruling out placement of ships on row 1.
	coordinate -= 1; //decrement by 1 so that the user can give a row and column number starting from 1.

					 //if the axis specifed was "row", check to see if the row number exists/is on the board. if it doesn't, loop input until it does.
	if (axis == "row")
	{

		//make sure the player can't reference a row that doesn't exist on the row(which could either be above the size of the row/column or below 0.
		while (coordinate > board.size() - 1)
		{
			cout << "\nRow does not exist within the board, please enter a different row." << endl;
			coordinate = getValidIntInput();
			coordinate -= 1; //decrement player input again so that they can always enter coordinates starting from 1.
		}
	}

	//we could easily reference the number of  rows, as they are the same, but to be more specific we reference the amount of columns in each row.
	//similar algorithim for validation of "row"
	else if (axis == "column")
	{
		while (coordinate > board[0].size() - 1)
		{
			cout << "Column does not exist within the board, please enter a different column." << endl;
			coordinate = getValidIntInput();
			coordinate -= 1;
		}
	}

	//if the coordinate can be verified and exists on the board, return it.
	return coordinate;
}

vector<vector<string> >Entity::getBoard()
{
	return board;
}

int Entity::getBoardSize()
{
	return boardColumns;
}

//draw the detection board to that it can be displayed to the player(s).
void Entity::drawBoard()
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

int Entity::getRN(unsigned int min, unsigned int max)
{
	//min: this number can be generated.
	//max: everything up until this number can be generated.

	random_device rd;
	uniform_int_distribution<int>dist(min, max);

	return dist(rd);
}

bool Entity::moreThanZero(int value)
{
	if (value > 0)
	{
		return true;
	}

	return false;
}

//takes in a set of coordinates(the vector will always be of length 2) and checks whether a ship exists there on the entity's board. 
//If it does, destroy it and replace a water cell at the position.
//The destroyer parameter is used to get the name of the player/enemy who destroyed the ship.
void Entity::destroyShip(vector<int>coordinates, string destroyer)
{
	//coordinates[0] is the X axis or the rows, and coordinates[1] is the y axis/column.
	if (board[coordinates[0]][coordinates[1]] == ship)
	{
		cout << "Hit!" << endl; //we need a better way of formatting text here.
		printf("%s hit a ship at coordinates %i,%i!\n",destroyer.c_str(), coordinates[0],coordinates[1]);
		board[coordinates[0]][coordinates[1]] = water;//the "ship" has been sunken; make the position water again.
		shipsLeft -= 1;
	}

	else
	{
		printf("\n%s missed!", destroyer.c_str());
	}	
}

void Entity::placeShip()
{
	unsigned int row;
	unsigned int column;

	cout << "\nEnter the desired row: " << endl;
	row = getValidCinput("row");

	cout << "\nEnter the desired column: " << endl;
	column = getValidCinput("column");

	while (board[row][column] == ship)
	{
		cout << "\nThere is already a ship at the given position." << endl;
		cout << "\nEnter another desired row to place your ship:" << endl;
		row = getValidCinput("row");
		cout << "\nEnter another desired column to place your ship:" << endl;
		column = getValidCinput("column");
	}

	board[row][column] = ship;
	drawBoard();
}

void Entity::autoPlaceShip()
{
	//get a random column/row number between 0 and the maximum number of columns/rows
	int randomColumn = getRN(0, boardColumns - 1);
	int randomRow = getRN(0, boardRows - 1);

	//assign a cell in the grid to a ship using the random set of coordinates.
	//this referencing assumes that the inner vectors are the rows, and their indexes are the columns.
	board[randomRow][randomColumn] = ship;
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

//returns a string with a specified number of characters. simplified custom version of the setw function.
string Entity::setw(int amount)
{
	string finalString;

	for (int x = 0; x <= amount; x++)
	{
		finalString += " ";
	}

	return finalString;
}
