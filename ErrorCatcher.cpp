#include "ErrorCatcher.h"
#include <string>
#include <iostream>



using namespace std;
bool ErrorCatcher::intMenuInputCheck(int choice, bool& intMenuInput) {

	int check = choice;
	if (cin.fail()) {
		cin.clear();
		string ignoreError;
		getline(cin, ignoreError);
	}
	else if (check != 0 && check != 1 && check != 2 && check != 3) {
		intMenuInput = false;		// redundant, keeping this here anyway for looks
	}
	else {
		intMenuInput = true;
		return intMenuInput;
	}
	cout << "\n\tInvalid input\nPlease choose only available numbers\n";
	intMenuInput = false;
	return intMenuInput;

}
bool ErrorCatcher::intMenuInputCheck(int choice, bool& intMenuInput, bool& choiceCheck) {
	{
		int check = choice;
		if (cin.fail()) {
			cin.clear();
			string ignoreError;
			getline(cin, ignoreError);
		}
		else if (check < 0 || check > 12) {
			intMenuInput = false;		// redundant, keeping this here anyway for looks
		}
		else {
			intMenuInput = true;
			return intMenuInput;
		}
		cout << "\n\tInvalid input\nPlease choose only available numbers\n";
		intMenuInput = false;
		return intMenuInput;
	}
}
bool ErrorCatcher::userInputCheck(string& input, bool& userInput) {
	string wordError;
	int const MAX_CHAR_LIMIT = 21;
	int wordLength;
	int limitExceeded;

	getline(cin, wordError);
	wordLength = input.length();
	limitExceeded = (wordLength - MAX_CHAR_LIMIT);

	for (int i = 0; i < wordError.length(); i++) {
		if (isspace(wordError.at(i))) {
			cout << "\nOne word at a time! Please re-enter word." << endl;
			userInput = false;
			return userInput;
		}
	}

	if (input.length() > MAX_CHAR_LIMIT) {
		cout << "\nYou exceeded the 21 maximum character limit by " << limitExceeded << "!" << endl;
	}
	else {
		userInput = true;
		return userInput;
	}
	userInput = false;
	return userInput;
}
int ErrorCatcher::wordCounterTracker(bool& userInput, int& wordCount) {
	if (userInput) wordCount++; return wordCount;
}