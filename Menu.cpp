#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <iomanip>

#include "Menu.h"
#include "Utils.h"



using namespace std;
namespace sdds
{
	MenuItem::MenuItem(const char* itemName)
	{
		mItems = nullptr;
		if (itemName && itemName[0])
		{
			mItems = new char[constCharStrLen(itemName) + 1];
			strcpy(mItems, itemName);
		}
	}


	MenuItem::~MenuItem()
	{
		delete[] mItems;
	}

	MenuItem::operator bool() const
	{
		return mItems != nullptr;
	}

	MenuItem::operator const char* ()const
	{
		return mItems;
	}

	std::ostream& MenuItem::display(std::ostream& ostr)const
	{
		if (mItems[0] != '\0' && mItems != nullptr)
		{
			ostr << mItems;
		}
		return ostr;
	}

	// Implementation for the Menu class
	Menu::Menu(const char* menutitle)
	{
		// Initialize them safely
		mTitle = nullptr;
		mCount = 0;

		if (menutitle[0] != '\0' && menutitle != nullptr)
		{
			mTitle = new char[constCharStrLen(menutitle) + 1];
			strcpy(mTitle, menutitle);
		}
	}

	Menu::~Menu()
	{
		delete[] mTitle;
		mTitle = nullptr;
		for (int i = 0; i < mCount; i++)
		{
			delete menuItems[i];
			menuItems[i] = nullptr;
		}
	}
	char* Menu::menuTitle() const
	{
		char* temp = nullptr;
		if (mTitle != nullptr && mTitle[0] != '\0')
		{
			temp = mTitle;
		}
		return temp;
	}

	void Menu::menuDisplay() const
	{
		if (menuTitle())
		{
			cout << menuTitle() << endl;
		}
		for (int i = 0; i < mCount; i++)
		{
			cout.setf(ios::right);
			cout.width(2);
			cout << i + 1 << "- " << menuItems[i]->mItems << endl;
		}
		cout << " 0- Exit" << endl;
		cout << "> ";
	}

	unsigned int Menu::run() const
	{
		menuDisplay();
		return Range(0, mCount);
	}

	unsigned int Menu::operator~() const
	{
		return run();
	}

	Menu& Menu::operator<<(const char* menuItemContent)
	{
		if (mCount < MAX_MENU_ITMES)
		{
			menuItems[mCount] = new MenuItem(menuItemContent);
			mCount++;
		}
		return *this;
	}

	Menu::operator int() const
	{
		return mCount;
	}

	Menu::operator unsigned int() const
	{
		return mCount;
	}

	Menu::operator bool() const
	{
		return mCount > 0;
	}

	const char* Menu::operator[](int index) const
	{
		char* temp = nullptr;
		index = index % mCount;
		if (index >= 0)
		{
			temp = menuItems[index]->mItems;
		}
		return temp;
	}

	std::ostream& operator <<(std::ostream& ostr, const Menu& menuObj)
	{
		if (menuObj.menuTitle())
		{
			ostr << menuObj.menuTitle();
		}
		return ostr;
	}
}