#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>

#include "LibApp.h"
#include "Book.h"
#include "PublicationSelector.h"
#include "Utils.h"
using namespace std;

namespace sdds {
	LibApp::LibApp(const char* filename) :m_changed(false),
		m_mainMenu("Seneca Library Application"),
		m_exitMenu("Changes have been made to the data, what would you like to do?"),
		m_publicationMenu("Choose the type of publication:") {

		// This is the main menu
		m_mainMenu << "Add New Publication";
		m_mainMenu << "Remove Publication";
		m_mainMenu << "Checkout publication from library";
		m_mainMenu << "Return publication to library";

		// This is the exit menu
		m_exitMenu << "Save changes and exit";
		m_exitMenu << "Cancel and go back to the main menu";

		//Publication menu development
		m_publicationMenu << "Book";
		m_publicationMenu << "Publication";
		strcpy(m_fileName, filename);
		load();
	}
	// Private methods
	char LibApp::typeGetter() {
		int userSelection = m_publicationMenu.run();
		char type{};
		if (userSelection == 1) {
			type = 'B';
		}
		else if (userSelection == 2) {
			type = 'P';
		}
		return type;
	}

	bool LibApp::confirm(const char* message) {
		Menu test(message);
		test << "Yes";
		return (test.run() == 1);
	}

	void LibApp::load() {
		std::cout << "Loading Data" << endl;
		ifstream loadFIle(m_fileName);
		char type{};
		int i;
		for (i = 0; loadFIle; i++) {
			loadFIle >> type;
			if (loadFIle) {
				if (type == 'P') {
					m_publications[i] = new Publication;
				}
				else if (type == 'B') {
					m_publications[i] = new Book;
				}
				if (m_publications[i]) {
					loadFIle >> *m_publications[i];
					m_pubNumber++;
				}
			}
		}
		m_libReferenceNum = m_publications[m_pubNumber - 1]->getRef();
	}

	void LibApp::save() {
		std::cout << "Saving Data" << endl;
		ofstream saveFile(m_fileName);
		for (int i = 0; i < m_pubNumber; i++) {
			if (m_publications[i]->getRef() != 0) {
				saveFile << *m_publications[i] << endl;
			}
		}
	}

	int LibApp::search(int searchType) {
		// std::cout << "Searching for publication" << endl;
		int value = 0;
		PublicationSelector pubSelObj("Select one of the following found matches:");
		char type = typeGetter();
		char title[256]{};
		std::cout << "Publication Title: ";
		cin.getline(title, 256);
		for (int i = 0; i < m_pubNumber; i++) {
			if (searchType == 1) {
				if (strstr(*m_publications[i], title) && type == m_publications[i]->type()) {
					pubSelObj << m_publications[i];
				}
			}
			else if (searchType == 2) {
				if (strstr(*m_publications[i], title) && m_publications[i]->onLoan() && type == m_publications[i]->type()) {
					pubSelObj << m_publications[i];
				}
			}
			else if (searchType == 3) {
				if (strstr(*m_publications[i], title) && !m_publications[i]->onLoan() && type == m_publications[i]->type()) {
					pubSelObj << m_publications[i];
				}
			}
		}
		if (pubSelObj) {
			pubSelObj.sort(); 
			int runobj = pubSelObj.run(); 
			if (runobj) {
				value = runobj;
				cout << *getPub(runobj) << endl;
			}
			else {
				cout << "Aborted!" << endl;
			}
		}
		else {
			cout << "No matches found!" << endl;
		}
		return value;
	}

	Publication* LibApp::getPub(int libRef) {
		int val = 0;
		for (int i = 0; i < m_pubNumber; i++) {
			if (libRef == m_publications[i]->getRef()) {
				val = i;
			}
		}
		return m_publications[val];
	}

