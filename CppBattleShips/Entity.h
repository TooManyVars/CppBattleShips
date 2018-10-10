#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	unsigned int score = 0;
	int boardColumns;
	int boardRows;
	unsigned int shipsLeft; //the number of ships left(will be set after the player/AI places their ships

	string playerName;
	vector<vector<string> >board; //implement later

public:

	Entity(string pName, int bCols, int bRows);

	//Getter functions.
	int getScore();
	string getPlayerName();

	//Core game functions.
	void drawBoard();
	virtual void placeShip() { cout << "PLACE SHIP METHOD" << endl; };
	virtual void guessShip() { cout << "GUESS SHIP METHOD" << endl; };
	//continue setting up game functionality.
};