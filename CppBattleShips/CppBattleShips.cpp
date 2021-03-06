// CppBattleShips.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std;


//Return a random line text from a file which is determined by the textType passed as a parameter.
//for example, typing "name" will generate a random line from the "name.txt" file.
string generateTextFromFile(string textType)
{
	//The file that we will be doing read and write operations on in order to retrieve a line of text.
	string fileOperand;
	//The vector of items we will have to reference in case the file we have tried to open is empty or non exsistent.
	vector<string>defaultVector;

	//check what type of text we want, and open the corresponding file. after that, file our default vectors with default values.
	if (textType == "name")
	{
		fileOperand = "Names.txt";
		//All of our unfunny names.
		defaultVector = 
		{ 
			"Robb","Chris the photographer","Mo",
			"Katarina","Miss fortune", "Kumiko the non-exsistent fox-cat",
			"Blueface", "T.O.", "The entire human endocrine system"
			"Jaeger blitz counter", "Zofia", "Ela",
			"Upset offset","Dead meme","Deadlocs",
			"Lancey", "Skep", "Discord manager in toronto",
			"r/woosh", "HentaiHaven","[CBA to name]"
			"999", "Missingno", "pump"
			"Dave", "Propane", "IQ",
			"Politically correct person(who is superior)", "Facist goverment", "Elon musk",
			"Don cannon", "The beat", "Tay keith", 
			"Offwhitevlone1", "Herbo", "Dkjstra"
			,"Vonn nuemann", "Elite four member", "Facist dictator",
			"The FBI", "Visual studio dark theme", "Kirito(oh, you're screwed now)",
			"Eliante the jewler", "Satan himself", "A rolls royce",
			"Volt", "Excalibur", "Mag",
			"Edward Elric", "Greg heffley", "Joe goldberg", "Beck"
			"Peach sallinger", "Grifeth(who did nothing wrong)", "Virgil abloh",
			"'Enemy'", "Seven deadly sins"
		};
	}
	else if (textType == "taunt")
	{
		fileOperand = "Taunts.txt";
		defaultVector = 
		{
			"You're not very good at this, are you?", "Oh, i get it, you were just warming up. understandable.", "That was a really bad guess.",
			"This is not your round. Enough said", "You can't even fein it off as lag - this game doesn't even require internet.", "Better like next turn.",
			"Well, it's only one round, i guess: you should be fine.", "L.", "Let's bring this back - no one likes losers.", "This match might soon just look like bow-wow's career.",
			"I guess you could say that your heart 'sank'... get it? cos, you know, ship? ahh whatever, you're losing anyways, who cares.", "Go get yourself an L next time.", "I have no words(for once)",
			"Geez, coming up with ways to taunt the player is tiring. i give up this time", "[Some smart ass comment about how much you suck at battleships]", "...",
		};

	}
	
	else if (textType == "win")
	{
		//We're not naming it Win.txt to avoid the possible wrath of the windows operating system(unlikely, but a good precaution).
		fileOperand = "WinnerText.txt";
		defaultVector = 
		{
			"A hard earned victory.", "Surely you could have won that quicker, no?","That it? i could win twice as fast."
			,"Well, i can't fault you too much, considering you own. Eventually.", "I'm running out of text to congratulate you. so, congrats, i guess.", 
			"Gonna be honest here, i didn't think you'd even win, but looks like you did. Nice work.", "Epic victory royale, or something along those lines.",
			"You won; no one cares, though."
		};
	}

	else if (textType == "loss")
	{
		fileOperand = "LossText.txt";
		defaultVector = 
		{
			"Let's be honest here, you were pretty bad anyways.", "Maybe next time you'll win. or maybe the time after that.", "Don't go blaming lag, now: an L's an L.",
			"I don't even have any sympathy, if i'm truly honest. but why should i? i'm a machine.", "HAHAHAHAHAHAHAHA you're bad at the game lol", " F ", "Don't look at me like that. you're the one who lost.",
			" L ", "Guess who won? not you.", " 'If you lose you're bad lmao' - Sun Tzu", "Ooof", "You lost. enough said."
		};
	}


	ofstream toFile;
	ifstream fromFile;

	//Firstly, try to open a text file as if it exists. 
	fromFile.open(fileOperand);

	//If the file fails to open(meaning that it doesn't exist) or is empty:
	if (fromFile.fail() || fromFile.peek() == std::ifstream::traits_type::eof())
	{
		fromFile.close(); //close the file(not sure if that even matters but it's good practice)

		//Create a new file called names.txt
		toFile.open(fileOperand);

		//Once you have created it, add the default lines from the string vector into the text file.
		//Iterate through the default vector in order to add each entry, of course.
		for (string line : defaultVector)
		{
			toFile << line << endl;
		}

		//Close after writing to the text file.
		toFile.close();

		//Re-open the file to read from it
		fromFile.open(fileOperand);

	}

	//Store the list of names from the file in a vector so that you can pick one at random. 1 line = 1 name.
	vector<string>textlines;
	string container;

	//Getline essentially takes whatever value is in the first parameter and copies it into the second parameter.
	//Begins to return null whenever the end of a file is reached, meaning that we can use getline's return parameter to control the loop.
	while (std::getline(fromFile, container))
	{
		//Put the text file line(Aka a name) into the names vector.
		textlines.push_back(container);
	}

	//now that you've got the names loaded onto memory, close the text file.
	fromFile.close();

	//return a random index from our names vector to use serve as a name.
	return textlines[Entity::getRN(0, textlines.size() - 1)];
}

