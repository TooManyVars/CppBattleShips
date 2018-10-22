// CppBattleShips.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;


//used to get input foe water/ships.
//With parameter 'cellType' we can pass either 'ship' or 'water' into the error message output.
string getValidStringInput(string cellType) 
{
	
	/*
		Algorithim:
		- Get the string as input

		- Make sure the length isn't longer or shorter than 1 character, and that it isn't empty
		- If all these conditions are true, then return the now valid string.
	
	*/

	string s;
	cin >> s;

	while (s.length() > 1 || s.length() < 1)
	{
		cout << "Input for " << cellType << " was invalid : input for" << cellType << " cell must be at least 1 character long but no longer.\nPlease re - enter: " << endl;
		cin >> s;
	}

	while (s == " ")
	{
		cout << "Input for " << cellType << " was invalid : input for" << cellType << " cell must not be an empty character.\nPlease re - enter: " << endl;
		cin >> s;
	}

	return s;


}

Player setupPlayer() //will be used to setup the player object(s).
{
	/*
	  what we are going to do here is get all the nessecary member function values,
	  and then return a player object with those values.
	*/
	string name;
	int boardDimensions;
	string water;
	string ship;

	cout << "Enter your name: " << endl;
	cin >> name;

	while (name.length() > 15) //make sure that the player can't enter excessively long names.
	{
		cout << "Name cannot be more than 15 characters.\nPlease choose a different name." << endl;
		cin >> name;
	}

	//get a value from the player which will act as the length and the width of the board.
	cout << "Enter a board size (value will be true for both length and width) between 5 and 15\nnote that board sizes above 10*10 provide more difficulty in guessing)." << endl;
	boardDimensions = Entity::getValidIntInput();

	//make sure the board dimensions are between 5*5 and 15*15.
	while (boardDimensions > 15 || boardDimensions < 5)
	{
		cout << "board size is outside of the recommended range, please choose another set of dimensions." << endl;
		boardDimensions = Entity::getValidIntInput();
	}
	

	//get inputs for ships and water(create validation which prevents entering 0 or more than 1 character).
	cout << "Enter the desired character to represent shipless cells on the bord(can be literally any character on the keyboard): " << endl;
	cin >> water;

	while (water.length() < 0 || water.length() > 1)
	{
		cout << "Input for water was invalid: input water cell must be at least 1 character long but no longer.\nPlease re-enter: " << endl;
		cin >> water;
	}

	cout << "Enter the desired character to represent ships on the bord(again, can be literally any character on the keyboard) : " << endl;
	cin >> ship;

	while (ship.length() < 0 || ship.length() > 1)
	{
		cout << "Input for ship was invalid: input water cell must be at least 1 character long but no longer.\nPlease re-enter: " << endl;
		cin >> water;
	}

	while (ship == water)
	{
		cout << "The ship and water symbols cannot be the same, please enter another value for the ship:" << endl;
		cin >> ship;
	}

	//Debug information.
	//cout << "Player object ready for creation. \n" << name << "'s attributes:\n----------------" << endl;
	//cout << "Board dimensions: " << boardDimensions << " x " << boardDimensions << endl;
	//cout << "Water character: " << water << endl;
	//cout << "Ship characters: " << ship << endl;
	//cout << "----------------" << endl;

	//create an object with the input values and return it.
	return Player(name, boardDimensions, boardDimensions, water, ship);
}

int main()
{	
	cout << "test" << endl;
	Player ob1 = setupPlayer();

	system("Pause");

    return 0;
}

