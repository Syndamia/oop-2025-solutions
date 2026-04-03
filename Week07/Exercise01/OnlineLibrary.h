#ifndef _ONLINE_LIBRARY
#define _ONLINE_LIBRARY

#include "Book.h"
#include "LibraryBanking.h"
#include "Transaction.h"
#include "User.h"
#include "Librarian.h"

class OnlineLibrary {
	Book* books;
	unsigned booksCount;
	unsigned booksAlloc;

	User* users;
	unsigned usersCount;
	unsigned usersAlloc;

	Librarian* librarians;
	unsigned librariansCount;
	unsigned librariansAlloc;

	// В методи на OnlineLibrary, тази структура се казва "TransactionConnection"
	// Извън методи на OnlineLibrary, тази структура се казва "OnlineLibrary::TransactionConnection"
	struct TransactionConnection {
		const User* user;
		const Book* book;
		const Transaction* transaction;
	};
	TransactionConnection* connections;
	unsigned connectionsCount;
	unsigned connectionsAlloc;

	void free();
	void copyFrom(const OnlineLibrary& other);

	void resizeBooks();
	void resizeUsers();
	void resizeLibrarians();
	void resizeConnections();

public:
	OnlineLibrary();
	~OnlineLibrary();
	OnlineLibrary(const OnlineLibrary& other);
	OnlineLibrary& operator=(const OnlineLibrary& other);
	OnlineLibrary(OnlineLibrary&& other);
	OnlineLibrary& operator=(OnlineLibrary&& other);

	void RegisterUser(const User& user);
	User* LoginUser(const String& email, const String& password);

	void RegisterLibrarian(const Librarian& librarian);
	Librarian* LoginLibrarian(unsigned librarianNumber, const String& password);

	void ListBooks() const;
	Book* GetBook(unsigned index);
	void AddBook(const Book& book);
	void PurchaseBook(const Book& book, const User& user, LibraryBanking& banking);

	void ListTransactions(const User& user) const;
	void ExportTransactions(const User& user, const String& fileName) const;
};

#endif /* _ONLINE_LIBRARY */
