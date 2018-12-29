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
	unsigned int initialShips = 0; //the number of ships the player will start with. will be calculated in the constructor.
	unsigned int shipsLeft; //the number of ships left(will change if a player/Enemy ship is destroyed.)
	

	string playerName;

	//The board which is never shown on screen, and simply for guessing. 
	vector<vector<string> >board; 

	//The board visible to the player.
	//if a set of coordinates on the enemy board with a ship is guessed correctly, the detection board puts a ship on it's board at the same position.
	//the reason we don't put this into the derived enemy class is because it's more convinient to initialise it here, in the base classes constructor.
	vector<vector<string> >detectionBoard; 

public:
	//All the colors that we wish to change our text to.
	static const int lightMagenta = 13;
	static const int lightGreen = 10;
	static const int white = 15;

	Entity(string pName, int bCols, int bRows, string water, string ship);

	//Simple Getter methods.
	int getScore();
	int shipsRemaining(); //gets the number of ships left on an entity board.
	int getBoardSize(); //get the board size(represents both height and width).
	int getInitialShips();
	int getValidCinput(string axis); //handles getting valid input for coordinates on the board, making sure they are within the bounds of the board.

	string getPlayerName();
	string getWater(); //gets the symbol being used to represent water.
	string getShip(); // gets the symbol being used to represent ships.

	vector<vector<string> >getBoard();
	vector<vector<string> >getDetectionBoard();
	
	//Core game methods.

	//Draws the board, but is now in obselecense, given our Draw UI function in our main() file
	virtual void drawBoard(vector<vector<string> >Aboard);

	//Check whether a set of coordinates the player has given matches the coordinates of a ship on the board. if it does, the ship is considered destroyed.
	virtual bool destroyedShip(vector<int>coordinates, string destroyer);

	void outputEntityInformation();//Outputs the various attributes of the player/ship.
	void autoPlaceShip(); //automatically place a ship on the board using RNG.
	void autoPlaceShips();//places all ships onto a given board at random.
	void incrementScore() { score += 10; };//Increases the store by a set amount when the player sinks a ship.
	
	/*how this function is going to work:

		- Will take a board size(will represent both the rows and columns: they will be presumed the same)
		- In the enemy implementation: a random row and column will be selected to act as coordinates for the enemy board.
		- in the player implementation: the player will get the choice of picking one set of coordinates 
		in order to guess where a possible ship may be.
		- both sets of coordinates will be returned as vector values, which can then be passed into destroyShip to determine whether there was a hit or not and destroy the ship accordingly.
	*/

	//returns 0,0 by default.
	virtual vector<int>guessShip(int boardSize) { return { 0,0 }; };//guess the coordinates of a ship on the adversary board.

	//unacssociated helper functions. are also static.
	static int getRN(unsigned int min, unsigned int max); //returns a random number in a given range.
	static int getValidIntInput(); //handles incorrect values and returns valid input(in this case ints)

	static bool moreThanZero(int value); //checks whether a given number is more than 0.

	static string setw(int amount);
	//positions text at the center of the screen, depending on the height and width of the screen.
	static string centerText();
	//centers the input cursor.
	static void centerCursor();

	//Set the text color of the output, using a number assigned color(for example bright green is 10) goes up until 256 meaning that there are 256 possible colors.
	static void setTextColor(int colorNum);
};