string generateRandomName()
{
	ofstream toFile;
	ifstream fromFile;

	//Firstly, try to open a text file as if it exists. 
	fromFile.open("Names.txt");

	//If the file fails to open(meaning that it doesn't exist) or is empty
	if (fromFile.fail() || fromFile.peek() == std::ifstream::traits_type::eof())
	{
		fromFile.close(); //close the file(not sure if that even matters but it's good practice)

		//Set the default(and unfunny)names that will be generated.
		vector<string>defaultNames = { 
			"Robb","Chris the photographer","Mo",
			"Katarina","Miss fortune", "Kumiko the non-exsistent fox-cat",
			"Blueface", "T.O.", "The entire human endocrine system",
			"Jaeger blitz counter", "Zofia", "Ela",
			"Upset offset","Dead meme","Deadlocs",
			"Lancey", "Skep", "Discord manager",
			"r/woosh", "HentaiHaven","[CBA to name]"
			"999", "Missingno", "pump"
			"Dave", "Propane", "IQ",
			"Politically correct person(who is superior)", "Facist goverment", "Elon musk",
			"Don cannon", "The beat", "Tay keith", 
			"Offwhitevlone1", "Herbo", "Dkjstra"
			,"Vonn nuemann", "Elite four member", "Facist dictator",
			"The FBI", "Visual studio dark theme", "Kirito(oh, you're screwed now)"
		};

		//Create a new file called names.txt(or open it if there is one existing already)
		toFile.open("Names.txt");

		//Once you have created it, add default the names from the string vector into the text file.
		//iterate through the names vector in order to add them, of course.
		for (string name : defaultNames)
		{
			toFile << name << endl;
		}

		//Close after writing to the text file.
		toFile.close();

		//Re-open the file to read from it
		fromFile.open("Names.txt");

	}

	//Store the list of names from the file in a vector so that you can pick one at random. 1 line = 1 name.
	vector<string>names;
	string container;

	//Getline essentially takes whatever value is in the first parameter and copies it into the second parameter.
	//Begins to return null whenever the end of a file is reached, meaning that we can use getline's return parameter to control the loop.
	while (std::getline(fromFile, container))
	{
		//Put the text file line(Aka a name) into the names vector.
		names.push_back(container);
	}

	//now that you've got the names loaded onto memory, close the text file.
	fromFile.close();

	//return a random index from our names vector to use serve as a name.
	return names[Entity::getRN(0, names.size() - 1)];

}

//Provides momentary pause in the action for the player. pressing any key will continue the game.
void pauseText()
{
	cout << "\n" << Entity::centerText();
	cout << "Press any key to continue..." << endl;

	Entity::centerCursor();
	int ch = _getch(); //get a key and do nothing with it.
}

//Check if the string is empty or not.
bool isEmptyString(string input)
{
	//Iterate through the string.
	//If one of the indexes of the string contains a non blank character, return false.
	//otherwise return true.
	for (char &c: input)
	{
		if (c != ' ')
		{
			return false;
		}

		return true;
	}
}

