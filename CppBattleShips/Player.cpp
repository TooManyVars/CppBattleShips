#include "stdafx.h"

using namespace std;

//used to generate a set of coordinates where an enemy ship may be. does not actually check whether there is a ship there or not; that's destroyShip's job
vector<int>Player::guessShip(int boardSize)
{
	unsigned int row;
	unsigned int column;

	cout << "\n" << centerText() << "Enter the row where you think an enemy ship may be:" << endl;
	row = getValidCinput("row");

	cout << centerText() << "Enter a possible column:" << endl;
	column = getValidCinput("column");

	//cast back to signed before returning as vector coordinates(i have no clue why???)
	return { (signed int)row, (signed int)column };
}