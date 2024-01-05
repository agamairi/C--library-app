#ifndef SDDS_STREAMABLE_H
#define SDDS_STREAMABLE_H

#include <iostream>


using namespace std;
namespace sdds {
	class Streamable {
	public:
		virtual ostream& write(ostream& ostr) const = 0;
		virtual istream& read(istream& istr) = 0;
		virtual bool conIO(ios& ios) const = 0;
		virtual operator bool() const = 0;
		virtual ~Streamable();
	};

	ostream& operator<<(ostream& ostr, const Streamable& streamObj);
	istream& operator>>(istream& istr, Streamable& streamObj);
}

#endif // !SDDS_STREAMABLE_H
