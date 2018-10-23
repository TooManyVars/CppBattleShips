#pragma once
#include <iostream>

using namespace std;

class Entity
{

protected:

	const int scoreAwarded = 100; //haven't decided the score awarded for sinking a ship yet, so for now we'll default to 100.
	
	int boardColumns;
	int boardRows;

	//i want the water and the ship symbols to be custom.
	string water; //the symbol indicating that there is no ship in that position.
	string ship; //the symbol indicating  ship.

	unsigned int score = 0;
	unsigned int initialShips; //the number of ships the player will start with. will be calculated in the constructor.
	unsigned int shipsLeft; //the number of ships left(will be set after the player/AI places their ships

	string playerName;
	vector<vector<string> >board; //where battle will be done, put simply.

public:

	Entity(string pName, int bCols, int bRows, string water, string ship);

	//Simple Getter methods.
	int getScore();
	int getBoardSize(); //get the board size(represents both height and width).
	int ShipsRemaining();

	string getPlayerName();
	string getWater(); //gets the symbol being used to represent water.
	string getShip(); // gets the symbol being used to represent ships.

	vector<vector<string> >getBoard();
	
	//Core game methods.
	void drawBoard();
	void destroyShip(vector<int>coordinates);

	//polymorphic game methods.
	virtual void placeShip() { cout << "PLACE SHIP METHOD" << endl; }; //place a sinle ship.
	
	/*how this function is going to work:

		- Will take a board size(will represent both the rows and columns: they will be presumed the same)
		- In the enemy implementation: a random row and column will be selected to act as coordinates for the enemy board.
		- in the player implementation: the player will get the choice of picking one set of coordinates 
		in order to guess where a possible ship may be.
		- both sets of coordinates will be returned as vector values, which can then be passed into destroyShip to determine whether there was a hit or not and destroy the ship accordingly.
	*/

	//returns 0,0 by default.
	virtual vector<int>guessShip(int boardSize) { return { 0,0 }; };//guess the coordinates of a ship on the adversary board.

	//unacssociated helper functions.
	static int getRN(unsigned int min, unsigned int max); //returns a random number in a given range.
	static int getValidIntInput(); //handles incorrect values and returns valid input(in this case ints)
	
};