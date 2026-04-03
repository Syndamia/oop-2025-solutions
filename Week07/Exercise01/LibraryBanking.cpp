#include "LibraryBanking.h"
#include "Transaction.h"
#include <fstream>
#include <iostream>

void LibraryBanking::free() {
	delete[] clerks;
	delete[] transactions;
}

void LibraryBanking::copyFrom(const LibraryBanking& other) {
	clerksAlloc = other.clerksAlloc;
	clerksCount = other.clerksCount;
	clerks = new BankClerk[clerksAlloc];
	for (unsigned i = 0; i < clerksCount; ++i)
		clerks[i] = other.clerks[i];

	transactionsAlloc = other.transactionsAlloc;
	transactionsCount = other.transactionsCount;
	transactions = new Transaction[transactionsAlloc];
	for (unsigned i = 0; i < transactionsCount; ++i)
		transactions[i] = other.transactions[i];
}

void LibraryBanking::resizeClerks() {
	clerksAlloc = clerksAlloc == 0 ? 8 : clerksAlloc * 2;
	BankClerk* newClerks = new BankClerk[clerksAlloc];

	for (unsigned i = 0; i < clerksCount; ++i)
		newClerks[i] = clerks[i];

	delete[] clerks;
	clerks = newClerks;
}

void LibraryBanking::resizeTransactions() {
	transactionsAlloc = transactionsAlloc == 0 ? 8 : transactionsAlloc * 2;
	Transaction* newTransactions = new Transaction[transactionsAlloc];

	for (unsigned i = 0; i < transactionsCount; ++i)
		newTransactions[i] = transactions[i];

	delete[] transactions;
	transactions = newTransactions;
}

LibraryBanking::LibraryBanking() : clerks(nullptr), clerksCount(0), clerksAlloc(0), transactions(nullptr), transactionsCount(0), transactionsAlloc(0)
{ }

LibraryBanking::~LibraryBanking() {
	free();
}

LibraryBanking::LibraryBanking(const LibraryBanking& other) {
	copyFrom(other);
}

LibraryBanking& LibraryBanking::operator=(const LibraryBanking& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

LibraryBanking::LibraryBanking(LibraryBanking&& other) {
	clerks = other.clerks;
	clerksCount = other.clerksCount;
	clerksAlloc = other.clerksAlloc;

	transactions = other.transactions;
	transactionsCount = other.transactionsCount;
	transactionsAlloc = other.transactionsAlloc;

	other.clerks = nullptr;
	other.clerksCount = other.clerksAlloc = 0;

	other.transactions = nullptr;
	other.transactionsCount = other.transactionsAlloc = 0;
}

LibraryBanking& LibraryBanking::operator=(LibraryBanking&& other) {
	if (this != &other) {
		free();

		clerks = other.clerks;
		clerksCount = other.clerksCount;
		clerksAlloc = other.clerksAlloc;

		transactions = other.transactions;
		transactionsCount = other.transactionsCount;
		transactionsAlloc = other.transactionsAlloc;

		other.clerks = nullptr;
		other.clerksCount = other.clerksAlloc = 0;

		other.transactions = nullptr;
		other.transactionsCount = other.transactionsAlloc = 0;
	}
	return *this;
}

void LibraryBanking::RegisterClerk(const BankClerk& clerk) {
	if (clerksCount >= clerksAlloc)
		resizeClerks();
	clerks[clerksCount++] = clerk;
}

BankClerk* LibraryBanking::LoginClerk(unsigned clerkNumber, unsigned dynamicPassword, const String& staticPassword) {
	for (unsigned i = 0; i < clerksCount; ++i) {
		if (clerks[i].Login(clerkNumber, dynamicPassword, staticPassword))
			// "clerks + i" е същото като "&clerks[i]"
			return clerks + i;
	}
	return nullptr;
}

void LibraryBanking::ListPendingTransactions() {
	for (unsigned i = 0; i < transactionsCount; ++i) {
		if (transactions[i].GetStatus() == STATUS_PENDING) {
			std::cout << '[' << i << "] ";
			transactions[i].PrintTransactionInfo();
		}
	}
}

Transaction* LibraryBanking::GetTransaction(unsigned index) {
	if (index >= transactionsCount)
		return nullptr;
	// "transactions + index" е същото като "&transactions[index]"
	return transactions + index;
}

const Transaction* LibraryBanking::RegisterTransaction(const Transaction& transaction) {
	if (transactionsCount >= transactionsAlloc)
		resizeTransactions();
	transactions[transactionsCount] = transaction;

	if (transaction.GetSum() == 0.0)
		transactions[transactionsCount].SetStatus(0, STATUS_ACCEPTED);

	return transactions + transactionsCount++;
}

void LibraryBanking::ExportNonPendingTransactions(const String& fileName) {
	std::ofstream exportFile(fileName.GetStr(), std::ios::trunc);

	if (!exportFile.is_open()) {
		std::cout << "Couldn't open file!" << std::endl;
	}
	else {
		for (unsigned i = 0; i < transactionsCount; ++i) {
			if (transactions[i].GetStatus() != STATUS_PENDING) {
				exportFile << i << ",";
				transactions[i].Export(exportFile);
			}
		}
	}
}
