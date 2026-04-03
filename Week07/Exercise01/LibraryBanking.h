#ifndef _LIBRARY_BANKING
#define _LIBRARY_BANKING

#include "BankClerk.h"
#include "Transaction.h"

class LibraryBanking {
	BankClerk* clerks;
	unsigned clerksCount;
	unsigned clerksAlloc;

	Transaction* transactions;
	unsigned transactionsCount;
	unsigned transactionsAlloc;

	void free();
	void copyFrom(const LibraryBanking& other);

	void resizeClerks();
	void resizeTransactions();

public:
	LibraryBanking();
	~LibraryBanking();
	LibraryBanking(const LibraryBanking& other);
	LibraryBanking& operator=(const LibraryBanking& other);
	LibraryBanking(LibraryBanking&& other);
	LibraryBanking& operator=(LibraryBanking&& other);

	void RegisterClerk(const BankClerk& clerk);
	BankClerk* LoginClerk(unsigned clerkNumber, unsigned dynamicPassword, const String& staticPassword);

	void ListPendingTransactions();
	Transaction* GetTransaction(unsigned index);
	const Transaction* RegisterTransaction(const Transaction& transaction);

	void ExportNonPendingTransactions(const String& fileName);
};

#endif /* _LIBRARY_BANKING */
