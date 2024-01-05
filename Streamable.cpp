#include <iostream>

#include "Streamable.h"

using namespace std;

namespace sdds {
	Streamable::~Streamable() {

	}

	ostream& operator<<(ostream& ostr, const Streamable& streamObj) {
		if (streamObj) {
			streamObj.write(ostr);
		}
		return ostr;
	}

	istream& operator>>(istream& istr, Streamable& streamObj) {
		streamObj.read(istr);
		return istr;
	}
}