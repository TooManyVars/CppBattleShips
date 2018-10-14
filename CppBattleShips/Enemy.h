#pragma once
#include "stdafx.h"

class Enemy : public Entity
{
public:
	Enemy(string pName, int bCols, int bRows) : Entity(pName, bCols,bRows) {};

	virtual void placeShip() override;
	virtual void guessShip() override;
};
