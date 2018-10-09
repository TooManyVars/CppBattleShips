#pragma once
#include "stdafx.h"

class Enemy : public Entity
{
public:
	Enemy(int s, string pName, int bCols, int bRows) : Entity(s, pName, bCols,bRows) {};
};
