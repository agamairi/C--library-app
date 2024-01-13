#include <iostream>
#include "Utils.h"
#include "Lib.h"

using namespace std;

namespace sdds {
	int Int()
	{
		int val;
		cin >> val;
		while (cin.get() != '\n' || cin.fail())
		{
			if (cin.fail())
			{
				cout << "Invalid Selection, try again: ";
			}
			cin.clear();
			cin.ignore(10000, '\n');
			cin >> val;
		}
		return val;
	}

	int Range(int min, int max)
	{
		int val = Int();
		bool loopOn = true;
		if (val<min || val>max)
		{
			while (loopOn)
			{
				loopOn = false;
				cout << "Invalid Selection, try again: ";
				val = Int();
				if (val<min || val>max)
				{
					loopOn = true;
				}
			}
		}
		return val;
	}

	void copyFile(char* destination, const char* source) {
		while (*source) *destination++ = *source++;
		*destination = *source;
	}

	void betterVersionOfstrcpy(char* destination, char* source, int number){
		int i;
		for (i = 0; i < number && i < strlen(source); i++) {
			destination[i] = source[i];
		}
		destination[i] = '\0';
	}

	int strlen(char* stringForGCCstupidity) {
		int i = 0;
		while (stringForGCCstupidity[i] != '\0') {
			i++;
		}
		return i;
	}

	int constCharStrLen(const char* str)
	{
		int length = -1;
		while (str[++length]);
		return length;
	}

	void pubValidation(unsigned int& val, unsigned int min, unsigned int max, const char* userSelection){
		bool finished = false;
		while (finished != true) {
			cin >> val;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid " << userSelection << ", try again: ";
			}
			else if (val < min || val > max) {
				cout << "Invalid " << userSelection << ", try again: ";
			}
			else if(cin.get() != '\n') {
				cout << "Invalid " << userSelection << ", try again: ";
			}
			else {
				finished = true;
			}

		}
	}
}
