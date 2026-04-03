#include "Transaction.h"
#include <iostream>

Transaction::Transaction(double sum, unsigned bankCard) {
	this->clerkNumber = 0;
	this->sum = sum;
	this->bankCard = bankCard;
	this->status = STATUS_PENDING;
}

Transaction::Transaction() : clerkNumber(0), sum(0), bankCard(0), status(0)
{ }

unsigned Transaction::GetClerkNumber() const {
	return clerkNumber;
}

double Transaction::GetSum() const {
	return sum;
}

unsigned Transaction::GetBankCard() const {
	return bankCard;
}

unsigned Transaction::GetStatus() const {
	return status;
}

String Transaction::GetStatusStr() const {
	switch (status) {
		case STATUS_PENDING: return "Pending";
		case STATUS_ACCEPTED: return "Accepted";
		case STATUS_REJECTED: return "Rejected";
	}
	return "";
}

void Transaction::SetStatus(unsigned clerk, unsigned status) {
	this->clerkNumber = clerk;
	this->status = status;
}

void Transaction::PrintTransactionInfo() const {
	std::cout << clerkNumber << ' '
		<< bankCard << ' '
		<< sum << ' '
		<< GetStatusStr().GetStr() << std::endl;
}

void Transaction::Export(std::ofstream& exportFile) const {
	exportFile << sum << ','
		<< bankCard << ','
		<< clerkNumber << ','
		<< status << std::endl;
}
