// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <algorithm>//we're using this to downcase text.
#include <conio.h> //we may need this if we want to color our text later on.
#include <limits> //use this header to clear int input streams.
#include <ctype.h>//This may or may not cause problems within the code later on, so i'm simply trying this so i can implement my own custom system("pause") function.
#include <fstream> //used to generate a random name for the enemy.

#include <Windows.h>//used to center text on screen by getting the dimensions on the console.
#undef max //negates problems relating to the max() macro when windows.h is included.

#include "Entity.h"
#include "Enemy.h"
#include "Player.h"



// TODO: reference additional headers your program requires here
