#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	int score;
	int boardColumns;
	int boardRows;

	string playerName;
	vector<vector<string> >board; //implement later

public:

	Entity(int s, string pName, int bCols, int bRows);

	//Getter functions.
	int getScore();
	string getPlayerName();

	void drawBoard();
};