//Used to get input foe water/ships.
//With parameter 'cellType' we can pass either 'ship' or 'water' into the error message output.
string getValidBoardInput(string cellType)
{
	/*
		Algorithim:
		- Get the string as input
		- Make sure the length is exactly one character long
		- If this condition is true, then return the now valid string.
	*/

	string s;
	Entity::centerCursor();
	getline(cin, s);
	
	while (s.length() > 1 || s.length() < 1)
	{
		cout << Entity::centerText() << flush;
		printf("\nInput for %s cell was invalid: input must be strictly one character long.\n%sEnter a CHARACTER(as in, a single valid key on the keyboard, dumbass):\n",cellType.c_str(), Entity::centerText().c_str()); //this currently gets output no matter what, but only for when getting input for the water cells.
		Entity::centerCursor();
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

	Entity::setTextColor(Entity::lightGreen);
	cout << "\n" << Entity::centerText() << "Enter your name(It will never be as cool as mine, but that's ok): " << endl;
	Entity::centerCursor();
	getline(cin, name);

	//Make sure that the player can't enter excessively long names.
	while (name.length() > 15)
	{
		cout << "\n" << Entity::centerText() << "Name cannot be more than 15 characters, because quite frankly working with a name that long is hassle." << "\n" << Entity::centerText() <<"Enter a shorter name, perhaps?:" << endl;
		Entity::centerCursor();
		getline(cin, name);
	}

	//Also make sure that the player cannot enter an empty string for his name.
	while(isEmptyString(name))
	{
		cout << "\n" << Entity::centerText() << "Name cannot be nothing. you stupid???" << "\n" << Entity::centerText() << "Now re-enter your name, before i lose my patience with you:" << endl;
		Entity::centerCursor();
		getline(cin, name);
	}

	

	//Get a value from the player which will act as the length and the width of the board.
	cout << "\n" << Entity::centerText() << "Enter a board size (value will be true for both length and width) between 5 and 9.\n" << "\n" << Entity::centerText() << "Note that board sizes above 8*8 provide more difficulty in guessing)" << endl;
	boardDimensions = Entity::getValidIntInput();

	//text formatting up until this point has been successful.

	//make sure the board dimensions are between 5*5 and 15*15.
	while (boardDimensions > 9 || boardDimensions < 5)
	{
		cout << "\n" << Entity::centerText() <<  "Board size is outside of the recommended range 5*5 - 9*9, please choose another set of dimensions." << endl;
		boardDimensions = Entity::getValidIntInput();
	}
	
	//Get inputs for ships and water(create validation which prevents entering 0 or more than 1 character, or entering the same symbol for water and ships).	
	
	//Clear the iostream to prevent the previous int input from interferring with the string input.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard inputs

	//Get input for the water cells.
	cout << "\n" << Entity::centerText() << "Enter the desired character to represent water cells on the board\n" << Entity::centerText()  << "(can be literally any character on the keyboard): " << endl;
	water = getValidBoardInput("water");
	
	//Get input for the ship cells.
	cout << "\n" << Entity::centerText() << "Enter the desired character to represent ships on the board\n" << Entity::centerText() << "(again, can be literally any character on the keyboard): " << endl;
	ship = getValidBoardInput("Ship");

	while (water == ship) //loop input to change the water/ship symbols until they are no longer the same.
	{
		string option;
		cout << "\n" << Entity::centerText() << "Now, looks like both the ship and water symbols are the same, so which one would you like to change?\n" << Entity::centerText() << "Type water or w to change the water symbol, or ship or s to change the ship symbol." << endl;
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
			water = getValidBoardInput("water");
		}

		else if (option == "s" || option == "ship")
		{
			cout << Entity::centerText() << "Enter the desired ship symbol:" << endl;
			ship = getValidBoardInput("ship");
		}
	}

	//Debug information for the player(s).
	cout << "\n" << Entity::centerText() << flush;

	Entity::setTextColor(Entity::white);

	//Output for the player attributes, formatted using printf and custom setw function.
	printf("\n%s%s's attributes:\n%s----------------\n",Entity::centerText().c_str(), name.c_str(), Entity::centerText().c_str());

	//create an object with the input values and return it.
	Player p(name, boardDimensions, boardDimensions, water, ship);
	p.outputEntityInformation();

	return p;
}

Enemy setupEnemy(Player &player) //creates and returns an enemy object, based on the information of the already existing player.
{
	string name = generateRandomName();
	string water = player.getWater();
	string ship = player.getShip();
	int boardDimensions  = player.getBoardSize();

	//Debug information for the enemy.
	
	////Output for the enemy attributes, formatted using printf and custom setw function.
	printf("\n%s%s's attributes:\n%s----------------\n",Entity::centerText().c_str() , name.c_str(), Entity::centerText().c_str());
	Enemy e(name, boardDimensions, boardDimensions, water, ship);
	e.outputEntityInformation(); //output entity attributes using dedicated function.

	//create the object and return it.
	return e;
}

