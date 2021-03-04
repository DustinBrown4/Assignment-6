//
//Assignment 2
//By Ben"jamin" V & Dustin "D-dawg" B
//Date: 02/01/2021
#include "WordArray.h"

#include <array>
#include <string>
#include<iostream>
using namespace std;


// class functions - default function

void WordArray::viewArray(string array[], int size) {
	int wordNum = 1;
	for (int i = 0; i < size; i++) {
		cout << "\nWord # " << wordNum + i << ": " << array[i] << endl;
	}
}

// overloaded function
void WordArray::viewArray(int& choice, string array[], int size) {
	for (int i = 0; i < size; i++) {
		if (choice == i) {
			cout << "\nThis is word # " << i << ": " << array[i] << endl;
			break;
		}
	}
}


//random choice of array
//WordArray::