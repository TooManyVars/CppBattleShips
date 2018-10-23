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
		- Make sure the length is exactly one character long
		- If this condition is true, then return the now valid string.
	*/

	string s;
	cin >> s;

	while (s.length() > 1 || s.length() < 1)
	{
		cout << "Input for " << cellType << " was invalid : input for " << cellType << " cell must be at least 1 character long but no longer.\nPlease re - enter: " << endl;
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

	cout << "\nEnter your name: " << endl;
	cin >> name;

	while (name.length() > 15) //make sure that the player can't enter excessively long names.
	{
		cout << "\nName cannot be more than 15 characters.\nPlease choose a different name." << endl;
		cin >> name;
	}

	//get a value from the player which will act as the length and the width of the board.
	cout << "\nEnter a board size (value will be true for both length and width) between 5 and 15\nnote that board sizes above 10*10 provide more difficulty in guessing)." << endl;
	boardDimensions = Entity::getValidIntInput();

	//make sure the board dimensions are between 5*5 and 15*15.
	while (boardDimensions > 15 || boardDimensions < 5)
	{
		cout << "\nBoard size is outside of the recommended range, please choose another set of dimensions." << endl;
		boardDimensions = Entity::getValidIntInput();
	}
	

	//get inputs for ships and water(create validation which prevents entering 0 or more than 1 character, or entering the same symbol for water and ships).	
	
	cout << "\nEnter the desired character to represent shipless cells on the bord(can be literally any character on the keyboard): " << endl;
	water = getValidStringInput("water");

	
	cout << "\nEnter the desired character to represent ships on the bord(again, can be literally any character on the keyboard) : " << endl;
	ship = getValidStringInput("Ship");

	while (water == ship) //loop input to change the water/ship symbols until they are no longer the same.
	{
		string option;
		cout << "\nBoth the ship and water symbols are the same, which one would you like to change?\nType water or w to change the water symbol, or ship or s to change the ship symbol." << endl;
		cin >> option; //get input for what to change.

		//lowercase letters and verify input.
		transform(option.begin(), option.end(), option.begin(), ::tolower);

		//loop option input of altering the water or ship symbol until it's valid.
		while (option != "water" && option != "w" && option != "s" && option != "ship") 
		{
			cout << "\nOption is invalid.\nEnter either ship or (s), or water or (w)." << endl;
			cin >> option;
			transform(option.begin(), option.end(), option.begin(), ::tolower);
		}

		if (option == "w" || option == "water")
		{
			cout << "\nEnter the desired water symbol:" << endl;
			water = getValidStringInput("water");
		}

		else if (option == "s" || option == "ship")
		{
			cout << "\nEnter the desired ship symbol:" << endl;
			ship = getValidStringInput("ship");
		}
	}


	//Debug information.
	cout << "\nPlayer object ready for creation. \n" << name << "'s attributes:\n----------------" << endl;
	cout << "Board dimensions: " << boardDimensions << " x " << boardDimensions << endl;
	cout << "Water character: " << water << endl;
	cout << "Ship characters: " << ship << endl;
	cout << "----------------" << endl;

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

