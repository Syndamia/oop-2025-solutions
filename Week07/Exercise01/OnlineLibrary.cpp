#include "OnlineLibrary.h"
#include <iostream>

void OnlineLibrary::free() {
	delete[] books;
	delete[] users;
	delete[] librarians;
	delete[] connections;
}

void OnlineLibrary::copyFrom(const OnlineLibrary& other) {
	booksCount = other.booksCount;
	booksAlloc = other.booksAlloc;
	books = new Book[booksAlloc];
	for (unsigned i = 0; i < booksCount; ++i)
		books[i] = other.books[i];

	usersCount = other.usersCount;
	usersAlloc = other.usersAlloc;
	users = new User[usersAlloc];
	for (unsigned i = 0; i < usersCount; ++i)
		users[i] = other.users[i];

	librariansCount = other.librariansCount;
	librariansAlloc = other.librariansAlloc;
	librarians = new Librarian[librariansAlloc];
	for (unsigned i = 0; i < librariansCount; ++i)
		librarians[i] = other.librarians[i];

	connectionsCount = other.connectionsCount;
	connectionsAlloc = other.connectionsAlloc;
	connections = new TransactionConnection[connectionsAlloc];
	for (unsigned i = 0; i < connectionsCount; ++i)
		connections[i] = other.connections[i];
}

void OnlineLibrary::resizeBooks() {
	booksAlloc = booksAlloc == 0 ? 8 : booksAlloc * 2;
	Book* booksLarger = new Book[booksAlloc];

	for (unsigned i = 0; i < booksCount; ++i)
		booksLarger[i] = books[i];

	delete[] books;
	books = booksLarger;
}

void OnlineLibrary::resizeUsers() {
	usersAlloc = usersAlloc == 0 ? 8 : usersAlloc * 2;
	User* usersLarger = new User[usersAlloc];

	for (unsigned i = 0; i < usersCount; ++i)
		usersLarger[i] = users[i];

	delete[] users;
	users = usersLarger;
}

void OnlineLibrary::resizeLibrarians() {
	librariansAlloc = librariansAlloc == 0 ? 8 : librariansAlloc * 2;
	Librarian* librariansLarger = new Librarian[librariansAlloc];

	for (unsigned i = 0; i < librariansCount; ++i)
		librariansLarger[i] = librarians[i];

	delete[] librarians;
	librarians = librariansLarger;
}

void OnlineLibrary::resizeConnections() {
	connectionsAlloc = connectionsAlloc == 0 ? 8 : connectionsAlloc * 2;
	TransactionConnection* connectionsLarger = new TransactionConnection[connectionsAlloc];

	for (unsigned i = 0; i < connectionsCount; ++i)
		connectionsLarger[i] = connections[i];

	delete[] connections;
	connections = connectionsLarger;
}

OnlineLibrary::OnlineLibrary() {
	books = nullptr;
	booksCount = booksAlloc = 0;
	users = nullptr;
	usersCount = usersAlloc = 0;
	librarians = nullptr;
	librariansCount = librariansAlloc = 0;
	connections = nullptr;
	connectionsCount = connectionsAlloc = 0;
}

OnlineLibrary::~OnlineLibrary() {
	free();
}

OnlineLibrary::OnlineLibrary(const OnlineLibrary& other) {
	copyFrom(other);
}

