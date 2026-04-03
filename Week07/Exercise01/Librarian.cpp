#include "Librarian.h"

Librarian::Librarian(unsigned librarianNumber) {
	this->librarianNumber = librarianNumber;
	this->password = "password";
}

Librarian::Librarian() : librarianNumber(0), password()
{ }

unsigned Librarian::GetLibrarianNumber() const {
	return librarianNumber;
}

void Librarian::SetPassword(const String& newPassword) {
	this->password = newPassword;
}

bool Librarian::Login(unsigned librarianNumber, const String& password) {
	return this->librarianNumber == librarianNumber && this->password.EqualTo(password);
}
