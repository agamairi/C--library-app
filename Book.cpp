#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

#include "Book.h"
#include "Lib.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	Book::Book() {}

	// Implementation of the rule of 3
	Book::Book(const Book& bookObj): Publication(bookObj) {
		delete[] m_author;
		m_author = nullptr;
		if (bookObj.m_author && bookObj.m_author[0]) {
			m_author = new char[strlen(bookObj.m_author) + 1];
			strcpy(m_author, bookObj.m_author);
		}
	}

	Book& Book::operator=(const Book& bookObj) {
		if (this != &bookObj) {
			Publication::operator=(bookObj);
			delete[] m_author;
			m_author = nullptr;
			if (bookObj.m_author && bookObj.m_author[0]) {
				m_author = new char[strlen(bookObj.m_author) + 1];
				strcpy(m_author, bookObj.m_author);
			}
		}
		return *this;
	}

	Book::~Book() {
		delete[] m_author;
		m_author = nullptr;
	}
	// end of the implementation

	char Book::type() const {
		return 'B';
	}

	ostream& Book::write(ostream& ostr) const {
		Publication::write(ostr);

		char authorTemp[SDDS_AUTHOR_WIDTH + 1]{};

		// using strcpy is not working idk why
		//strcpy(authorTemp, m_author);

		//int i;
		//for (i = 0; i < SDDS_AUTHOR_WIDTH && i < strlen(m_author); i++) {
		//	authorTemp[i] = m_author[i];
		//}
		//authorTemp[i] = '\0';

		betterVersionOfstrcpy(authorTemp, m_author, SDDS_AUTHOR_WIDTH);

		if (conIO(ostr)) {
			ostr << ' ';
			ostr.setf(ios::left);
			ostr.width(SDDS_AUTHOR_WIDTH);
			ostr << authorTemp << " |";
			ostr.unsetf(ios::left);
		}
		else {
			ostr << '\t' << m_author;
		}

		return ostr;
	}

	istream& Book::read(istream& istr) {
		char authorTemp[256];

		Publication::read(istr);

		delete[] m_author;
		m_author = nullptr;

		if (conIO(istr) == true) {
			istr.get();
			cout << "Author: ";
			istr.get(authorTemp, 256);
		}
		else {
			istr.get();
			istr.get(authorTemp, 256);
		}

		if (istr) {
			m_author = new char[strlen(authorTemp) + 1];
			strcpy(m_author, authorTemp);
		}
		return istr;
	}

	void Book::set(int memberID) {
		Publication::set(memberID);
		resetDate();
	}

	Book::operator bool() const {
		return Publication::operator bool() && m_author && m_author[0];
	}

}