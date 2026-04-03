#ifndef _LIBRARIAN
#define _LIBRARIAN

#include "String.h"

class Librarian {
	unsigned librarianNumber;
	String password;

public:
	Librarian(unsigned librarianNumber);
	// Ако направим поне един конструктор, то конструктора по подразбиране
	// спира да се създава автоматично
	Librarian();

	unsigned GetLibrarianNumber() const;

	void SetPassword(const String& newPassword);

	bool Login(unsigned librarianNumber, const String& password);
};

#endif /* _LIBRARIAN */
