#include "stdafx.h"

using namespace std;

Entity::Entity(int s, string pName, int bCols, int bRows) : score(s), playerName(pName), boardRows(bCols), boardColumns(bCols)
{
	string water = "0"; //each cell will default to this "0" which indicates empty waters.

	vector<string>temp; //a temporary holding place to put our desired amount of "0"s per row.

	for (int i = 0; i < bCols; i++)//determines the amount of columns.
	{
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

void Entity::drawBoard()
{
	for (int i = 0; i < board.size(); i++)//iterate through the board's outer vector
	{
		for (int x = 0; x < board.size(); x++) //iterate through each index's inner vector
		{
			cout << board[i][x] << " "; //output it's contents
		}
		cout << endl; //end the line.
	}
}