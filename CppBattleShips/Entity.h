#pragma once
#include <iostream>

using namespace std;

class Entity
{
	const int scoreAwarded; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.

	int score;
	string playerName;
	//string board[]; //implement later
};