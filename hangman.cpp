/*********Assignment 3**********
*	Authors: Ben"Jamin" VanderHart, Dustin "D-dawg" Brown
*	Class: CIS 227
*	Date: Due 2/10/2021
*	Purpose:
*		User can make an array, then choose to load the array or a txt file for a game of hangman
*/



// imported libs
#include <iostream>
#include <array>
#include <string>
#include "WordArray.h"
#include "FileReader.h"
#include <vector>
#include "ErrorCatcher.h"
#include <stdlib.h> //for random

using namespace std;


// declared functions - some overloaded
void mainMenu();


// global objs and vars
WordArray obj_WordArray;
int const MAX_CHAR_LIMIT = 21;



// main function w/ 1 argument to display on main menu page - one call to mainmenu for a clean main look.
int main(int argc, char* argv[]) {

	if (argc == 1) {
		cout << "This program is a product of group 2.  Date: 02/01/2021" << endl;
	}
	cout << "\n\n\t\t\t\tASSIGNMENT 2\n\tBrought to you by Group 2: Dustin 'D-dawg' B. & Ben'jamin' V.\n";
	mainMenu();
}


// main - where local vars are declared
void mainMenu() {
	int choice, wordCount, displayChoice;
	string input, plural;
	string arrWords[12];
	bool mainMenuInput, userInput, menuLoop, arrayEmpty;

	choice = -1;
	displayChoice = -1;
	input = "";
	wordCount = 0;
	mainMenuInput = false;
	userInput = false;
	arrayEmpty = true;
	menuLoop = true;
	ErrorCatcher errorCheck;




	//Begin Word Array program
	cout << "\n\t\t\tWelcome to the Word Array Program";
	while (menuLoop) {
		cout << "\n\tPlease choose option by entering the coordinating number\n";
		do {
			cout << "\n1 - Add to the Word Array\n2 - View the Word Array\n3 - Remove an entry from Word Array\n0 - Load Hangman program\n";
			cout << "\nEnter number: ";
			cin >> choice;
			errorCheck.intMenuInputCheck(choice, mainMenuInput);  // calls error handler
		} while (!mainMenuInput);

		do {
			switch (choice) {

			case 1:
				if (!arrayEmpty) {
					cout << "\nCannot add additional words to array, contents already full\n" << endl;
				}
				else {
					while (wordCount < 11) {
						errorCheck.wordCounterTracker(userInput, wordCount); // counts wordcount
						if (wordCount == 11) {
							plural = "word";
						}
						else {
							plural = "words";
						}
						cout << "\nAdd 12 words to the Word Array (" << MAX_CHAR_LIMIT << " char limit) " << "\t\t" << (12 - wordCount) <<
							" " << plural << " remaining\nWord: ";
						cin >> input;
						errorCheck.userInputCheck(input, userInput); // error handling
						if (userInput) {
							arrWords[wordCount] = input; // puts words into array
						}
					}
					arrayEmpty = false;
				}
				break;

			case 2:
				if (arrayEmpty) {
					cout << "\nArray is empty, use option 1 to fill array\n";
					userInput = true;
					break;
				}
				else {
					cout << "\nViewing Word Array Contents\n";
					do {
						cout << "\nPlease choose from available options\n1 - View all contents of Word Array\n";
						cout << "2 - Display a single word by entering a number 1 thru 12\n3 - Display range of words " <<
							"by entering beginning and ending numbers\n0 - Go back to previous menu\n" << endl;
						cout << "Enter number: ";
						cin >> choice;
						errorCheck.intMenuInputCheck(choice, mainMenuInput); // error handling
					} while (!mainMenuInput);
					if (choice == 1) {
						obj_WordArray.viewArray(arrWords, 12);  // calls object array to view its contents
					}
					else if (choice == 2) {
						bool choiceCheck = true;
						do {
							cout << "\nEnter number to display coordinating word\n";
							cin >> choice;
							errorCheck.intMenuInputCheck(choice, mainMenuInput, choiceCheck);  //error handling
							obj_WordArray.viewArray(choice, arrWords, 12);
						} while (!mainMenuInput);
					}
					else if (choice == 3) {
						cout << "\nOption not available at this time\n";  // for future work
						wordCount = -1;
					}
					else {
						userInput = true;
						break;
					}
				}
				break;

			case 3:
				cout << "\nRemoving entry from array\n";
				cout << "Option not available at this time\n"; // for future work				
				userInput = true;
				menuLoop = true;
				wordCount = -1;
				break;

			case 0:
				cout << "\nLoading Hangman program . . .\n";
				userInput = true;
				menuLoop = false;
				break;

			default:
				userInput = true;   // this may be used for future work
				menuLoop = false;
				break;
			}
		} while (!userInput);
	}
	
	system("CLS"); //clears screen
	//Begin Hangman program
	//possibly add more file choices for more difficulty options/add difficulty to menu -- future
	menuLoop = true;
	string wordToGuess;
	FileReader wordsFromFile;
	cout << "\n\n\t\t\tLet's play Hangman!" << endl;
	while (menuLoop) {
		cout << "\n\tPlease choose option by entering the coordinating number\n";
		do {
			cout << "\n1 - Guess a random word from your Word Array\n2 - Guess a random word from a file\n0 - Exit program\n";
			cout << "\nEnter number: ";
			cin >> choice;
			errorCheck.intMenuInputCheck(choice, mainMenuInput);  // calls error handler
		} while (!mainMenuInput);
		do {
			switch (choice) {
			case 1:
				wordToGuess = arrWords[rand() % 12];
				menuLoop = false;
				break;
			case 2:

				wordToGuess = wordsFromFile.sendWord();
				menuLoop = false;
				break;

			case 0:
				cout << "\nExiting hangman program . . .\n";
				userInput = true;
				menuLoop = false;
				break;
			default:
				userInput = true;   // this may be used for future work
				menuLoop = true;
				break;
			}
		} while (!userInput);

	}
	system("CLS"); //clears screen for loops
	//loop section variables for guessing
	FileReader highscore;
	bool wordFound = false;
	string userFoundCharacters;
	string wrongCharacters;
	int i;
	int position;
	char c;
	int pointsSpent = 0;

	//size string and make ? place holder
	userFoundCharacters.resize(wordToGuess.size());
	for (i = 0; i <= wordToGuess.size(); ++i) {
		userFoundCharacters.assign(i, '?');
	}
	cout << "\n\t\t\tYour secret word has " << wordToGuess.size() << " letters.\n\n" << endl;
	
	//begin loop for guessing
	//hint counter before loop
	int hintCount = 0;
	string userGuess;
	do {
		
		cout << "\n\t\tfound: " << userFoundCharacters << endl;
		cout << "\t\twrong: " << wrongCharacters << endl;
		cout << "\t\thints used: " << hintCount << endl;
		cout << "\t\tpoints lost: " << pointsSpent << "\n" << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "\t\tType \"Hint\" for a hint, \"Scores\" for Top Scores" << endl;
		cout << "--------------------------------------------------------------------------------" << endl;
		cout << "\n\nEnter a letter to guess: " << endl;
		cin >> userGuess;

		//convert letter guess to lower
		for (i = 0; i < userGuess.size(); ++i) {
			c = userGuess[i];
			c = tolower(c);
			userGuess[i] = c;
		}
		//branch for guess of entire word
		if (userGuess.size() > 1) {
			if (userGuess == wordToGuess) {
				cout << "\n\t\t\tCorrect! Your secret word was: " << wordToGuess << endl;
				wordFound = true;
			}
			//hint option
			else if (userGuess == "hint") {
				srand(time(NULL));
				hintCount += 1;
				
				if (hintCount < 3) {
					userGuess = wordToGuess.at(rand() % (wordToGuess.size()));
				}
				else if (hintCount >= 3) {
					cout << "\n\n*****Additional hints will take away 10 points each and are not always unique.*****\n\nDo you wish to continue?(Y/N)" << endl;
					cin >> c;
					c = tolower(c);
					if (c == 'y') {
						pointsSpent -= 10;
						userGuess = wordToGuess.at(rand() % (wordToGuess.size()));
					}	
				}
			}
			//highscore list display
			else if (userGuess == "scores") {
				highscore.highScores();		
			}
			else {
				cout << "\n\t\t\tIncorrect! Try again...\n" << endl;
			}
			system("CLS");
		}

		//branch for single letter guess
		if (userGuess.size() == 1) {

			//searches string for userGuess
			size_t found = wordToGuess.find(userGuess);
			if (found == string::npos) {
				wrongCharacters = wrongCharacters.append(userGuess);
			}

			//places first occurence of userGuess if found
			if (found != string::npos) {
				position = wordToGuess.find(userGuess);
				userFoundCharacters[position] = userGuess[0];

				//checks for repeats, places them in correct order
				for (i = 1; i < wordToGuess.size(); ++i) {
					string repeatCheck = wordToGuess.substr(i, wordToGuess.size());
					found = repeatCheck.find(userGuess);
					if (found != string::npos) {
						position = repeatCheck.find(userGuess);
						userFoundCharacters[position + i] = userGuess[0];
					}
				}
			}
			if (userFoundCharacters == wordToGuess) {
				cout << "\nYou've guessed all the correct characters!\nYour secret word was: " << wordToGuess << endl;
				wordFound = true;
			}
			system("CLS");
		}
	} while (!wordFound);

	//Section is for demo use of using players name and score to send to 
	//scores list. Needs changing
	cout << "You've finished the game!\n\nEnter name and score:\nname:" << endl;
	string name;
	cin >> name;
	cout << "score" << endl;
	int myscore;
	cin >> myscore;

	//call highscore list and appends player's info
	FileReader updater;
	updater.updateScore(name, myscore);
	//displays new list
	highscore.highScores();
	cout << "\n\nThank you for using our program!\n\n";
}


/*
Assignment Details
•	Use at least on class
•	Read a list of 12 words into an array
•	Prompt the user for which word in the array to display
•	Use a command line argument to present the user with information about your program.
•	Exit the program on user request
*/