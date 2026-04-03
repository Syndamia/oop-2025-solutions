#ifndef _USER
#define _USER

#include "String.h"
#include "Book.h"

class User {
	String email;
	String password;
	unsigned bankCard;

	// Масив от указатели към книги
	const Book** library;
	unsigned libraryCount;
	unsigned libraryAlloc;

	void copyFrom(const User& other);
	void free();

	void resizeLibrary();

public:
	User();
	~User();
	User(const User& other);
	User& operator=(const User& other);
	User(User&& other);
	User& operator=(User&& other);

	void SetEmail(const String& newEmail);
	const String& GetEmail() const;

	void SetPassword(const String& newPassword);

	bool Login(const String& email, const String& password);

	void AddBookToLibrary(const Book* book);
	void ListLibrary();
	const Book* GetBook(unsigned index) const;

	void SetBankCard(unsigned newBankCard);
	unsigned GetBankCard() const;
};

#endif /* _USER */