	void LibApp::returnPub() {
		cout << "Return publication to the library" << endl;
		int userInput = search(2);
		if (userInput) {
			if (confirm("Return Publication?")) {
				int totalDaysLoan = Date() - getPub(userInput)->checkoutDate();
				if (totalDaysLoan > SDDS_MAX_LOAN_DAYS) {
					int daysLate = totalDaysLoan - SDDS_MAX_LOAN_DAYS;
					double fineAmt = 0;
					fineAmt = 0.5 * daysLate;
					cout << "Please pay $";
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << fineAmt << " penalty for being " << daysLate << " days late!" << endl;
					cout.unsetf(ios::fixed);
				}
				getPub(userInput)->set(0);
				m_changed = true;
				cout << "Publication returned" << endl;
			}
		}
	}

	void LibApp::newPublication() {
		if (m_pubNumber == SDDS_LIBRARY_CAPACITY) {
			cout << "Library is at its maximum capacity!" << endl;
			return;
		}
		else {
			cout << "Adding new publication to the library" << endl;
			char type = typeGetter();
			if (!type) {
				cout << "Aborted!" << endl;
				return;
			}
			Publication* temp = nullptr;
			if (type == 'P') {
				temp = new Publication;
			}
			else if (type == 'B') {
				temp = new Book;
			}
			temp->read(cin);
			if (cin) {
				if (confirm("Add this publication to the library?")) {
					if (temp) {
						temp->setRef(++m_libReferenceNum);
						m_publications[m_pubNumber++] = temp;
						m_changed = true;
						cout << "Publication added" << endl;
					}
					else {
						cout << "Failed to add publication!" << endl;
						delete temp;
					}
				}
				else {
					cout << "Aborted!" << endl;
					delete temp;
				}
			}
			else {
				cin.ignore(1000, '\n');
				cout << "Aborted!" << endl;
				delete temp;
			}
		}
	}

	void LibApp::removePublication() {
		cout << "Removing publication from the library" << endl;
		int userSelection = search(1);
		if (userSelection) {
			if (confirm("Remove this publication from the library?")) {
				getPub(userSelection)->setRef(0);
				m_changed = true;
				cout << "Publication removed" << endl;
			}
		}
	}

	void LibApp::checkOutPub() {
		cout << "Checkout publication from the library" << endl;
		int selection = search(3), val = 0, temp = 0;
		if (selection) {
			if (confirm("Check out publication?")) {
				unsigned int membershipNumber = 0;
				cout << "Enter Membership number: ";
				do{
					if (temp){
						cout << "Invalid membership number, try again: ";
					}
					cin >> val;
					temp = 1;
				} while (val < 9999 || val > 100000);
				getPub(selection)->set(membershipNumber);
				m_changed = true;
				cout << "Publication checked out" << endl;
			}
		}
	}

	void LibApp::run() {
		bool appTerminate = false;
		do {
			unsigned int selection = m_mainMenu.run();
			if (selection == 1) {
				newPublication();
				cout << endl;
			}
			else if (selection == 2) {
				removePublication();
				cout << endl;
			}
			else if (selection == 3) {
				checkOutPub();
				cout << endl;
			}
			else if (selection == 4) {
				returnPub();
				cout << endl;
			}
			else {
				if (m_changed) {
					unsigned int selectionB = m_exitMenu.run();
					if (selectionB == 1) {
						save();
						appTerminate = true;
						cout << endl;
					}
					else if (selectionB == 0) {
						if (confirm("This will discard all the changes are you sure?")) {
							appTerminate = true;
							cout << endl;
						}
					}
					else {
						cout << endl;
					}
				}
				else {
					appTerminate = true;
					cout << endl;
				}
			}
		} while (!appTerminate);
		cout << "-------------------------------------------" << endl 
		 << "Thanks for using Seneca Library Application" << endl;
	}

	LibApp::~LibApp() {
		for (int i = 0; i < m_pubNumber; i++) {
			delete m_publications[i];
		}
	}
}