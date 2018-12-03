#pragma once
#include "stdafx.h"

class Enemy : public Entity
{
public:
	Enemy(string pName, int bCols, int bRows, string water, string ship) : Entity(pName, bCols,bRows, water, ship) {};

	virtual vector<int>guessShip(int boardSize) override;

	//Overrided variation of the destroyShip method adds the ship at the discovered coordinates onto the detection board.
	virtual bool destroyedShip(vector<int>coordinates, string destroyer) override;
	//Enemy variation of the drawBoard method only shows the detection board instead of the real board.
	virtual void drawBoard() override;

};
