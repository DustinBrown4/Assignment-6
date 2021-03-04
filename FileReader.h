#pragma once
/*File Reader Class
* Authors: Ben"Jamin" VanderHart, Dustin "D-dawg" Brown
*	Class: CIS 227
*	Date: Due 2/10/2021
*	Purpose:
*		To allow users of the app to read a txt file for a selection of words.
*/


#include <string>
#include <fstream> //for file
#include <iostream>
#include <stdlib.h> //for random
#include <vector>
#include <string>

#ifndef FILEREADER_H_
#define FILEREADER_H_

using namespace std;

class FileReader
{
private:
	//none

public:
	//function to select word
	string sendWord();
	//displays highscores
	void highScores();
	//writes new scores
	void updateScore(string player, int score);
};



#endif
