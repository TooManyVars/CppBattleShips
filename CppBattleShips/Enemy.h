#pragma once
#include "stdafx.h"

class Enemy : public Entity
{
public:
	Enemy(string pName, int bCols, int bRows, string water, string ship) : Entity(pName, bCols,bRows, water, ship) {};

	virtual vector<int>guessShip(int boardSize) override;
};
