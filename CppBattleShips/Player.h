#pragma once
#include "Entity.h"

class Player: public Entity
{
public:

	//Player constructor. take parameters, and then put those as parameters into the base "Entity" class.
	Player(string pName, int bCols, int bRows, string water, string ship) : Entity(pName, bCols, bRows, water, ship) {};

	virtual void placeShip() override;
	virtual vector<int> guessShip(int boardSize) override;
	int getValidCinput(string axis); //handles getting valid input for coordinates on the board, making sure they are within the bounds of the board.
};