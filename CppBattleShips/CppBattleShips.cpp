// CppBattleShips.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

int main()
{	

	//Here, we should get the desired player and enemy name, desired board play size and pass them in to create enemy/player objects.

	
	cout << "test" << endl;


	Enemy ob("Enemy",15,15, "@","X"); 
	//Enemy ob2("Enemy1", 10, 10);
	//Enemy ob3("Enemy2", 5, 5);
	ob.drawBoard();
	
	//cout << "Ships left standing for " << ob.getPlayerName() << ": " << ob.ShipsRemaining() << endl;
	//cout << "Ships left standing for " << ob2.getPlayerName() << ": " << ob2.ShipsRemaining() << endl;
	//cout << "Ships left standing for " << ob3.getPlayerName() << ": " << ob3.ShipsRemaining() << endl;

	system("Pause");

    return 0;
}

