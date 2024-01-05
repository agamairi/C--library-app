#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H

#include "Publication.h"

using namespace std;
namespace sdds {
	class Book : public Publication {
		char* m_author{};
	public: 
		Book();
		//start of the rule of 3
		Book(const Book& bookObj);
		Book& operator= (const Book& bookObj);
		virtual ~Book();
		// end of the rule of 3
		virtual char type() const;
		virtual ostream& write(ostream& ostr) const;
		virtual istream& read(istream& istr);
		virtual void set(int memberID);
		virtual operator bool() const;
	};
}
#endif // !SDDS_BOOK_H
