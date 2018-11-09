// CppBattleShips.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;


//used to get input foe water/ships.
//With parameter 'cellType' we can pass either 'ship' or 'water' into the error message output.
string getValidStringInput(string cellType) //i was trying to get the printf function to work here, 26/19/18.
{
	
	/*
		Algorithim:
		- Get the string as input
		- Make sure the length is exactly one character long
		- If this condition is true, then return the now valid string.
	*/

	string s;
	getline(cin, s);

	while (s.length() > 1 || s.length() < 1)
	{
		printf("\nInput for %s cell was invalid: input must be strictly one character long.\nPlease re-enter:\n",cellType.c_str()); //this currently gets output no matter what, but only for when getting input for the water cells.
		getline(cin, s);
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
	getline(cin, name);

	while (name.length() > 15) //make sure that the player can't enter excessively long names.
	{
		cout << "\nName cannot be more than 15 characters.\n\nPlease enter a different name:" << endl;
		getline(cin, name);
	}

	//get a value from the player which will act as the length and the width of the board.
	cout << "\nEnter a board size (value will be true for both length and width) between 5 and 15.\n\nNote that board sizes above 10*10 provide more difficulty in guessing)." << endl;
	boardDimensions = Entity::getValidIntInput();

	//make sure the board dimensions are between 5*5 and 15*15.
	while (boardDimensions > 15 || boardDimensions < 5)
	{
		cout << "\nBoard size is outside of the recommended range, please choose another set of dimensions." << endl;
		boardDimensions = Entity::getValidIntInput();
	}
	
	//get inputs for ships and water(create validation which prevents entering 0 or more than 1 character, or entering the same symbol for water and ships).	
	
	cout << "\nEnter the desired character to represent water cells on the bord(can be literally any character on the keyboard): " << endl;
	water = getValidStringInput("water");

	
	cout << "\nEnter the desired character to represent ships on the bord(again, can be literally any character on the keyboard): " << endl;
	ship = getValidStringInput("Ship");

	while (water == ship) //loop input to change the water/ship symbols until they are no longer the same.
	{
		string option;
		cout << "\nBoth the ship and water symbols are the same, which one would you like to change?\nType water or w to change the water symbol, or ship or s to change the ship symbol." << endl;
		getline(cin, option);//get input for what to change.

		//lowercase letters and verify input.
		transform(option.begin(), option.end(), option.begin(), ::tolower);

		//loop option input of altering the water or ship symbol until it's valid.
		while (option != "water" && option != "w" && option != "s" && option != "ship") 
		{
			cout << "\nOption is invalid.\nEnter either ship or (s), or water or (w)." << endl;
			getline(cin, option);
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

	//Debug information for the player(s).
	printf("\nPlayer object ready for creation. \n\n%s's attributes:\n----------------\n", name.c_str());
	printf("Board dimensions: %i x %i\n", boardDimensions, boardDimensions);
	printf("Water character: %s\n", water.c_str());
	printf("Ship characters: %s\n", ship.c_str());
	cout << "----------------" << endl;

	//create an object with the input values and return it.
	return Player(name, boardDimensions, boardDimensions, water, ship);
}

Enemy setupEnemy(Player &player) //creates and returns an enemy object, based on the information of the already existing player.
{
	string name = "[Blank]";
	string water = player.getWater();
	string ship = player.getShip();
	int boardDimensions  = player.getBoardSize();

	//Debug information for the enemy.
	printf("\nEnemy object ready for creation. \n\n%s's attributes:\n----------------\n", name.c_str());
	printf("Board dimensions: %i x %i\n", boardDimensions, boardDimensions);
	printf("Water character: %s\n", water.c_str());
	printf("Ship characters: %s\n", ship.c_str());
	cout << "----------------" << endl;

	//create the object and return it.
	return Enemy(name, boardDimensions, boardDimensions, water, ship);
}

//A typical round in which both the enemy AI and the player try to guess the coordinates of a potential ship.
void PvERound(Player& player, Enemy& enemy, int currentRound) 
{
	cout << "Current round: " << currentRound << "\n--------------------------------" << endl;

	player.destroyShip(enemy.guessShip(player.getBoardSize()),enemy.getPlayerName());
	enemy.destroyShip(player.guessShip(enemy.getBoardSize()),player.getPlayerName());

	system("pause");
}


//Outputs a given row of a board without ending the line.
void outputRow(int index, vector<vector<string> >board)
{
	//iterates through the row at position x on the board and outputs each cell.
	for (int x = 0; x < board[index].size(); x++)
	{
		//use printf for consistency.
		printf("%s", (Entity::setw(1) + board[index][x] + Entity::setw(1)).c_str());
	}
}


//draws out the user interface(currently in shambles).
void drawUI(Player& player, Enemy& enemy)
{
	system("CLS");

	//spacing above the UI.
	printf("\n");
	printf("\n");
	printf("\n");


	//output the player/enemy's name and score.
	//Here, it's simpler to use "cout" instead of printf.
	cout <<  Entity::setw(Entity::defaultLeftPadding) << player.getPlayerName() << "'s score: " << player.getScore() << flush;
	cout <<  Entity::setw(Entity::defaultPadding) << enemy.getPlayerName() << "'s score: " << enemy.getScore() << "\n" << endl;

	//This algorithim works becaause both boards will be the same size, and will be referencing the same index at the same time(albeit on differnet boards).
	for (int x = 0; x < player.getBoard().size(); x++)
	{
		cout << Entity::setw(Entity::defaultLeftPadding); //the proportions of spacing still need work.

		//Output the cells(flushed) from row x on the player board.
		outputRow(x, player.getBoard());

		printf("|");//Flush a separator character to separate boards.

		//Flush output the cells from row x on the enemy board.
		outputRow(x, enemy.getBoard());

		//end the newly created output row off by ending the line.
		printf("\n");
	}
}

int main()
{	
	//code to setup the enemy and the board. chances are i'm going to move all of this code into a function
	Player ob1 = setupPlayer();
	//setting up an enemy board requires that there first be a player object created.
	Enemy ob2 = setupEnemy(ob1);



	string option; //The option of whether the player wants to manually place his or her ships, or have them placed randomly.
	cout << Entity::setw(Entity::defaultLeftPadding - 32) <<  "Would you like to place your own ships? note that selecting 'no' or 'n' will have the ships randomly placed for you." << endl;
	getline(std::cin, option);

	//lowercase input before verifying it.
	transform(option.begin(), option.end(), option.begin(), ::tolower);

	while (option != "n" && option != "no" && option != "y" && option != "yes")
	{
		cout << Entity::setw(Entity::defaultLeftPadding)  << "Choice must be either yes or no(or alternatively, y or n).\n" << Entity::setw(Entity::defaultLeftPadding) << "Please re-enter your choice:" << endl;
		getline(std::cin,option);
		transform(option.begin(), option.end(), option.begin(), ::tolower);
	}


	if (option == "y" || option == "yes") //if the player chooses to place their own ships, commence the for loop for the manual placement of ships.
	{
		for (int x = 0; x < ob1.getInitialShips(); x++)
		{
			//cout << "\nShip #" << x + 1 << ":" << endl;
			cout << Entity::setw(Entity::defaultLeftPadding) << flush;
			printf("\nShip #%i:", x + 1);
			cout << endl;
			ob1.placeShip();
		}
	}

	else if (option == "n" || option == "no") //if they choose not to, on the other hand, commence the loop to automatically and randomly place ships on the board.
	{
		for (int x = 0; x < ob1.getInitialShips(); x++)
		{
			ob1.autoPlaceShip();
		}
	}



	//ob1.drawBoard();

	for (int i = 0; i < ob2.getInitialShips(); i++)
	{
		ob2.autoPlaceShip();
	}

	//cout << "\n--------------------------------" << endl;
	//ob2.drawBoard();

	//int i = 1;

	//while (ob1.shipsRemaining() > 0 && ob2.shipsRemaining() > 0)
	//{
	//	PvERound(ob1, ob2, i);
	//	i++;
	//}

	drawUI(ob1,ob2);

	//cout << "test" << endl;
	system("Pause");

    return 0;
}

