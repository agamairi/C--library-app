#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>

#define MAX_MENU_ITMES 20

namespace sdds
{
	class MenuItem
	{
		// Everything is private in this class
		char* mItems;
		friend class Menu;
		MenuItem(const char* itemName = nullptr);
		MenuItem(const MenuItem& menuObj) = delete;
		MenuItem& operator=(const MenuItem& menuObj) = delete;
		// Deallocates everything
		~MenuItem();
		// if item is not empty, return true. Else, return false
		operator bool() const;
		// Should return the address of the content cstring
		operator const char* () const;
		// Print nothing if MenuItem is empty 
		std::ostream& display(std::ostream& ostr) const;
	};
	class Menu
	{
		char* mTitle;
		MenuItem* menuItems[MAX_MENU_ITMES]{ nullptr };
		int mCount;
		Menu(const Menu& menuObj) = delete;
		Menu& operator=(const Menu& menuObj) = delete;
	public:
		Menu(const char* = nullptr);
		~Menu();
		// Displays the title of the menu on ostream if its not empty
		char* menuTitle() const;
		// Dispplays the entire menu on ostream
		void menuDisplay() const;
		// Makes sure user inputs correct value
		unsigned int run() const;
		// Does exactly what run() function does
		unsigned int operator~()const;


		Menu& operator<<(const char* mehuItemContent);
		operator int() const;
		operator unsigned int() const;
		operator bool() const;
		const char* operator[](int index)const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Menu& menuObj);
}

#endif