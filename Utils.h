/***********************************************************************
// OOP244 Utils Module
// File  utils.h
// Version
// Author
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
/////////////////////////////////////////////////////////////////
***********************************************************************/
#ifndef SDDS_UTILS_H
#define SDDS_UTILS_H

#include <iostream>
namespace sdds {
	int Int();
	int Range(int min, int max);
	void pubValidation(unsigned int& value1, unsigned int min, unsigned int max, const char* userSelection);
	void betterVersionOfstrcpy(char* destination, char* source, int number);
	int strlen(char* stringForGCCstupidity);
	void copyFile(char* destination, const char* source);

	int constCharStrLen(const char* str);
}
#endif // !