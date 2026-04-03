#ifndef _BANKCLERK
#define _BANKCLERK

#include "String.h"

class BankClerk {
	unsigned clerkNumber;
	String staticPassword;

public:
	BankClerk(unsigned clerkNumber);
	// Ако направим поне един конструктор, то конструктора по подразбиране
	// спира да се създава автоматично
	BankClerk();

	unsigned GetClerkNumber() const;

	void SetPassword(const String& newPassword);

	bool Login(unsigned clerkNumber, unsigned dynamicPassword, const String& staticPassword);
};

#endif /* _BANKCLERK */
