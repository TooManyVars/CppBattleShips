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
		cout << Entity::centerText() << flush;
		printf("Input for %s cell was invalid: input must be strictly one character long.\n%sPlease re-enter:\n",cellType.c_str(), Entity::centerText().c_str()); //this currently gets output no matter what, but only for when getting input for the water cells.
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

	cout << "\n" << Entity::centerText() << "Enter your name: " << endl;
	getline(cin, name);

	while (name.length() > 15) //make sure that the player can't enter excessively long names.
	{
		cout << "\n" << Entity::centerText() << "Name cannot be more than 15 characters." << "\n" << Entity::centerText() <<"Please enter a different name:" << endl;
		getline(cin, name);
	}

	//get a value from the player which will act as the length and the width of the board.
	cout << "\n" << Entity::centerText() << "Enter a board size (value will be true for both length and width) between 5 and 15.\n" << "\n" << Entity::centerText() << "Note that board sizes above 10*10 provide more difficulty in guessing)." << endl;
	boardDimensions = Entity::getValidIntInput();

	//text formatting up until this point has been successful.

	//make sure the board dimensions are between 5*5 and 15*15.
	while (boardDimensions > 15 || boardDimensions < 5)
	{
		cout << "\n" << Entity::centerText() <<  "Board size is outside of the recommended range, please choose another set of dimensions." << endl;
		boardDimensions = Entity::getValidIntInput();
	}
	
	//Get inputs for ships and water(create validation which prevents entering 0 or more than 1 character, or entering the same symbol for water and ships).	
	
	//Clear the iostream to prevent the previous int input from interferring with the string input.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard inputs

	cout << "\n" << Entity::centerText() << "Enter the desired character to represent water cells on the board\n" << Entity::centerText()  << "(can be literally any character on the keyboard): " << endl;
	water = getValidStringInput("water");
	
	cout << "\n" << Entity::centerText() << "Enter the desired character to represent ships on the board\n" << Entity::centerText() << "(again, can be literally any character on the keyboard): " << endl;
	ship = getValidStringInput("Ship");

	while (water == ship) //loop input to change the water/ship symbols until they are no longer the same.
	{
		string option;
		cout << "\n" << Entity::centerText() << "Both the ship and water symbols are the same, which one would you like to change?\n" << Entity::centerText() << "Type water or w to change the water symbol, or ship or s to change the ship symbol." << endl;
		getline(cin, option);//get input for what to change.

		//lowercase letters and verify input.
		transform(option.begin(), option.end(), option.begin(), ::tolower);

		//loop option input of altering the water or ship symbol until it's valid.
		while (option != "water" && option != "w" && option != "s" && option != "ship") 
		{
			cout << Entity::centerText() << "Option is invalid.\n" << Entity::centerText() << "Enter either ship or (s), or water or (w)." << endl;
			getline(cin, option);
			transform(option.begin(), option.end(), option.begin(), ::tolower);
		}

		if (option == "w" || option == "water")
		{
			cout << Entity::centerText() << "Enter the desired water symbol:" << endl;
			water = getValidStringInput("water");
		}

		else if (option == "s" || option == "ship")
		{
			cout << Entity::centerText() << "Enter the desired ship symbol:" << endl;
			ship = getValidStringInput("ship");
		}
	}

	//Debug information for the player(s).
	cout << "\n" << Entity::centerText() << flush;


	//Output for the player attributes, formatted using printf and custom setw function.
	printf("\n%sPlayer object ready for creation. \n\n%s%s's attributes:\n%s----------------\n", Entity::centerText().c_str(), Entity::centerText().c_str(), name.c_str(), Entity::centerText().c_str());

	//create an object with the input values and return it.
	Player p(name, boardDimensions, boardDimensions, water, ship);
	p.outputEntityInformation();

	return p;
}

