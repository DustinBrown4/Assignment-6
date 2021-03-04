#pragma once

#ifndef ERRORCATCHER_H
#define ERRORCATCHER_H
#include <string>
using namespace std;

class ErrorCatcher
{
private:
	//none
public:
	bool intMenuInputCheck(int choice, bool& intMenuInput);
	bool intMenuInputCheck(int choice, bool& intMenuInput, bool& choiceCheck);
	bool userInputCheck(string& input, bool& userInput);
	int wordCounterTracker(bool& userInput, int& wordCount);


};

#endif;