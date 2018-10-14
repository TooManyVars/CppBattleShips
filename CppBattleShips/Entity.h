#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	
	int boardColumns;
	int boardRows;

	unsigned int score = 0;
	unsigned int initialShips; //the number of ships the player will start with. will be calculated in the constructor.
	unsigned int shipsLeft; //the number of ships left(will be set after the player/AI places their ships

	string playerName;
	vector<vector<string> >board; //where battle will be done, put simply.

public:

	Entity(string pName, int bCols, int bRows);

	//Simple Getter methods.
	int getScore();
	string getPlayerName();
	int ShipsRemaining();

	//Core game methods.
	void drawBoard();
	//polymorphic game methods
	virtual void placeShip() { cout << "PLACE SHIP METHOD" << endl; };
	virtual void guessShip() { cout << "GUESS SHIP METHOD" << endl; };

	//unacssociated helper functions.
	static int getRN(unsigned int max, unsigned int min); //returns a random number in a given range.
};