Enemy setupEnemy(Player &player) //creates and returns an enemy object, based on the information of the already existing player.
{
	string name = "[Blank]";
	string water = player.getWater();
	string ship = player.getShip();
	int boardDimensions  = player.getBoardSize();

	
	//Debug information for the enemy.
	
	////Output for the enemy attributes, formatted using printf and custom setw function.
	printf("\n%sEnemy object ready for creation.  \n\n%s%s's attributes:\n%s----------------\n\n", Entity::centerText().c_str(), Entity::centerText().c_str() , name.c_str(), Entity::centerText().c_str());
	Enemy e(name, boardDimensions, boardDimensions, water, ship);
	e.outputEntityInformation(); //output entity attributes using dedicated function.

	//create the object and return it.
	return e;
}

//A typical round in which both the enemy AI and the player try to guess the coordinates of a potential ship.
void PvERound(Player& player, Enemy& enemy, int currentRound) 
{
	cout << "\n\n"<< Entity::centerText() << "Current round: " << currentRound << "\n" << Entity::centerText() << "--------------------------------" << endl;

	//player.destroyShip(enemy.guessShip(player.getBoardSize()),enemy.getPlayerName());
	enemy.destroyShip(player.guessShip(enemy.getBoardSize()),player.getPlayerName());
	player.destroyShip(enemy.guessShip(player.getBoardSize()), enemy.getPlayerName());

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
	cout << Entity::centerText() << player.getPlayerName() << "'s score: " << player.getScore() << flush;

	//When outputting the enemy's name, displace it from the player's name rather than trying to center it, otherwise it seems somewhat offset.
	cout << Entity::setw(15) << enemy.getPlayerName() << "'s score: " << enemy.getScore() << "\n" << endl;

	//This algorithim works becaause both boards will be the same size, and will be referencing the same index at the same time(albeit on differnet boards).
	for (int x = 0; x < player.getBoard().size(); x++)
	{
		cout << Entity::centerText(); //the proportions of spacing still need work.

		//Output the cells(flushed) from row x on the player board.
		outputRow(x, player.getBoard());

		printf("|");//Flush a separator character to separate boards.

		//Flush output the cells from row x on the enemy board.
		outputRow(x, enemy.getBoard());

		//end the newly created output row off by ending the line.
		printf("\n");
	}
	system("Pause");
}




int main()
{	

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions

	MoveWindow(console, r.left, r.top, 1250, 700, TRUE); // 800 width, 100 height

	//code to setup the enemy and the board. chances are i'm going to move all of this code into a function
	Player ob1 = setupPlayer();
	//setting up an enemy board requires that there first be a player object created.
	Enemy ob2 = setupEnemy(ob1);



	string option; //The option of whether the player wants to manually place his or her ships, or have them placed randomly.
	cout << Entity::centerText() <<  "Would you like to place your own ships?\n" << Entity::centerText() <<"Note that selecting 'no' or 'n' will have the ships randomly placed for you." << endl;
	getline(std::cin, option);

	//lowercase input before verifying it.
	transform(option.begin(), option.end(), option.begin(), ::tolower);

	while (option != "n" && option != "no" && option != "y" && option != "yes")
	{
		cout << Entity::centerText() << "Choice must be either yes or no(or alternatively, y or n).\n" << Entity::centerText() << "Please re-enter your choice:" << endl;
		getline(std::cin,option);
		transform(option.begin(), option.end(), option.begin(), ::tolower);
	}


	if (option == "y" || option == "yes") //if the player chooses to place their own ships, commence the for loop for the manual placement of ships.
	{
		for (int x = 0; x < ob1.getInitialShips(); x++)
		{
			//cout << "\nShip #" << x + 1 << ":" << endl;
			cout << Entity::centerText() << flush;
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

	drawUI(ob1, ob2);

	int i = 1;

	while (ob1.shipsRemaining() > 0 && ob2.shipsRemaining() > 0)
	{
		PvERound(ob1, ob2, i);
		i++;

		drawUI(ob1, ob2);
	}


	system("pause");

    return 0;
}

