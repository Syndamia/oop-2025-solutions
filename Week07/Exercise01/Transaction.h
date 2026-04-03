#ifndef _TRANSACTION
#define _TRANSACTION

#include "String.h"
#include <fstream>

const unsigned STATUS_PENDING = 0;
const unsigned STATUS_ACCEPTED = 1;
const unsigned STATUS_REJECTED = 2;

// Няма да обвързваме транзакции с потребители директно
// (т.е. няма член-данна която свързва User обект).
// Тази връзка осъществяваме с UserTransaction класа.
// Логически, можем да приемем че не искаме банковия служител
// да знае за акаунтите на купувачите.
class Transaction {
	unsigned clerkNumber;
	double sum;
	unsigned bankCard;
	// Уговаряме се, че стойността на status ще бъде равна на една
	// от глобалните променливи STATUS_PENDING, STATUS_ACCEPTED и STATUS_REJECTED.
	// Тук е добро място за употреба на енумерации (enum).
	unsigned status;

public:
	Transaction(double sum, unsigned bankCard);
	// Ако направим поне един конструктор, то конструктора по подразбиране
	// спира да се създава автоматично
	Transaction();

	// Не искаме транзакции да могат да се променят своеволно.
	// Т.е. след като се създаде транзакция, единствено можем да променяме статус
	unsigned GetClerkNumber() const;
	double GetSum() const;
	unsigned GetBankCard() const;

	unsigned GetStatus() const;
	String GetStatusStr() const;
	void SetStatus(unsigned clerk, unsigned status);

	void PrintTransactionInfo() const;

	void Export(std::ofstream& exportFile) const;
};

#endif /* _TRANSACTION */