OnlineLibrary& OnlineLibrary::operator=(const OnlineLibrary& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

OnlineLibrary::OnlineLibrary(OnlineLibrary&& other) {
	books = other.books;
	booksCount = other.booksCount;
	booksAlloc = other.booksAlloc;

	users = other.users;
	usersCount = other.usersCount;
	usersAlloc = other.usersAlloc;

	librarians = other.librarians;
	librariansCount = other.librariansCount;
	librariansAlloc = other.librariansAlloc;

	connections = other.connections;
	connectionsCount = other.connectionsCount;
	connectionsAlloc = other.connectionsAlloc;

	other.books = nullptr;
	other.booksCount = other.booksAlloc = 0;

	other.users = nullptr;
	other.usersCount = other.usersAlloc = 0;

	other.librarians = nullptr;
	other.librariansCount = other.librariansAlloc = 0;

	other.connections = nullptr;
	other.connectionsCount = other.connectionsAlloc = 0;
}

OnlineLibrary& OnlineLibrary::operator=(OnlineLibrary&& other) {
	if (this != &other) {
		free();

		books = other.books;
		booksCount = other.booksCount;
		booksAlloc = other.booksAlloc;

		users = other.users;
		usersCount = other.usersCount;
		usersAlloc = other.usersAlloc;

		librarians = other.librarians;
		librariansCount = other.librariansCount;
		librariansAlloc = other.librariansAlloc;

		connections = other.connections;
		connectionsCount = other.connectionsCount;
		connectionsAlloc = other.connectionsAlloc;

		other.books = nullptr;
		other.booksCount = other.booksAlloc = 0;

		other.users = nullptr;
		other.usersCount = other.usersAlloc = 0;

		other.librarians = nullptr;
		other.librariansCount = other.librariansAlloc = 0;

		other.connections = nullptr;
		other.connectionsCount = other.connectionsAlloc = 0;
	}
	return *this;
}

void OnlineLibrary::RegisterUser(const User& user) {
	if (usersCount >= usersAlloc)
		resizeUsers();
	users[usersCount++] = user;
}

User* OnlineLibrary::LoginUser(const String& email, const String& password) {
	for (unsigned i = 0; i < usersCount; ++i) {
		if (users[i].Login(email, password))
			// "users + i" е същото като "&users[i]"
			return users + i;
	}
	return nullptr;
}

void OnlineLibrary::RegisterLibrarian(const Librarian& librarian) {
	if (librariansCount >= librariansAlloc)
		resizeLibrarians();
	librarians[librariansCount++] = librarian;
}

Librarian* OnlineLibrary::LoginLibrarian(unsigned librarianNumber, const String& password) {
	for (unsigned i = 0; i < librariansCount; ++i) {
		if (librarians[i].Login(librarianNumber, password))
			// "librarians + i" е същото като "&librarians[i]"
			return librarians + i;
	}
	return nullptr;
}

void OnlineLibrary::ListBooks() const {
	for (unsigned i = 0; i < booksCount; ++i) {
		if (books[i].GetAvailableForPurchase()) {
			std::cout << '[' << i << "] ";
			books[i].PrintBookInfo();
		}
	}
}

Book* OnlineLibrary::GetBook(unsigned index) {
	if (index >= booksCount)
		return nullptr;
	// "books + index" е същото като "&books[index]"
	return books + index;
}

void OnlineLibrary::AddBook(const Book& book) {
	if (booksCount >= booksAlloc)
		resizeBooks();
	books[booksCount++] = book;
}

void OnlineLibrary::PurchaseBook(const Book& book, const User& user, LibraryBanking& banking) {
	if (connectionsCount >= connectionsAlloc)
		resizeConnections();

	TransactionConnection tc;
	tc.user = &user;
	tc.book = &book;
	tc.transaction = banking.RegisterTransaction(Transaction(book.GetPrice(), user.GetBankCard()));

	connections[connectionsCount++] = tc;
}

void OnlineLibrary::ListTransactions(const User& user) const {
	for (unsigned i = 0; i < connectionsCount; ++i) {
		if (connections[i].user == &user) {
			std::cout << connections[i].book->GetTitle().GetStr() << ", "
				<< connections[i].book->GetAuthor().GetStr() << " Price:"
				<< connections[i].book->GetPrice() << " Card:"
				<< connections[i].transaction->GetBankCard() << " Status:"
				<< connections[i].transaction->GetStatusStr().GetStr() << std::endl;
		}
	}
}

void OnlineLibrary::ExportTransactions(const User& user, const String& fileName) const {
	std::ofstream exportFile(fileName.GetStr(), std::ios::trunc);

	if (!exportFile.is_open()) {
		std::cout << "Couldn't open export file!" << std::endl;
	}
	else {
		for (unsigned i = 0; i < connectionsCount; ++i) {
			if (connections[i].user == &user) {
				exportFile << i << ','
					<< connections[i].book->GetTitle().GetStr() << ',';
				connections[i].transaction->Export(exportFile);
			}
		}
	}
}