//A typical round in which both the enemy AI and the player try to guess the coordinates of a potential ship.
void PvERound(Player& player, Enemy& enemy, int currentRound) 
{
	cout << "\n\n"<< Entity::centerText() << "Current round: " << currentRound << "\n" << Entity::centerText() << "--------------------------------" << endl;

	Entity::setTextColor(Entity::lightGreen);
	if (enemy.destroyedShip(player.guessShip(enemy.getBoardSize()), player.getPlayerName()))
	{
		player.incrementScore();
	}

	Entity::setTextColor(Entity::lightMagenta);
	if (player.destroyedShip(enemy.guessShip(player.getBoardSize()), enemy.getPlayerName()))
	{
		enemy.incrementScore();
	}

	Entity::setTextColor(Entity::white);
	pauseText();
}


//Outputs a given row of a board without ending the line.
void outputBoardRow(int index, vector<vector<string> >board, bool outputRowToppings = true)
{
	for (int i = 0; i < board[index].size(); i++)
	{
		cout << board[index][i] << flush;
		
		if (outputRowToppings)
		{
			cout << "|" << flush;
		}
		else
		{
			cout << " " << flush;
		}
	}
}

//Neatly and simoultaneously outputs any two rows of two boards, given their indexes. 
//Default boolean "addRowNumber" adds a number to the end of each row.
void output2BoardRows(int index, int index2, vector<vector<string> >playerBoard, vector<vector<string> >enemyBoard, bool addRowNumber = true, bool outputRowToppings = true)
{
	//If the parameter addRowNumber is true, add a number at the start of the row for the player/enemy. (create spacing of 7 characters instead of 8 to avoid disaligning the board rows.
	//Center the text and output the player row.

	//Set the color of the player board rows to be greem first.
	Entity::setTextColor(Entity::lightGreen);
	cout << Entity::centerText() << flush;

	if (addRowNumber)
	{
		cout << Entity::setw(14) << flush;
		cout << index - 1 << flush;
	}

	else
	{
		cout << Entity::setw(15) << flush;
	}

	if (outputRowToppings)
	{
		cout << "|" << flush;
	}

	else
	{
		cout << " " << flush;
	}

	outputBoardRow(index, playerBoard, outputRowToppings);

	Entity::setTextColor(Entity::lightMagenta);
	//Output the enemy board row.
	//Output the enemy board row.
	if (addRowNumber)
	{
		cout << Entity::setw(14) << flush;
		cout << index - 1 << flush;
	}

	else
	{
		cout << Entity::setw(15) << flush;
	}

	if (outputRowToppings)
	{
		cout << "|" << flush;
	}
	else
	{
		cout << " " << flush;
	}

	outputBoardRow(index2, enemyBoard, outputRowToppings);
	cout << endl;

	Entity::setTextColor(Entity::white);
}

void outputColumnNumbers(int n) //output the column nunbers along the to, the input being n.
{
	for (int x = 0; x <= n; x++)
	{
		cout << Entity::setw(1) << x << Entity::setw(1);
	}
}


