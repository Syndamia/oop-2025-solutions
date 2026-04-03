#include "User.h"
#include <iostream>

void User::copyFrom(const User& other) {
	email = other.email;
	password = other.password;
	bankCard = other.bankCard;

	libraryCount = other.libraryCount;
	libraryAlloc = other.libraryAlloc;
	library = new const Book*[libraryAlloc];
	for (unsigned i = 0; i < libraryCount; ++i)
		library[i] = other.library[i];
}

void User::free() {
	delete[] library;
}

void User::resizeLibrary() {
	libraryAlloc = libraryAlloc == 0 ? 8 : libraryAlloc * 2;
	const Book** libraryLarger = new const Book*[libraryAlloc];

	for (unsigned i = 0; i < libraryCount; ++i)
		libraryLarger[i] = library[i];

	delete[] library;
	library = libraryLarger;
}

User::User() : email(), password(), bankCard(0), library(nullptr), libraryCount(0), libraryAlloc(0)
{ }

User::~User() {
	free();
}

User::User(const User& other) {
	copyFrom(other);
}

User& User::operator=(const User& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

User::User(User&& other) {
	email = other.email;
	password = other.password;
	bankCard = other.bankCard;

	library = other.library;
	libraryCount = other.libraryCount;
	libraryAlloc = other.libraryAlloc;

	other.email.Clear();
	other.password.Clear();
	other.bankCard = 0;

	other.library = nullptr;
	other.libraryCount = other.libraryAlloc = 0;
}

User& User::operator=(User&& other) {
	if (this != &other) {
		free();

		email = other.email;
		password = other.password;
		bankCard = other.bankCard;

		library = other.library;
		libraryCount = other.libraryCount;
		libraryAlloc = other.libraryAlloc;

		other.email.Clear();
		other.password.Clear();
		other.bankCard = 0;

		other.library = nullptr;
		other.libraryCount = other.libraryAlloc = 0;
	}
	return *this;
}

void User::SetEmail(const String& newEmail) {
	email = newEmail;
}

const String& User::GetEmail() const {
	return email;
}

void User::SetPassword(const String& newPassword) {
	password = newPassword;
}

bool User::Login(const String& email, const String& password) {
	return this->email.EqualTo(email) && this->password.EqualTo(password);
}

void User::AddBookToLibrary(const Book* book) {
	if (libraryCount >= libraryAlloc)
		resizeLibrary();
	library[libraryCount++] = book;
}

void User::ListLibrary() {
	for (unsigned i = 0; i < libraryCount; ++i) {
		std::cout << '[' << i << "] ";
		library[i]->PrintBookInfo();
	}
}

const Book* User::GetBook(unsigned index) const {
	return library[index];
}

void User::SetBankCard(unsigned newBankCard) {
	bankCard = newBankCard;
}

unsigned User::GetBankCard() const {
	return bankCard;
}
