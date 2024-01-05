#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>

#include "Publication.h"
#include "Lib.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	Publication::Publication() : m_date() {}

	// implementaion of the rule of 3 begins here
	Publication::Publication(const Publication& publication) {
		operator=(publication);
	}

	Publication& Publication::operator= (const Publication& publicationObj) {
		if (this != &publicationObj) {
			delete[] m_title;
			m_title = nullptr;
			if (publicationObj) {
				m_title = new char[strlen(publicationObj.m_title) + 1];
				strcpy(m_title, publicationObj.m_title);
				strcpy(m_shelfId, publicationObj.m_shelfId);
			}
			m_membership = publicationObj.m_membership;
			m_libRef = publicationObj.m_libRef;
			m_date = publicationObj.m_date;
		}

		return *this;
	}

	Publication:: ~Publication() {
		delete[] m_title;
	}
	// implementation of the rule of 3 ends here


	void Publication::set(int member_id) {
		if (member_id > 9999 && member_id < 100000) {
			m_membership = member_id;
		}
		else {
			m_membership = 0;
		}
	}

	void Publication::setRef(int value) {
		m_libRef = value;
	}

	void Publication::resetDate() {
		Date temp = Date();
		m_date = temp;
	}

	char Publication::type() const {
		return'P';
	}

	bool Publication::onLoan() const {
		return m_membership > 0;
	}

	Date Publication::checkoutDate() const {
		return m_date;
	}

	bool Publication::operator==(const char* title) const {
		return strstr(m_title, title);
	}

	Publication::operator const char* () const {
		return m_title;
	}

	int Publication::getRef() const {
		return m_libRef;
	}

	bool Publication::conIO(ios& ioObj) const {
		return &ioObj == &cin || &ioObj == &cout;
	}

	ostream& Publication::write(ostream& ostr) const {
		char titleButTemp[SDDS_TITLE_WIDTH + 1];
		/*int i;

		for (i = 0; i < SDDS_TITLE_WIDTH && i < strlen(m_title); i++) {
			titleButTemp[i] = m_title[i];
		}
		titleButTemp[i] = '\0';
		*/
		betterVersionOfstrcpy(titleButTemp, m_title, SDDS_TITLE_WIDTH);

		// It worked for ms3 but does not work for ms4. IDK why
		//strcpy(titleButTemp, m_title);

		if (conIO(ostr) == true) {
			ostr << "| ";
			ostr.width(4);
			ostr << m_shelfId << " | ";
			ostr.width(SDDS_TITLE_WIDTH);
			ostr.fill('.');
			ostr.setf(ios::left);
			ostr << titleButTemp << " | ";
			ostr.unsetf(ios::left);
			ostr.width(5);
			ostr.fill(' ');
			if (onLoan()) {
				ostr << m_membership << " | ";
			}
			else {
				ostr << " N/A " << " | ";
			}
			ostr << m_date << " |";
		}
		else {
			ostr << type() << '\t'
				<< m_libRef << '\t'
				<< m_shelfId << '\t'
				<< m_title << '\t'
				<< m_membership << '\t'
				<< m_date;
		}
		return ostr;
	}

	istream& Publication::read(istream& istr) {
		// Creating temp objects to store the data for the time being
		char tempTitle[256]{};
		char tempShelfID[5]{};
		int tempMembershiop = 0;
		int tempLibRef = -1;
		Date tempDate;

		// Freeing up the memory to prevent a memory leak 
		delete[] m_title;

		// reassigning the values
		m_shelfId[0] = 0;
		m_libRef = 0;
		m_membership = 0;
		resetDate();

		if (conIO(istr) == true) {
			cout << "Shelf No: ";
			istr.get(tempShelfID, SDDS_SHELF_ID_LEN + 1);
			// peek allows to check the file for the desired character. Newline in this case
			if (istr.peek() != '\n') {
				istr.setstate(ios::failbit);
				istr.ignore(1000, '\n');
			}
			istr.get();
			cout << "Title: ";
			istr.get(tempTitle, 256);
			istr.get();
			cout << "Date: ";
			if (istr.fail() != true) tempDate.read(istr);
		}
		else {
			istr >> tempLibRef;
			istr.get();
			istr.get(tempShelfID, 5, '\t');
			istr.get();
			istr.get(tempTitle, 256, '\t');
			istr.get();
			istr >> tempMembershiop;
			istr.get();
			tempDate.read(istr);
		}

		if (tempDate == false) {
			istr.setstate(ios::failbit);
		}

		if (istr) {
			m_title = new char[strlen(tempTitle) + 1];
			strcpy(m_title, tempTitle);
			strcpy(m_shelfId, tempShelfID);
			m_membership = tempMembershiop;
			m_libRef = tempLibRef;
			m_date = tempDate;
		}

		return istr;
	}

	Publication::operator bool() const {
		return m_title && m_title[0] && m_shelfId && m_shelfId[0];
	}


}