//draws out the user interface(currently in shambles).
void drawUI(Player& player, Enemy& enemy)
{
	system("CLS");

	//Store our player and enemy boards for easy reference.
	vector<vector<string> >playerBoard = player.getBoard();
	vector<vector<string> >enemyBoard = enemy.getDetectionBoard();

	//These vectors will be placed onto the board vector.
	//A vector to store our column numbers.
	vector<string>columnNumbers;
	//A vector to store our "row toppings" (a row that goes across the top of our board, mainly for aesthetic reasons).
	vector<string>rowToppings;
	

	//Add row toppings to the rowToppings vector by putting n amount of underscores, equal to the number of columns(which is essentially the size of the vectors within the main vector).
	for (int i = 0; i < playerBoard[0].size(); i++)
	{
		rowToppings.push_back("_");
	}

	//Create the column numbers by pushing back i into the vector and and incrementing it until it reaches the maximum amount of columns.
	for (int i = 0; i < playerBoard[0].size(); i++)
	{
		columnNumbers.push_back(to_string(i+1));
	}
	
	//Note that we can use the same row toppings and column numbers for both boards as they are the same size.
	
	//Add these vectors to the front of the displayBoard vector, the column numbers coming first and the row toppings coming second.
	//When it comes to the position of the board to insert at, the parameters dictate(there is no int parameter for a position, only an iterator) that it must be relative to the beginning or the end.
	playerBoard.insert(playerBoard.begin(), rowToppings);
	playerBoard.insert(playerBoard.begin() + 1, columnNumbers);

	//Insert these into the second display board too.
	enemyBoard.insert(enemyBoard.begin(), rowToppings);
	enemyBoard.insert(enemyBoard.begin() + 1, columnNumbers);


	//Output the first four rows of the player and enemy board manually, so that we don't put the row number on their sides.
	//Also, the "Column toppings"(as we'll call them, they're simply the top of the board) act as a roof to the board and as a result don't need dividers. 
	//The final booleanparameter, outputRowToppings, is there so that we can opt out of outputting the dividers.
	output2BoardRows(0, 0, playerBoard, enemyBoard, false, false);
	output2BoardRows(1, 1, playerBoard, enemyBoard, false);

	//Iterate through each row of both boards and output them. no nested loop needed because both boards are of the same size.
	for (int i = 2; i < playerBoard.size(); i++)
	{
		output2BoardRows(i , i, playerBoard, enemyBoard);
	}

	//Output a key to tell the player which symbols on the board is a ship/cell
	printf("\n\n%sShip cells: %s\n", Entity::centerText().c_str(), player.getShip().c_str());
	printf("%sWater cells: %s\n", Entity::centerText().c_str(), player.getWater().c_str());

	Entity::setTextColor(Entity::lightGreen);
	printf("\n%s%s's ships remaining: %s", Entity::centerText().c_str(), player.getPlayerName().c_str() ,to_string(player.shipsRemaining()).c_str());
	Entity::setTextColor(Entity::lightMagenta);
	printf("\n%s%s's ships remaining: %s\n", Entity::centerText().c_str(), enemy.getPlayerName().c_str(), to_string(enemy.shipsRemaining()).c_str());
	Entity::setTextColor(Entity::white);

	pauseText();
}


void mainGame()
{
	//code to setup the enemy and the board. chances are i'm going to move all of this code into a function.
	Player player = setupPlayer();
	//setting up an enemy board requires that there first be a player object created.
	Enemy enemy = setupEnemy(player);

	Entity::setTextColor(Entity::lightGreen);
	string option; //The option of whether the player wants to manually place his or her ships, or have them placed randomly.
	cout << "\n" << Entity::centerText() << "Would you like to place your own ships?\n" << Entity::centerText() << "Note that selecting 'no' or 'n' will have the ships randomly placed for you." << endl;
	Entity::centerCursor();
	getline(std::cin, option);

	//lowercase input before verifying it.
	transform(option.begin(), option.end(), option.begin(), ::tolower);

	while (option != "n" && option != "no" && option != "y" && option != "yes")
	{
		cout << Entity::centerText() << "Choice must be either yes or no(or alternatively, y or n).\n" << Entity::centerText() << "Please re-enter your choice:" << endl;
		Entity::centerCursor();
		getline(std::cin, option);
		transform(option.begin(), option.end(), option.begin(), ::tolower);
	}


	if (option == "y" || option == "yes") //if the player chooses to place their own ships, commence the for loop for the manual placement of ships.
	{
		for (int x = 0; x < player.getInitialShips(); x++)
		{
			cout << Entity::centerText() << flush;
			printf("\n%sShip #%i:", Entity::centerText().c_str(), x + 1);
			cout << endl;
			player.placeShip();
			player.drawBoard(player.getBoard());
		}
	}

	//Create a method to place ships on the board for each entity object.
	else if (option == "n" || option == "no") //if they choose not to, on the other hand, commence the loop to automatically and randomly place ships on the board.
	{
		player.autoPlaceShips();
	}

	Entity::setTextColor(Entity::white);

	enemy.autoPlaceShips();

	drawUI(player, enemy);

	int i = 1;

	while (player.shipsRemaining() > 0 && enemy.shipsRemaining() > 0)
	{
		PvERound(player, enemy, i);
		i++;

		drawUI(player, enemy);
	}

	cout << "\n" << Entity::centerText() << "Game over." << endl;

	if (player.shipsRemaining() <= 0)
	{
		Entity::setTextColor(Entity::lightMagenta);
		cout << "\n" << Entity::centerText() << enemy.getPlayerName() << " wins!" << endl;
	}

	else if (enemy.shipsRemaining() <= 0)
	{
		Entity::setTextColor(Entity::lightGreen);
		cout << "\n" << Entity::centerText() << player.getPlayerName() << " wins!" << endl;
	}

	Entity::setTextColor(Entity::white);
}

int main()
{	
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 1250, 700, TRUE); // 800 width, 100 height

	mainGame();
	//pauseText();

	//system("pause");

    return 0;
}

