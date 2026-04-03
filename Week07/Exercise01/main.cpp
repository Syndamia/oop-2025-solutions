#include "OnlineLibrary.h"
#include "LibraryBanking.h"
#include "Transaction.h"
#include <iostream>

// Игнорираме всички букви до края на реда вкл.
void ignoreLine() {
	while (std::cin.get() != '\n');
}

// Тази функция ни позволява да приемем от входа низ с неограничена дължина
String getlineEndless() {
	String bufferString;
	for (char buffer = std::cin.get(); buffer != '\n'; buffer = std::cin.get()) {
		bufferString.AppendChar(buffer);
	}
	return bufferString;
}

void RegisterConsole(OnlineLibrary& lib, LibraryBanking& libBank) {
	char c;
	std::cin >> c;
	switch (c) {
		case 'u': {
				User newUser;

				std::cout << "Username: ";
				ignoreLine();
				newUser.SetEmail(getlineEndless());

				std::cout << "Password: ";
				newUser.SetPassword(getlineEndless());

				std::cout << "Bank card: ";
				unsigned bankCard;
				std::cin >> bankCard;
				newUser.SetBankCard(bankCard);

				lib.RegisterUser(newUser);
			}
			break;
		case 'l': {
				std::cout << "Librarian Number: ";
				unsigned number;
				std::cin >> number;

				Librarian newLib(number);

				std::cout << "Password: ";
				ignoreLine();
				newLib.SetPassword(getlineEndless());

				lib.RegisterLibrarian(newLib);
			}
			break;
		case 'c': {
				std::cout << "Clerk Number: ";
				unsigned number;
				std::cin >> number;

				BankClerk newClerk(number);

				std::cout << "Static password: ";
				ignoreLine();
				newClerk.SetPassword(getlineEndless());

				libBank.RegisterClerk(newClerk);
			}
			break;
	}
}

