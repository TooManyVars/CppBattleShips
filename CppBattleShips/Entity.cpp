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


void Entity::outputEntityInformation()
{
	cout << Entity::centerText() << flush;
	printf("Board dimensions: %i x %i\n", boardColumns, boardRows);
	cout << Entity::centerText() << flush;
	printf("Water character: %s\n", water.c_str());
	cout << Entity::centerText() << flush;
	printf("Ship characters: %s\n", ship.c_str());
	cout << Entity::centerText() << flush;
	cout << "----------------" << endl;
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

	//Check that the expected input is not a string.

	while (!moreThanZero(coordinate)) //while loop to validate input of numbers which are less than 1(we do this because we want the user to give coordinates starting from 1.
	{
		printf("\n%s%s coordinate cannot be less than 1, please re-enter:\n", centerText().c_str(),axis.c_str());
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
			cout << "\n" << centerText() << "Row does not exist within the board, please enter a different row." << endl;
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
			cout << centerText() <<"Column does not exist within the board, please enter a different column." << endl;
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
//Returns either true or false so that we can determine, outside the class, whether or not the player/enemy hit or not and adjust their score accordingly.
bool Entity::destroyedShip(vector<int>coordinates, string destroyer)
{
	//cout << centerText() << flush; //center the text no matter the output.

	//coordinates[0] is the X axis or the rows, and coordinates[1] is the y axis/column.
	if (board[coordinates[0]][coordinates[1]] == ship)
	{
		cout << "\n" << centerText() << flush;
		cout << "Hit!" << endl; //we need a better way of formatting text here.
		cout << centerText() << flush;
		printf("%s hit a ship at coordinates %i,%i!\n",destroyer.c_str(), coordinates[0]+1,coordinates[1]+1);
		board[coordinates[0]][coordinates[1]] = water;//the "ship" has been sunken; make the position water again.
		shipsLeft -= 1;

		return true;
	}

	else
	{ 
		printf("\n%s%s missed!\n", centerText().c_str(),destroyer.c_str());
		cout << endl;

		return false;
	}	
}

void Entity::placeShip()
{
	unsigned int row;
	unsigned int column;

	cout << "\n" <<  centerText() << "Enter the desired row: " << endl;
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
	drawBoard();
}


void Entity::autoPlaceShip()
{
	//get a random column/row number between 0 and the maximum number of columns/rows
	int randomColumn = getRN(0, boardColumns - 1);
	int randomRow = getRN(0, boardRows - 1);

	//check if the coordinates generated already exist.
	while (board[randomRow][randomColumn] == ship)
	{
		//while there is already a ship at the generated set of coordinates, generate a new set.
		randomColumn = getRN(0, boardColumns - 1);
		randomRow = getRN(0, boardRows - 1);
	}


	//assign a cell in the grid to a ship using the random set of coordinates.
	//this referencing assumes that the inner vectors are the rows, and their indexes are the columns.
	board[randomRow][randomColumn] = ship;
}

void Entity::autoPlaceShips()
{
	for (int i = 0; i < initialShips; i++)
	{
		autoPlaceShip();
	}
}


int Entity::getValidIntInput()
{
	int value = 0;
	cin >> value;

	while (cin.fail()) //when the user gives anything other than an integer:
	{
		//clear bad input flag
		cin.clear();
		//discard inputs
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		
		//give error message.
		cout << centerText() << "Value must be positive/an integer, Please re-enter:" << endl;

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
	string finalString; //the final empty string we'll return so that we can space out the text.

	for (int x = 0; x <= amount; x++) //Depending on the amount of spaces needed
	{
		//add x number of spaces to the final string.
		finalString += " ";
	}

	return finalString;
}

string Entity::centerText() //Centers the text on screen to fit it to the middle of the window.
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);

	const double multiplier = 1.001; //the multiplier to add slightly more characters and push the text slightly further to the right, to more perfectly centered feel of the UI.

	string finalString;

	for (int x = 0; x <= rows * multiplier ; x++)
	{
		finalString += " ";
	}

	return finalString;
}

void Entity::setTextColor(int colorNum)
{
	/*
	Important colors:
		- light red = 12
		- light green = 10
		- white: 15
	*/

	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Get the console with the standard input handle(not much of a clue what that is, but stay with me) so that we can change the color of the text.
	SetConsoleTextAttribute(console, colorNum); //actually set the color of the text on screen.
}
