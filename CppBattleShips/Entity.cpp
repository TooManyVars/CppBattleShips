#include "stdafx.h"

using namespace std;

Entity::Entity(string pName, int bCols, int bRows) : playerName(pName), boardRows(bCols), boardColumns(bCols)
{

	//initialise the board(max 15x15 grid)
	string water = "~"; //each cell will default to this "~" which indicates empty waters.

	

	for (int i = 0; i < bCols; i++)//determines the amount of columns.
	{
		vector<string>temp; //a temporary holding place to put our desired amount of "~"s per row.

		for (int x = 0; x < bRows; x++)//determines the number of rows.
		{
			temp.push_back(water); //created row
		}

		board.push_back(temp); //append created row to the board.
	}
}

string Entity::getPlayerName()
{
	return playerName;
}

int Entity::getScore()
{
	return score;
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