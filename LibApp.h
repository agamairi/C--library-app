#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H

#include "Menu.h"
#include "Publication.h"
#include "Lib.h"

namespace sdds {
    class LibApp {
        // flag to keep a track of changes made to application data. Initial value: false
        bool m_changed;
        // Main Menu of the application
        Menu m_mainMenu;
        // Ask if the user wants to save the data or nah
        Menu m_exitMenu;
        char m_fileName[256]{};
        Publication* m_publications[SDDS_LIBRARY_CAPACITY]{};
        int m_pubNumber = 0;
        int m_libReferenceNum = 0;
        // Creating a menuu for the publication
        Menu m_publicationMenu;
        // Private Methods
             // Instantiates a Menu with a message
        bool confirm(const char* confirmString);
        void load();  // prints: "Loading Data"<NEWLINE>
        void save();  // prints: "Saving Data"<NEWLINE>
        int search(int searchType = 1);  // prints: "Searching for publication"<NEWLINE>
        void returnPub();  /*  Calls the search() method.
                               prints "Returning publication"<NEWLINE>
                               prints "Publication returned"<NEWLINE>
                               sets m_changed to true;
                           */
                           // Will ask for permssion before printing and adding the data
        void newPublication();
        // Will ask for persmission before removing the data
        void removePublication();
        // will call the search method then calls the confirm method before printing 
        void checkOutPub();

        Publication* getPub(int libRef);
        char typeGetter();
    public:
        LibApp(const char* nameOfTheFile);
        void run();
        ~LibApp();
    };
}
#endif // !SDDS_LIBAPP_H


