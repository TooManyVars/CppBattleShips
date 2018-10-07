#include "stdafx.h"

using namespace std;

Entity::Entity(int s, string pName) : score(s), playerName(pName)
{
	//setup the board, which is a vector.
}

string Entity::getPlayerName()
{
	return playerName;
}

int Entity::getScore()
{
	return score;
}