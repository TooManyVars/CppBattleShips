#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	int score;
	string playerName;
	vector<string>board; //implement later

public:

	Entity(int s, string pName);

	int getScore();
	string getPlayerName();
};