void UserConsole(OnlineLibrary& lib, LibraryBanking& libBank) {
	std::cout << "Username: ";
	ignoreLine();
	String bufferUsername = getlineEndless();

	std::cout << "Password: ";
	String bufferPassword = getlineEndless();

	User* loggedIn = lib.LoginUser(bufferUsername, bufferPassword);
	if (loggedIn == nullptr) {
		std::cout << "Invalid username or password!" << std::endl;
		return;
	}

	while (true) {
		char c;
		std::cin >> c;
		switch (c) {
			case 'e':
				return;
			case 'l':
				loggedIn->ListLibrary();
				break;
			case 'r': {
					std::cout << "User library index: ";
					unsigned i;
					std::cin >> i;
					const Book* book = loggedIn->GetBook(i);

					if (book == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else {
						std::cout << book->GetText().GetStr() << std::endl;
					}
				}
				break;
			case 's':
				lib.ListBooks();
				break;
			case 'p': {
					std::cout << "Book index: ";
					unsigned i;
					std::cin >> i;
					const Book* book = lib.GetBook(i);

					if (book == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else if (loggedIn->GetBankCard() == 0 && book->GetPrice() != 0.0) {
						std::cout << "Cannot purchase book with invalid card!" << std::endl;
					}
					else {
						lib.PurchaseBook(*book, *loggedIn, libBank);
						loggedIn->AddBookToLibrary(book);
					}
				}
				break;
			case 't':
				lib.ListTransactions(*loggedIn);
				break;
			case 'x': {
					std::cout << "Output file: ";
					ignoreLine();
					String fileName = getlineEndless();

					lib.ExportTransactions(*loggedIn, fileName);
				}
				break;

			case 'P': {
					std::cout << "New password: ";
					ignoreLine();
					String newPassword = getlineEndless();

					loggedIn->SetPassword(newPassword);
				}
				break;
			case 'C': {
					std::cout << "New bank card: ";
					unsigned newBankCard;
					std::cin >> newBankCard;

					loggedIn->SetBankCard(newBankCard);
				}
				break;
		}
	}
}

void LibrarianConsole(OnlineLibrary& lib) {
	std::cout << "Librarian number: ";
	unsigned bufferLibrarianNo;
	std::cin >> bufferLibrarianNo;

	std::cout << "Password: ";
	ignoreLine();
	String bufferPassword = getlineEndless();

	Librarian* loggedIn = lib.LoginLibrarian(bufferLibrarianNo, bufferPassword);
	if (loggedIn == nullptr) {
		std::cout << "Invalid librarian number or password!" << std::endl;
		return;
	}

	while (true) {
		char c;
		std::cin >> c;
		switch (c) {
			case 'e':
				return;
			// Не се изисква по условие, но е удобно
			case 's':
				lib.ListBooks();
				break;
			case 'a': {
					Book newBook;
					newBook.SetAvailableForPurchase(true);

					std::cout << "Title: ";
					ignoreLine();
					newBook.SetTitle(getlineEndless());

					std::cout << "Author: ";
					newBook.SetAuthor(getlineEndless());

					std::cout << "Year: ";
					short year;
					std::cin >> year;
					newBook.SetYear(year);

					std::cout << "Price: ";
					double price;
					std::cin >> price;
					newBook.SetPrice(price);

					ignoreLine();
					String text;
					char prevprev = std::cin.get(), prev = std::cin.get(), curr = std::cin.get();
					while (prevprev != '\n' || prev != '.' || curr != '\n') {
						text.AppendChar(prevprev);
						std::cout << '[' << (int)prevprev << ',' << (int)prev << ',' << (int)curr << ']' << std::endl;

						prevprev = prev;
						prev = curr;
						curr = std::cin.get();
					}
					text.AppendChar(prevprev);
					newBook.SetText(text);

					lib.AddBook(newBook);
				}
				break;
			case 'i': {
					Book newBook;
					newBook.SetAvailableForPurchase(true);

					std::cout << "File name: ";
					ignoreLine();
					if (newBook.Import(getlineEndless())) {
						double price;
						std::cout << "Price: ";
						std::cin >> price;
						newBook.SetPrice(price);

						lib.AddBook(newBook);
					}
				}
				break;
			case 'x': {
					std::cout << "Book index: ";
					unsigned i;
					std::cin >> i;
					Book* book = lib.GetBook(i);

					if (book == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else {
						std::cout << "File name: ";
						ignoreLine();
						book->Export(getlineEndless());
					}
				}
				break;
			case 'E': {
					std::cout << "Book index: ";
					unsigned i;
					std::cin >> i;
					Book* book = lib.GetBook(i);

					if (book == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else {
						ignoreLine();
						std::cout << "Title: ";
						book->SetTitle(getlineEndless());

						std::cout << "Author: ";
						book->SetAuthor(getlineEndless());

						std::cout << "Price: ";
						double price;
						std::cin >> price;
						book->SetPrice(price);
					}
				}
				break;
			case 'A': {
					std::cout << "Book index: ";
					unsigned i;
					std::cin >> i;
					Book* book = lib.GetBook(i);

					if (book == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else {
						book->SetAvailableForPurchase(! book->GetAvailableForPurchase());
						if (book->GetAvailableForPurchase()) {
							std::cout << "Book is now available!" << std::endl;
						}
						else {
							std::cout << "Book is now not available!" << std::endl;
						}
					}
				}
				break;
		}
	}
}

void ClerkConsole(LibraryBanking& libBank) {
	std::cout << "Clerk number: ";
	unsigned bufferClerkNo;
	std::cin >> bufferClerkNo;

	std::cout << "Dynamic password: ";
	unsigned dynamicPassword;
	std::cin >> dynamicPassword;

	ignoreLine();
	std::cout << "Static password: ";
	String bufferPassword = getlineEndless();

	BankClerk* loggedIn = libBank.LoginClerk(bufferClerkNo, dynamicPassword, bufferPassword);
	if (loggedIn == nullptr) {
		std::cout << "Invalid clerk number or password!" << std::endl;
		return;
	}

	while (true) {
		char c;
		std::cin >> c;
		switch (c) {
			case 'e':
				return;
			case 'l':
				libBank.ListPendingTransactions();
				break;
			case 'A':
			case 'R': {
					std::cout << "Transaction index: ";
					unsigned i;
					std::cin >> i;
					Transaction* transaction = libBank.GetTransaction(i);

					if (transaction == nullptr) {
						std::cout << "Invalid index!" << std::endl;
					}
					else if (transaction->GetStatus() != STATUS_PENDING) {
						std::cout << "Transaction not pending!" << std::endl;
					}
					else {
						transaction->SetStatus(loggedIn->GetClerkNumber(), c == 'A' ? STATUS_ACCEPTED : STATUS_REJECTED);
					}
				}
				break;
			case 'x': {
					std::cout << "File name: ";
					ignoreLine();
					libBank.ExportNonPendingTransactions(getlineEndless());
				}
				break;
		}
	}
}

// Поискано ни е да имплементираме система,
// това да направим конзолен интерфейс се подразбира
int main() {
	OnlineLibrary lib;
	LibraryBanking libBank;

	while (true) {
		char c;
		std::cin >> c;
		switch (c) {
			case 'r': RegisterConsole(lib, libBank); break;
			case 'u': UserConsole(lib, libBank); break;
			case 'l': LibrarianConsole(lib); break;
			case 'c': ClerkConsole(libBank); break;
			case 'e': return 0;
			default: std::cout << "Invalid!" << std::endl;
		}
	}

	return 0;
}
