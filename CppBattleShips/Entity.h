#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	
	int boardColumns;
	int boardRows;

	//i want the water and the ship symbols to be custom.
	string water; //the symbol indicating that there is no ship in that position.
	string ship; //the symbol indicating  ship.

	unsigned int score = 0;
	unsigned int initialShips; //the number of ships the player will start with. will be calculated in the constructor.
	unsigned int shipsLeft; //the number of ships left(will be set after the player/AI places their ships

	string playerName;
	vector<vector<string> >board; //where battle will be done, put simply.

public:

	Entity(string pName, int bCols, int bRows, string water, string ship);

	//Simple Getter methods.
	int getScore();
	string getPlayerName();
	int ShipsRemaining();

	//Core game methods.
	void drawBoard();
	static void destroyShip(vector<vector<string> >board,string water,int row, int column); //destroys a ship given a board, a set of coordinates within said board and the water to replace the ship.

	//polymorphic game methods.
	virtual void placeShip() { cout << "PLACE SHIP METHOD" << endl; }; //place a sinle ship.
	virtual void guessShip() { cout << "GUESS SHIP METHOD" << endl; };//guess the coordinates of a ship on the adversary board.

	//unacssociated helper functions.
	static int getRN(unsigned int min, unsigned int max); //returns a random number in a given range.
};