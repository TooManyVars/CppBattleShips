#pragma once
#include "Entity.h"

class Player: public Entity
{
public:

	//Player constructor. take parameters, and then put those as parameters into the base "Entity" class.
	Player(string pName, int bCols, int bRows, string water, string ship) : Entity(pName, bCols, bRows, water, ship) {};

	virtual vector<int> guessShip(int boardSize) override;

	void placeShip(); //place a sinle ship on the board.
};